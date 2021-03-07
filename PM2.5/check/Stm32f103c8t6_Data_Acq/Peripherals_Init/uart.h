/**
************************************************************
* @file         uart.h
* @brief        ��������ͷ�ļ�
* @author       cxiaoqiu12@qq.com
* @date         2017��4��
* 
* @note         ��stm32F103c8t6�������������ʼ��
*
***********************************************************/
#ifndef _UART_H
#define _UART_H

#include <stdio.h>
#include <stm32f10x.h>


#define Open_UART1//��PM2.5ģ��ͨ�š�uart����
//#define Open_UART2//�������ݵ�esp266
#define Open_UART3//��HCHOģ��ͨ��


void Uart_Init(void);
void uart2SendData(uint8_t data);
void uart3SendData(uint8_t data);

#endif /*_HAL_UART_H*/


