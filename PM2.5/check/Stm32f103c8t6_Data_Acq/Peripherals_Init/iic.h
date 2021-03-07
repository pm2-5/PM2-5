#ifndef __IIC_H
#define __IIC_H
#include "sys.h"


//IO操作函数	 
#define IIC_SCL    PAout(4) //SCL
#define IIC_SDA    PAout(1) //SDA	 
#define READ_SDA   PAin(1)  //输入SDA 

void SDA_IN(void);
void SDA_OUT(void);

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

#endif



