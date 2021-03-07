/**
************************************************************
* @file         spi.h
* @brief        spi��ʼ������
* @author       cxiaoqiu12@qq.com
* @date         2017��4��
* 
* @note         spi��ʼ������ͷ�ļ�
*
***********************************************************/
#ifndef _SPI_H
#define _SPI_H

#include <stm32f10x.h>


uint8_t SPI1_ReadWriteByte(uint8_t TxData);
void Spi_Init(void);

#endif /*_HAL_UART_H*/


