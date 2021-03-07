/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
//#include "gizwits_protocol.h"
#include "key.h"
#include "uart.h"
#include "dht12.h"
#include "nrf24l01.h"


uint8_t V_Pm25;
uint8_t USART1_RX_BUF[3];

uint16_t V_Hcho;
u8 USART3_TX_BUF[5]={0xa5,0x5a,0x02,0x80,0xAA};		//发送缓冲
u8 USART3_RX_BUF[3];		//接收缓冲

uint16_t V_Humid,V_Temper;
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 

//TIM2中断函数
//定时器TIM2的中断函数内完成多按键检测逻辑
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        keyHandle( );
    }
}

//TIM3中断服务函数
//void TIM3_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
//    {
//        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
//        gizTimerMs();
//    }
//}

//TIM4中断服务函数,定时5s开启USART1接收中断
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//关闭USART1接收终端
    }
}

//串口1中断服务函数
//用于接收PM2.5的值
void USART1_IRQHandler(void)//串口2中断服务程序
{
	uint8_t i;
	uint8_t Res;
	static char start=0;
	static uint16_t USART1_RX_STA;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接收中断
	{
		Res =USART_ReceiveData(USART1); 				//读取接收到的数据
		if(Res == 0x42) 			//如果接收的第一位数据是0X42
		{
			USART1_RX_STA = 0;      //让数组索引值从0开始
			start = 1;  			//变量用于确定第二位是否接收到了0X4D
		}

		if(start == 1)
		{
			switch (USART1_RX_STA)
			{
				case 1:
					USART1_RX_BUF[0] = Res ;	break;			//接收0x4D
				case 12:
					USART1_RX_BUF[1] = Res ;	break;			//接收大气环境下PM2.5高8位
				case 13:
					USART1_RX_BUF[2] = Res ;	break;			//接收大气环境下PM2.5低8位
				default:	break;
			}
			USART1_RX_STA++;
			if(USART1_RX_STA >= 14 && (0x4d == USART1_RX_BUF[0]))
			{ 
				start  = 0;
				USART1_RX_STA=0;								//对static类型赋初值
				USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	//关闭USART1接收终端，由定时器中断打开
				V_Pm25 = (USART1_RX_BUF[1]<<8) + USART1_RX_BUF[2];
				Tx_Data[0] = V_Pm25;							//数据传入全局变量
				printf("Value_Pm2.5 %d\t",V_Pm25);				//调试打印输出
				for(i=0;i<5;i++)
					uart3SendData(USART3_TX_BUF[i]);
			}
		}                   
	}
} 
//串口2中断服务函数
//接收功能，用于接收与WiFi模组间的串口协议数据
//void USART2_IRQHandler(void)
//{
//    uint8_t value = 0;
//    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//    {
//        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//        value = USART_ReceiveData(USART2);

//        gizPutData(&value, 1);
//    }
//}

//串口3中断服务程序
//用于接收HCHO的数据
void USART3_IRQHandler(void)                	
{
	u8 Res;
	static char start=0;
	static uint8_t USART3_RX_STA=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收中断
	{
		Res =USART_ReceiveData(USART3); //读取接收到的数据
		if(Res == 0xa5) //如果接收的第一位数据是0Xa5
		{
			USART3_RX_STA = 0;     //让数组索引值从0开始
			start = 1;  //这个变量是来确定第二位是否接收到了0X5a
		}

		if(start == 1)
		{
			switch (USART3_RX_STA)
			{
				case 1:
					USART3_RX_BUF[0] = Res ;	break;//接收0x5a
				case 4:
					USART3_RX_BUF[1] = Res ;	break;//接收HCHO 的高8位
				case 5:
					USART3_RX_BUF[2] = Res ;	break;//接收HCHO 的低8位
				default:	break;
			}
			USART3_RX_STA++;
			if(USART3_RX_STA >=6 && (0x5a == USART3_RX_BUF[0]))
			{
				start  = 0;
				USART3_RX_STA=0;//重新开始接收
				//V_Hcho的分辨率为0.01，乘100；
				V_Hcho =((USART3_RX_BUF[1]<<8) + USART3_RX_BUF[2])*100;
				Tx_Data[1] = V_Hcho;
				printf("Value_Hcho %d\t",V_Hcho);
				V_Humid = Humid_Read();
				printf("Value_Humid %d\t",Humid_Read());
				Tx_Data[2]=(uint8_t)(V_Humid>>8);
				Tx_Data[3]=(uint8_t)(V_Humid & 0x00FF);
				
				V_Temper = Temper_Read( );
				printf("Value_Temper %d\n",V_Temper);
				Tx_Data[4]=(uint8_t)(V_Temper>>8);
				Tx_Data[5]=(uint8_t)(V_Temper & 0x00FF);
				Tx_Data[6]=0xff;
				printf("数据发送：%0x\n",NRF24L01_TxPacket(Tx_Data));

			}
		}                   
	}
} 


void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
