/**
************************************************************
* @file         spi.h
* @brief        spi初始化配置
* @author       cxiaoqiu12@qq.com
* @date         2017年4月
* 
* @note         spi初始化配置头文件
*
***********************************************************/
#ifndef _SPI_H
#define _SPI_H

#include <stm32f10x.h>


uint8_t SPI1_ReadWriteByte(uint8_t TxData);
void Spi_Init(void);

#endif /*_HAL_UART_H*/


