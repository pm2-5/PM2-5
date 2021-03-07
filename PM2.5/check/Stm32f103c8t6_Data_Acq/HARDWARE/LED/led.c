/**
********************************************************
*
* @file      led.c
* @author    cxiaoqiu12@qq.com
* @date      2017年4月
*
* @brief     LED初始化
*
*********************************************************/
#include "led.h"


void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_LED1_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN;
    GPIO_Init(GPIO_LED1_PORT, &GPIO_InitStructure);
	
    Led_Off( );
}

void Led_On( )
{
	GPIO_SetBits(GPIO_LED1_PORT,GPIO_LED1_PIN);
}

void Led_Off( )
{
     GPIO_ResetBits(GPIO_LED1_PORT,GPIO_LED1_PIN);
}
