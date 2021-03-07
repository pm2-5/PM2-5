/**
************************************************************
* @file         key.h
* @brief        key.c��Ӧͷ�ļ�
* @date         2016-09-05
* @author		cxiaoqiu12@qq.com
* 
* @note         �ڻ����Ƶ��ļ��Ͻ��е��޸�
*
***********************************************************/
#ifndef __KEY_H
#define __KEY_H

#include <stdio.h>
#include <stm32f10x.h>


#define KEY_TIMER_MS                            1			//������ʱ��1ms
#define DEBOUNCE_TIME                           30			//<����
#define PRESS_LONG_TIME                         3000

#define KEY_DOWN                                0x10
#define KEY_LONG                                0x40


#define GPIO_KEY1_CLK   RCC_APB2Periph_GPIOC
#define GPIO_KEY1_PORT 	GPIOC
#define GPIO_KEY1_Pin 	GPIO_Pin_13


void KEY_Init(void);
void keyHandle(void);

#endif 

