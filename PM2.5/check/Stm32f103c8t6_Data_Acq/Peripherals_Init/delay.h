/**
********************************************************
*
* @file      delay.h
* @author    cxiaoqiu12@qq.com
* @date      2017年4月
*
* @brief     systick定时器延时函数头文件
*
*********************************************************/
#ifndef __DELAY_H
#define __DELAY_H 	

#include <stm32f10x.h>

void Delay_Init(void);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);


#endif 

