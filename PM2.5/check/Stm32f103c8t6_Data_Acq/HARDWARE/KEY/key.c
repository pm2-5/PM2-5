/**
************************************************************
* @file         key.c
* @brief        ��������

* ������ֻʹ����һ������������wifi�����ӣ�
* ������Ӳ�������ǣ�����������ʱ
* @author       cxiaoqqiu12@qq.com
*
* @note        	�ڻ����Ƶ��ļ��Ļ����Ͻ����޸ĵ�
***********************************************************/
#include "key.h"
#include <stm32f10x.h>
#include "tim.h"
//#include "gizwits_protocol.h"

uint8_t    keyCountTime;		//<��ʱ����������


//KEY1 GPIO��ʼ��
void KEY_Init( )
{   
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_KEY1_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		

	GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_Pin;
	GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);

    //��ʼ������Ϊ1MS��ʱ��,���������Ѿ���ʼ���ˣ�
    //TIM2_Init();
}

//short Press������
void Key1shortPress( )
{
	printf("KEY1 PRESS SHORT ,Wifi Reset\n");
//    gizwitsSetMode(WIFI_RESET_MODE);
}
//long Rress������
void Key1longPress()
{
	printf("KEY2 PRESS LONG ,AirLink mode\n");
//    gizwitsSetMode(WIFI_AIRLINK_MODE);
}
/**
* @brief Read the KEY value
* @param none
* @return uint16_t�͵İ���״ֵ̬
*/
uint16_t readKeyValue( )
{
    static uint8_t keyCheck = 0;
    static uint8_t keyState = 0;
    static uint16_t keyLongCheck = 0;
    static uint16_t keyPrev = 0;      						///<��һ�ΰ���

    uint16_t keyPress = 0;
    uint16_t keyReturn = 0;
    
    keyCountTime ++;
    
    if(keyCountTime >= (DEBOUNCE_TIME / KEY_TIMER_MS))      ///<keyCountTime 1MS+1  ��������10MS
    {
        keyCountTime = 0;
        keyCheck = 1;
    }
    if(1 == keyCheck)
    {
        keyCheck = 0;
        keyPress = !GPIO_ReadInputDataBit(GPIO_KEY1_PORT,GPIO_KEY1_Pin);//��ȡKEY1 GPIO��ֵ��GPIO����
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
                else                //����̧��,�Ƕ���,����Ӧ����
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
                    if(keyLongCheck >= (PRESS_LONG_TIME / DEBOUNCE_TIME))    //����3S��Ч
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
* @brief �����ص�����

* �ڸú�������ɰ���״̬������ö�Ӧ�Ļص�����
* @param [in] keys ��������ȫ�ֽṹ��ָ��
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


