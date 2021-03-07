#ifndef __IIC_H
#define __IIC_H
#include "sys.h"


//IO��������	 
#define IIC_SCL    PAout(4) //SCL
#define IIC_SDA    PAout(1) //SDA	 
#define READ_SDA   PAin(1)  //����SDA 

void SDA_IN(void);
void SDA_OUT(void);

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

#endif



