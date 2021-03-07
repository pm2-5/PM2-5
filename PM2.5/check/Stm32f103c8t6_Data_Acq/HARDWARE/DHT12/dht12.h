#ifndef __DHT12_H
#define __DHT12_H
#include "iic.h" 
#include "stm32f10x.h"


extern uint8_t Humid[3];
extern uint8_t Temper[4];//��һλ��������

typedef enum
{
	FALSE=0,
	TURE
}bool;

void DHT12_Init(void); //��ʼ��IIC
					  
//��ȡ��ʪ�Ȳ�ת��Ϊ�ַ��� 0ʧ�� 1�ɹ�
uint16_t Humid_Read(void);
uint16_t Temper_Read(void);
#endif

