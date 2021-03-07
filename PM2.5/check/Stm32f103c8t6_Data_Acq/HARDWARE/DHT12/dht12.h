#ifndef __DHT12_H
#define __DHT12_H
#include "iic.h" 
#include "stm32f10x.h"


extern uint8_t Humid[3];
extern uint8_t Temper[4];//第一位是正负号

typedef enum
{
	FALSE=0,
	TURE
}bool;

void DHT12_Init(void); //初始化IIC
					  
//读取温湿度并转换为字符串 0失败 1成功
uint16_t Humid_Read(void);
uint16_t Temper_Read(void);
#endif

