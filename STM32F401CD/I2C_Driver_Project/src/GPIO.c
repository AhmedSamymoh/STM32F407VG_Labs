/************************************************************
* @Author : AhmedSamy
* @File: GPIO.c
* @Platform(MCU) : STM32F401CD
* @Date : 17-12-2023
*************************************************************/

#include "GPIO.h"


/************************************************************
 * @brief Initializes the specified GPIO pin.
 * @param PORT: Port identifier (e.g., PORT_A, PORT_B, etc.)
 * @param PIN: Pin number
 * @param State: Pin state (INPUT or OUTPUT)
*************************************************************/
void GPIO_InitPin(int PORT , int PIN , int State){
    switch(PORT){
           case PORT_A:
                RCC_AHB1ENR = (1 << PORT_A);
                if(State == INPUT){
                   CLR_BIT(GPIOA_MODER , 2*PIN);
                   CLR_BIT(GPIOA_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOA_MODER , 2*PIN);
                   CLR_BIT(GPIOA_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_B:
                RCC_AHB1ENR = (1 << PORT_B);
                if(State == INPUT){
                   CLR_BIT(GPIOB_MODER , 2*PIN);
                   CLR_BIT(GPIOB_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOB_MODER , 2*PIN);
                   CLR_BIT(GPIOB_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_C:
                RCC_AHB1ENR = (1 << PORT_C);
                if(State == INPUT){
                   CLR_BIT(GPIOC_MODER , 2*PIN);
                   CLR_BIT(GPIOC_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOC_MODER , 2*PIN);
                   CLR_BIT(GPIOC_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_D:
                RCC_AHB1ENR = (1 << PORT_D);
                if(State == INPUT){
                   CLR_BIT(GPIOD_MODER , 2*PIN);
                   CLR_BIT(GPIOD_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOD_MODER , 2*PIN);
                   CLR_BIT(GPIOD_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_E:
                RCC_AHB1ENR = (1 << PORT_E);
                if(State == INPUT){
                   CLR_BIT(GPIOE_MODER , 2*PIN);
                   CLR_BIT(GPIOE_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOE_MODER , 2*PIN);
                   CLR_BIT(GPIOE_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
          default:
                  break;

    }
}
/************************************************************
* @brief Writes a digital value (Logic) to the specified GPIO pin.
* @param PORT: Port identifier (e.g., PORT_A, PORT_B, etc.)
* @param PIN: Pin number
* @param Logic: Digital value to write (HIGH or LOW)
*************************************************************/
void GPIO_DigitalWrite(int PORT , int PIN , int Logic){
    switch(PORT){
           case PORT_A:
                if(Logic == HIGH) {
                   SET_BIT(GPIOA_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOA_ODR , PIN);
                }else{/*Nothing*/}
                break;

           case PORT_B:
                if(Logic == HIGH) {
                   SET_BIT(GPIOB_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOB_ODR , PIN);
                }else{/*Nothing*/}
                break;

           case PORT_C:
                if(Logic == HIGH) {
                   SET_BIT(GPIOC_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOC_ODR , PIN);
                }else{/*Nothing*/}
                break;

           case PORT_D:
                if(Logic == HIGH) {
                   SET_BIT(GPIOD_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOD_ODR , PIN);
                }else{/*Nothing*/}
                break;

           case PORT_E:
                if(Logic == HIGH) {
                   SET_BIT(GPIOE_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOE_ODR , PIN);
                }else{/*Nothing*/}
                break;

          default:
                  break;

    }
}
/************************************************************
 * @brief Reads the digital value from the specified GPIO pin.
 * @param PORT: Port identifier (e.g., PORT_A, PORT_B, etc.)
 * @param PIN: Pin number
 * @return: Digital value read from the pin (HIGH or LOW)
*************************************************************/
int GPIO_DigitalRead(int PORT , int PIN){
    switch(PORT){
           case PORT_A:
                return GET_BIT(GPIOA_IDR , PIN);
                break;
           case PORT_B:
                return GET_BIT(GPIOB_IDR , PIN);
                break;
           case PORT_C:
                return GET_BIT(GPIOC_IDR , PIN);
                break;
           case PORT_D:
                return GET_BIT(GPIOD_IDR , PIN);
                break;
           case PORT_E:
                return GET_BIT(GPIOE_IDR , PIN);
                break;

          default:
                  break;

    }
}

/*====================     Lab Example     ====================*/
/*
void main() {

GPIO_InitPin(PORT_A , 0 , INPUT);
GPIO_InitPin(PORT_A , 1 ,OUTPUT);
GPIO_InitPin(PORT_A , 2 ,OUTPUT);
GPIO_InitPin(PORT_A , 3 ,OUTPUT);
GPIO_InitPin(PORT_A , 4 ,OUTPUT);
GPIO_InitPin(PORT_A , 5 ,OUTPUT);
GPIO_InitPin(PORT_A , 6 ,OUTPUT);
GPIO_InitPin(PORT_A , 7 ,OUTPUT);
   while(1){
      {
          if(1 == GPIO_DigitalRead(PORT_A , 0))
           {
            GPIO_DigitalWrite(PORT_A , 1 , LOW);
            GPIO_DigitalWrite(PORT_A , 2 , LOW);
            GPIO_DigitalWrite(PORT_A , 3 , LOW);
            GPIO_DigitalWrite(PORT_A , 4 , LOW);
            GPIO_DigitalWrite(PORT_A , 5 , LOW);
            GPIO_DigitalWrite(PORT_A , 6 , LOW);
            GPIO_DigitalWrite(PORT_A , 7 , LOW);
            Delay_ms(1000);

            }else{
            GPIO_DigitalWrite(PORT_A , 1 , HIGH);
            GPIO_DigitalWrite(PORT_A , 2 , HIGH);
            GPIO_DigitalWrite(PORT_A , 3 , HIGH);
            GPIO_DigitalWrite(PORT_A , 4 , HIGH);
            GPIO_DigitalWrite(PORT_A , 5 , HIGH);
            GPIO_DigitalWrite(PORT_A , 6 , HIGH);
            GPIO_DigitalWrite(PORT_A , 7 , HIGH);
            Delay_ms(1000);
          }

      }

   }
}
*/

