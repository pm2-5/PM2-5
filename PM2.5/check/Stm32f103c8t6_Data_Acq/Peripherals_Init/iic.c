#include "iic.h"
#include "delay.h"

//SDA:PA1
void SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;   //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//SDA:PA1
void SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//初始化IIC
//SDA:PA1	SCL:PA4
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	IIC_SCL=1;//高电平
	IIC_SDA=1;

}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     	//SDA线设为输出；
	IIC_SDA=1;	  	//SDA输出高电平；
	IIC_SCL=1;			//SCL输出高电平；
	delay_us(4);		
 	IIC_SDA=0;			//开始信号:当SCL为高,SDA由高变低；
	delay_us(4);
	IIC_SCL=0;			//钳住I2C总线，准备发送或接收数据 
	delay_us(4);
}	  
//产生IIC停止信号
//当SCL为hight时，SDA从low变hight
void IIC_Stop(void)
{
	SDA_OUT();			
	IIC_SCL=0;
	IIC_SDA=0;			
 	delay_us(4);
	IIC_SCL=1; 
	delay_us(4);
	IIC_SDA=1;			//发送I2C总线结束信号
	delay_us(4);									   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	
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
	IIC_SCL=0;//时钟输出0 
  delay_us(50);	
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


