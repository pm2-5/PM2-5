/**
************************************************************
* @file         main.c
* @brief        ������
* @author       cxiaoqiu12@qq.com
* @date         2017��4��
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
* @brief������ں���

* �ڸú���������û���صĳ�ʼ��,�����߼�ѭ��
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

