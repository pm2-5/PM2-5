/**
************************************************************
* @file         uart.h
* @brief        串口驱动头文件
* @author       cxiaoqiu12@qq.com
* @date         2017年4月
* 
* @note         对stm32F103c8t6进行条件编译初始化
*
***********************************************************/
#ifndef _UART_H
#define _UART_H

#include <stdio.h>
#include <stm32f10x.h>


#define Open_UART1//与PM2.5模块通信、uart调试
//#define Open_UART2//发送数据到esp266
#define Open_UART3//与HCHO模块通信


void Uart_Init(void);
void uart2SendData(uint8_t data);
void uart3SendData(uint8_t data);

#endif /*_HAL_UART_H*/


