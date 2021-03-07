/**
************************************************************
* @file         main.c
* @brief        主函数
* @author       cxiaoqiu12@qq.com
* @date         2017年4月
* 
* @note         
*
***********************************************************/
#include <string.h>
#include "uart.h"
#include "delay.h"
#include "led.h"
#include "dht12.h"
#include "tim.h"
#include "key.h"
#include "spi.h"
#include "nrf24l01.h"

/**
* @brief程序入口函数

* 在该函数中完成用户相关的初始化,及主逻辑循环
* @param none
* @return none
*/
int main()
{
	Uart_Init( );
	Delay_Init( );
	Led_Init( );
	DHT12_Init( );
	TIMx_Init( );
	KEY_Init( );
	NRF24L01_Init( );
	while(1)
	{
		Led_On();
		delay_ms(500);
		Led_Off();
		delay_ms(500);
		
	};
}

