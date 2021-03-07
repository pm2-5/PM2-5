#include "dht12.h" 
#include "delay.h"

uint8_t dat[5];					//��������
static uint8_t check;			//���ڱ�������У��Ľ��

//��ʼ��IIC�ӿ�
void DHT12_Init(void)
{
	IIC_Init();
}

void DHT12_ReadByte()
{				  
	uint8_t i;		  	    																 
    IIC_Start( );  				//�����������߿�ʼ�źţ�

	IIC_Send_Byte(0xB8);		
	IIC_Wait_Ack( );

	IIC_Send_Byte(0x00);		//дģʽ������0x00
	IIC_Wait_Ack( );			//��Ӧ��IIC_Stop

	IIC_Start( );	//�������ģʽ	,����0xB8������	
	IIC_Send_Byte(0xB9); 				   
	IIC_Wait_Ack( );	 
	 
	for(i=0;i<4;i++)
	{
		dat[i]=IIC_Read_Byte(1);//��ǰ�ĸ�������ACK
	}
	dat[i]=IIC_Read_Byte(0);	//����5������NACK

    IIC_Stop();//����һ��ֹͣ����	    
}

//��ʪ��ʫ���ȡУ�飬�ɹ����� TURE�����󷵻� FALSE
void Data_Check()
{ 
	DHT12_ReadByte();
	
	if(dat[4] == (dat[0]+dat[1]+dat[2]+dat[3]))
		check = 0xff;	//��ȡ�ɹ�
	else
		check = 0;	//��ȡʧ��
}

//��ȡʪ��ֵ
uint16_t Humid_Read( )
{
	
	uint16_t V_Humid;
	Data_Check( );
	if(check)
	{
		V_Humid = ((dat[0]*10+dat[1])-200);//ʪ�ȵ�ȡֵ��ΧΪ20%-95%��ȡ����Ϊ-20�����ֵ��ΧΪ0-750
										//����Ľ�������ֵ V_Humid =(����λ+С��λ)/�ֱ���+������
		return V_Humid;
	}
	else
		return 0;
}
//��ȡ�¶�ֵ��
uint16_t Temper_Read( )
{
	uint16_t V_Temper;
	if(check)
	{
		if(dat[3]&0x80)
			V_Temper = (200-(dat[2]*10+(dat[3]&0x7F)));//�¶�Ϊ�������¶ȵ�ȡֵ��Χ��-20��60������Ϊ200,��
		else
			V_Temper = (200+(dat[2]*10+(dat[3]&0x7F)));//�¶�Ϊ������
		check = 0;
		return V_Temper; 
	}
	else
		return 0;
}


