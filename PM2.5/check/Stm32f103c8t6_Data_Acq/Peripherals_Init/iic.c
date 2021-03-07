#include "iic.h"
#include "delay.h"

//SDA:PA1
void SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;   //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//SDA:PA1
void SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//��ʼ��IIC
//SDA:PA1	SCL:PA4
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	IIC_SCL=1;//�ߵ�ƽ
	IIC_SDA=1;

}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     	//SDA����Ϊ�����
	IIC_SDA=1;	  	//SDA����ߵ�ƽ��
	IIC_SCL=1;			//SCL����ߵ�ƽ��
	delay_us(4);		
 	IIC_SDA=0;			//��ʼ�ź�:��SCLΪ��,SDA�ɸ߱�ͣ�
	delay_us(4);
	IIC_SCL=0;			//ǯסI2C���ߣ�׼�����ͻ�������� 
	delay_us(4);
}	  
//����IICֹͣ�ź�
//��SCLΪhightʱ��SDA��low��hight
void IIC_Stop(void)
{
	SDA_OUT();			
	IIC_SCL=0;
	IIC_SDA=0;			
 	delay_us(4);
	IIC_SCL=1; 
	delay_us(4);
	IIC_SDA=1;			//����I2C���߽����ź�
	delay_us(4);									   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	
	delay_us(4);	   
	IIC_SCL=1;
	delay_us(4);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
		delay_us(1);
	}
	IIC_SCL=0;//ʱ�����0 
  delay_us(50);	
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(5);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(5);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	 {
        IIC_SCL=0; 
        delay_us(50);
				IIC_SCL=1;
		    delay_us(50);
        receive<<=1;
        if(READ_SDA)
				receive++;	
				
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


