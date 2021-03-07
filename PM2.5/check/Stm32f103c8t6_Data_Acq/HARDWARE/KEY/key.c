/**
************************************************************
* @file         key.c
* @brief        按键驱动

* 本工程只使用了一个按键来设置wifi的连接；
* 按键的硬件连接是，当按键按下时
* @author       cxiaoqqiu12@qq.com
*
* @note        	在机智云的文件的基础上进行修改的
***********************************************************/
#include "key.h"
#include <stm32f10x.h>
#include "tim.h"
//#include "gizwits_protocol.h"

uint8_t    keyCountTime;		//<定时次数计数；


//KEY1 GPIO初始化
void KEY_Init( )
{   
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_KEY1_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		

	GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_Pin;
	GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);

    //初始化周期为1MS定时器,在主函数已经初始化了；
    //TIM2_Init();
}

//short Press服务函数
void Key1shortPress( )
{
	printf("KEY1 PRESS SHORT ,Wifi Reset\n");
//    gizwitsSetMode(WIFI_RESET_MODE);
}
//long Rress服务函数
void Key1longPress()
{
	printf("KEY2 PRESS LONG ,AirLink mode\n");
//    gizwitsSetMode(WIFI_AIRLINK_MODE);
}
/**
* @brief Read the KEY value
* @param none
* @return uint16_t型的按键状态值
*/
uint16_t readKeyValue( )
{
    static uint8_t keyCheck = 0;
    static uint8_t keyState = 0;
    static uint16_t keyLongCheck = 0;
    static uint16_t keyPrev = 0;      						///<上一次按键

    uint16_t keyPress = 0;
    uint16_t keyReturn = 0;
    
    keyCountTime ++;
    
    if(keyCountTime >= (DEBOUNCE_TIME / KEY_TIMER_MS))      ///<keyCountTime 1MS+1  按键消抖10MS
    {
        keyCountTime = 0;
        keyCheck = 1;
    }
    if(1 == keyCheck)
    {
        keyCheck = 0;
        keyPress = !GPIO_ReadInputDataBit(GPIO_KEY1_PORT,GPIO_KEY1_Pin);//获取KEY1 GPIO的值，GPIO下拉
        switch (keyState)
        {
            case 0:
                if(keyPress != 0)
                {
                    keyPrev = keyPress;
                    keyState = 1;
                }
                break;
                
            case 1:
                if(keyPress == keyPrev)
                    keyState = 2;
                else                //按键抬起,是抖动,不响应按键
                    keyState = 0;
                break;
                
            case 2:
                if(keyPress != keyPrev)
                {
                    keyState = 0;
                    keyLongCheck = 0;
                    keyReturn = KEY_DOWN;
                    return keyReturn;
                }
                if(keyPress == keyPrev)
                {
                    keyLongCheck++;
                    if(keyLongCheck >= (PRESS_LONG_TIME / DEBOUNCE_TIME))    //长按3S有效
                    {
                        keyLongCheck = 0;
                        keyState = 3;
                        keyReturn= KEY_LONG;
                        return keyReturn;
                    }
                }
                break;

            case 3:
                if(keyPress != keyPrev)
                {
                    keyState = 0;
                }
                break;
        }
    }
    return  0;
}

/**
* @brief 按键回调函数

* 在该函数内完成按键状态监测后调用对应的回调函数
* @param [in] keys 按键功能全局结构体指针
* @return none
*/
void keyHandle( )
{
    uint16_t key_value = 0;

    key_value = readKeyValue( );

    if(0 == key_value) return;
    
    if(key_value == KEY_DOWN)
	{
		Key1shortPress( ); 
	}
    if(key_value == KEY_LONG)
	{
		Key1longPress( );
	}
} 


