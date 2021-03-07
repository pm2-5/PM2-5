#include "dht12.h" 
#include "delay.h"

uint8_t dat[5];					//接收数据
static uint8_t check;			//用于保存数据校验的结果

//初始化IIC接口
void DHT12_Init(void)
{
	IIC_Init();
}

void DHT12_ReadByte()
{				  
	uint8_t i;		  	    																 
    IIC_Start( );  				//主机发送总线开始信号；

	IIC_Send_Byte(0xB8);		
	IIC_Wait_Ack( );

	IIC_Send_Byte(0x00);		//写模式，发送0x00
	IIC_Wait_Ack( );			//无应答，IIC_Stop

	IIC_Start( );	//进入接收模式	,接收0xB8的数据	
	IIC_Send_Byte(0xB9); 				   
	IIC_Wait_Ack( );	 
	 
	for(i=0;i<4;i++)
	{
		dat[i]=IIC_Read_Byte(1);//读前四个，发送ACK
	}
	dat[i]=IIC_Read_Byte(0);	//读第5个发送NACK

    IIC_Stop();//产生一个停止条件	    
}

//温湿度诗句读取校验，成功返回 TURE，错误返回 FALSE
void Data_Check()
{ 
	DHT12_ReadByte();
	
	if(dat[4] == (dat[0]+dat[1]+dat[2]+dat[3]))
		check = 0xff;	//读取成功
	else
		check = 0;	//读取失败
}

//读取湿度值
uint16_t Humid_Read( )
{
	
	uint16_t V_Humid;
	Data_Check( );
	if(check)
	{
		V_Humid = ((dat[0]*10+dat[1])-200);//湿度的取值范围为20%-95%，取增量为-20，相对值范围为0-750
										//计算的结果是相对值 V_Humid =(整数位+小数位)/分辨率+增量；
		return V_Humid;
	}
	else
		return 0;
}
//读取温度值；
uint16_t Temper_Read( )
{
	uint16_t V_Temper;
	if(check)
	{
		if(dat[3]&0x80)
			V_Temper = (200-(dat[2]*10+(dat[3]&0x7F)));//温度为负数，温度的取值范围是-20—60，增量为200,；
		else
			V_Temper = (200+(dat[2]*10+(dat[3]&0x7F)));//温度为正数；
		check = 0;
		return V_Temper; 
	}
	else
		return 0;
}


