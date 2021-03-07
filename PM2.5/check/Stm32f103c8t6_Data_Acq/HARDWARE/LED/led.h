#ifndef _LED_H
#define _LED_H

#include <stdio.h>
#include <stm32f10x.h>

#define GPIO_LED1_CLK    RCC_APB2Periph_GPIOB
#define GPIO_LED1_PORT   GPIOB
#define GPIO_LED1_PIN    GPIO_Pin_1


#define LED1           0X01

void Led_Init(void);
void Led_On(void);
void Led_Off(void);

#endif /*_HAL_LED_H*/

