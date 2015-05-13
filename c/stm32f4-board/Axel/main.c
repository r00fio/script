#include "stm32_ub_lis302dl.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "main.h"
#include "math.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include <misc.h>
#include <stm32f4xx_syscfg.h>
// #define ARM_MATH_CM4
// #include "arm_math.h"c
#define __STM32F4xx_EXTI_H


int main(void) {
    //  SystemInit();fd
    //  while(!(RCC->CR & RCC_CR_HSERDY)){} //proverka na zapusk occ
    //  RCC -> CR |= RCC_CR_HSEON;
    //  while(!(RCC->CR & RCC_CR_HSEON)){}

    USART_Configuration();

    USART2 -> BRR = (16000000 / 115200);
    UB_LIS302_Init(SCALE_8G);
    init_leds();
    init_it();
    tim_init();

    while (1) {
        UB_LIS302_Read(); // read LIS302

        toSphericalCoordinateSystem();
        blinkInclination();

        println("\n\r");
        splitAndSend(LIS302.pitch);
        println(",");
        splitAndSend(LIS302.roll);
        println(",");
        splitAndSend(LIS302.yaw);
        
    }
}

void blinkInclination(){
    
    int m = 1;
 // делитель частоты
    // if (LIS302.roll >= 0) {
    //     TIM4 -> CCR1 = m * 2 * LIS302.roll;
    // }else {
    //     TIM4 -> CCR1 = m * LIS302.roll * (-2);
    // }

    TIM_OCInitTypeDef oc_init;
    TIM_OCStructInit(&oc_init);
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    oc_init.TIM_OutputState = TIM_OutputState_Enable;

    //1
    if (LIS302.roll >= 0) {
        oc_init.TIM_Pulse = LIS302.roll * m;
    }else{
        oc_init.TIM_Pulse = 0; // or defined speed
    }
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4,&oc_init);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    //2

    if (LIS302.pitch > 0) {
        oc_init.TIM_Pulse =  LIS302.pitch * m;
    }else{
        oc_init.TIM_Pulse = 0;
    }
    TIM_OC2Init(TIM4,&oc_init);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
     
    //3
    if (LIS302.roll >= 0) {
        oc_init.TIM_Pulse = 0;
    }else{
        oc_init.TIM_Pulse = LIS302.roll * m * (-1);
    }
    
    TIM_OC3Init(TIM4,&oc_init);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
     
    // 4
    if (LIS302.pitch >= 0) {
        oc_init.TIM_Pulse = 0;
    }else{
        oc_init.TIM_Pulse = LIS302.pitch * m * (-1);
    }
    
    TIM_OC4Init(TIM4,&oc_init);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
    EXTI_ClearITPendingBit(EXTI_Line0);    
}

void splitAndSend(int16_t coordinate) {
    sendData((coordinate & 0xFF00) >> 8);
    sendData(coordinate & 0xFF);
}
void EXTI0_IRQHandler() {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        TIM_OCInitTypeDef oc_init;
        TIM_OCStructInit(&oc_init);
        oc_init.TIM_OCMode = TIM_OCMode_PWM1;
        oc_init.TIM_OutputState = TIM_OutputState_Enable;
        oc_init.TIM_Pulse = 5000;
        oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OC1Init(TIM4,&oc_init);
        TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
        // //2
        // oc_init.TIM_Pulse = 500;
        // TIM_OC2Init(TIM4,&oc_init);
        // TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
         
        //3
        oc_init.TIM_Pulse = 5000;
        TIM_OC3Init(TIM4,&oc_init);
        TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
         
        // //4
        // oc_init.TIM_Pulse = 500;
        // TIM_OC4Init(TIM4,&oc_init);
        // TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
        EXTI_ClearITPendingBit(EXTI_Line0);    
 }
}

void init_it() {
      EXTI_InitTypeDef   EXTI_InitStructure;
      GPIO_InitTypeDef   GPIO_InitStructure;
      NVIC_InitTypeDef   NVIC_InitStructure;
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0); // разрешаем внешнее прерывание по порту А
      EXTI_InitStructure.EXTI_Line = EXTI_Line0;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;
      EXTI_Init(&EXTI_InitStructure);
      NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
}

void tim_init(){
        TIM_TimeBaseInitTypeDef base_timer;
        TIM_TimeBaseStructInit(&base_timer);
 
        // base_timer.TIM_Prescaler = 8400 - 1;   // делитель частоты
        base_timer.TIM_Prescaler = 0;   // делитель частоты
        base_timer.TIM_Period = 180;  // период
        base_timer.TIM_CounterMode = TIM_CounterMode_Up; // счёт вверх
        TIM_TimeBaseInit(TIM4, &base_timer);
 
        // TIM_OCInitTypeDef oc_init;
        // TIM_OCStructInit(&oc_init);
        // oc_init.TIM_OCMode = TIM_OCMode_PWM1;   // работаем в режиме ШИМ ( PWM )
        // oc_init.TIM_OutputState = TIM_OutputState_Enable;
        // oc_init.TIM_Pulse = 500;   // частота шим
        // oc_init.TIM_OCPolarity = TIM_OCPolarity_High;  // положительная полярность
 
        // TIM_OC1Init(TIM4,&oc_init);   /// заносим данные в первый канал - порт D12
        // TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
        //2
        // oc_init.TIM_Pulse = 5000; /// изменяем частоту шим
        // TIM_OC2Init(TIM4,&oc_init);  // настраиваем второй канал D13
        // TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
        // //3 канал - D14
        // oc_init.TIM_Pulse = 500;
        // TIM_OC3Init(TIM4,&oc_init);
        // TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
        //4  - D15
        // oc_init.TIM_Pulse = 5000;
        // TIM_OC4Init(TIM4,&oc_init);
        // TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
        TIM_ARRPreloadConfig(TIM4,ENABLE);
        TIM_Cmd(TIM4,ENABLE);   // запускаем счёт
}

void init_leds() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF;
    init.GPIO_OType = GPIO_OType_PP;
    init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&init);
 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
}

void USART_Configuration(void) {
    // sort out clocks
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Map USART2 to A.02
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    // Initialize USART
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    /* Configure USART */
    USART_Init(USART2, &USART_InitStructure);
    /* Enable the USART */
    USART_Cmd(USART2, ENABLE);
}

int size(char *ptr) {
    int count = 0;
    while (*(ptr + count) != '\0')
    {
        ++count;
    }
    return count;
}

void sendData(int8_t ch) {
    while (!(USART2->SR & USART_SR_TXE) | !(USART2->SR & USART_SR_TC));
    USART2->DR = ch;
}
    
void USART_PutChar(char ch) {
    while (!(USART2->SR & USART_SR_TXE) | !(USART2->SR & USART_SR_TC));
    USART2->DR = ch;
}

int println(char *str) {
    while (*str != 0)
    {
        USART_PutChar(*str);
        str++;
    }
    return 0;
}

int clearArray(char *str) {
    while (*str != 0)
    {
        *str = 0;
        str++;
    }
    return 0;
}

void toSphericalCoordinateSystem() {
    int z, x, y;
    x = LIS302.x_achse ;
    y = LIS302.y_achse ;
    z = LIS302.z_achse ;
    int s1 = (y * y) + (z * z);
    int s2 = (x * x) + (z * z);
    int s3 = (x * x) + (y * y);
    double q1 = x / sqrt(s1);
    double q2 = y / sqrt(s2);
    double q3 = sqrt(s3) / z;
    LIS302.pitch = atan(q1) * 100;
    LIS302.roll = atan(q2) * 100;
    LIS302.yaw = atan(q3) * 100;
}