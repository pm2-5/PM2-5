/**
************************************************************
* @file         uart.c
* @brief        串口驱动初始化
* @author       cxiaoqiu12@qq.com
* @date         2017年4月
* 
* @note         对串口进行初始化
*
***********************************************************/
#include "stm32f10x_rcc.h"
#include "uart.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
* @brief 串口GPIO初始化

* @param none
* @return none
*/
void uartGpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
//TX:PA9	RX:PA10
#if defined (Open_UART1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);// APB2

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
	
//TX:PA2	RX:PA3
#if defined (Open_UART2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);// APB1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

//TX:PB10	RX:PB11
#if defined (Open_UART3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);// APB1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
}

/**
* @brief 串口配置初始化

* @param none
* @return none
*/
void uartConfig(void)
{
    USART_InitTypeDef USART_InitStructure;
	
#if defined (Open_UART1)
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

//  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启接收终端
    USART_Cmd(USART1, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC); /*清空发送完成标志,Transmission Complete flag */
#endif

#if defined (Open_UART2)
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2, ENABLE);
    USART_ClearFlag(USART2, USART_FLAG_TC); /*清空发送完成标志,Transmission Complete flag */
#endif

#if defined (Open_UART3)
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3, ENABLE);
    USART_ClearFlag(USART3, USART_FLAG_TC); /*清空发送完成标志,Transmission Complete flag */
#endif

}

/**
* @brief 串口NVIC初始化

* @param none
* @return none
*/
void nvicConfiguration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
#if defined (Open_UART1)
    /*使能串口中断,并设置优先级*/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (Open_UART2)
    /*使能串口中断,并设置优先级*/
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (Open_UART3)
    /*使能串口中断,并设置优先级*/
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

/**
* @brief UART2写操作
*
* @param data     : 数据
*
* @return : none
*/

void uart2SendData(uint8_t data)
{
    USART_SendData(USART2,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

/**
* @brief UART2写操作
*
* @param data     : 数据
*
* @return : none
*/
void uart3SendData(uint8_t data)
{
    USART_SendData(USART3,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

/**
* @brief 串口初始化函数
* @param none
* @return none
*/
void Uart_Init(void)
{
    uartGpioInit();
    uartConfig();
    nvicConfiguration();
}

/**
* @brief printf打印重定向
* @param none
* @return none
*/
PUTCHAR_PROTOTYPE
{
    //Place your implementation of fputc here , e.g. write a character to the USART
    USART_SendData(USART1,(uint8_t)ch);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}
