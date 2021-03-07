/**
********************************************************
*
* @file      delay.c
* @author    cxiaoqiu12@qq.com
* @date      2017年4月
*
* @brief     systick定时器延时函数
*
*********************************************************/

#include "delay.h"

static uint8_t  facUs=0;		//us延时倍乘数
static uint16_t facMs=0;		//ms延时倍乘数

/**
* @brief 初始化delay

* 选择HCK/8，1us为系统始终的1/8
* @param none
* @return none
*/
void Delay_Init( void )
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟,HCLK/8
    facUs=72/8; 										//为系统时钟的1/8 ，系统始终为72M
    facMs =(u16)facUs*1000;
}

/**
* @brief 延时nus

* @param nus
* @return none
*/
void delay_us(uint32_t nus)
{
    uint32_t temp;  
    SysTick->LOAD = nus*facUs;  //延时10us,10*9 = 90,装到load寄存器中
    SysTick->VAL=0x00;//计数器清0
    SysTick->CTRL = 0x01;//配置异常生效,也就是计数器倒数到0时发出异常通知
    do  
    {  
         temp = SysTick->CTRL;//时间到,该位将被硬件置1,但被查询后自动清0
    }  
    while(temp & 0x01 && !(temp &(1<<16)));//查询
    SysTick->CTRL = 0x00;//关闭定时器
    SysTick->VAL = 0x00;//清空val,清空定时器
}

/**
* @brief 延时nms

* @param nms
* @return none
*/
void delay_ms(uint16_t nms)
{
    uint32_t temp;  
    SysTick->LOAD = nms*facMs;//延时10ms,10*9 = 90,装到load寄存器中
    SysTick->VAL=0x00;//计数器清0
    SysTick->CTRL = 0x01;//配置异常生效,也就是计数器倒数到0时发出异常通知
    do  
    {  
         temp = SysTick->CTRL;//时间到,该位将被硬件置1,但被查询后自动清0
    }  
    while(temp & 0x01 && !(temp &(1<<16)));//查询

    SysTick->CTRL = 0x00;//关闭定时器
    SysTick->VAL = 0x00;//清空val,清空定时器
}
