/**
********************************************************
*
* @file      delay.c
* @author    cxiaoqiu12@qq.com
* @date      2017��4��
*
* @brief     systick��ʱ����ʱ����
*
*********************************************************/

#include "delay.h"

static uint8_t  facUs=0;		//us��ʱ������
static uint16_t facMs=0;		//ms��ʱ������

/**
* @brief ��ʼ��delay

* ѡ��HCK/8��1usΪϵͳʼ�յ�1/8
* @param none
* @return none
*/
void Delay_Init( void )
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��,HCLK/8
    facUs=72/8; 										//Ϊϵͳʱ�ӵ�1/8 ��ϵͳʼ��Ϊ72M
    facMs =(u16)facUs*1000;
}

/**
* @brief ��ʱnus

* @param nus
* @return none
*/
void delay_us(uint32_t nus)
{
    uint32_t temp;  
    SysTick->LOAD = nus*facUs;  //��ʱ10us,10*9 = 90,װ��load�Ĵ�����
    SysTick->VAL=0x00;//��������0
    SysTick->CTRL = 0x01;//�����쳣��Ч,Ҳ���Ǽ�����������0ʱ�����쳣֪ͨ
    do  
    {  
         temp = SysTick->CTRL;//ʱ�䵽,��λ����Ӳ����1,������ѯ���Զ���0
    }  
    while(temp & 0x01 && !(temp &(1<<16)));//��ѯ
    SysTick->CTRL = 0x00;//�رն�ʱ��
    SysTick->VAL = 0x00;//���val,��ն�ʱ��
}

/**
* @brief ��ʱnms

* @param nms
* @return none
*/
void delay_ms(uint16_t nms)
{
    uint32_t temp;  
    SysTick->LOAD = nms*facMs;//��ʱ10ms,10*9 = 90,װ��load�Ĵ�����
    SysTick->VAL=0x00;//��������0
    SysTick->CTRL = 0x01;//�����쳣��Ч,Ҳ���Ǽ�����������0ʱ�����쳣֪ͨ
    do  
    {  
         temp = SysTick->CTRL;//ʱ�䵽,��λ����Ӳ����1,������ѯ���Զ���0
    }  
    while(temp & 0x01 && !(temp &(1<<16)));//��ѯ

    SysTick->CTRL = 0x00;//�رն�ʱ��
    SysTick->VAL = 0x00;//���val,��ն�ʱ��
}
