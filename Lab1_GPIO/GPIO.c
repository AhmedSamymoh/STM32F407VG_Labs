/************************************************************
* @Author : AhmedSamy 
* @File: GPIO.c
* @Platform(MCU) : STM32F407VG
* @Date : 29-10-2023
*************************************************************/


#define         SET_BIT(REG , BIT)      (REG |= ( 1 << BIT ))
#define         CLR_BIT(REG , BIT)      (REG &= ~( 1 << BIT ))
#define         GET_BIT(REG , BIT)      ((REG >> BIT) & 1)

#define  PORT_A      0
#define  PORT_B      1
#define  PORT_C      2
#define  PORT_D      3
#define  PORT_E      4
#define  PORT_F      5

#define OUTPUT    1
#define INPUT    0

#define HIGH    1
#define LOW    0

int GPIO_DigitalRead(int PORT , int PIN);
void GPIO_DigitalWrite(int PORT , int PIN , int Logic);
void GPIO_InitPin(int PORT , int PIN , int State);

void main() {

GPIO_InitPin(PORT_D , 0 , INPUT);
GPIO_InitPin(PORT_D , 1 ,OUTPUT);
GPIO_InitPin(PORT_D , 2 ,OUTPUT);
GPIO_InitPin(PORT_D , 3 ,OUTPUT);
GPIO_InitPin(PORT_D , 4 ,OUTPUT);
GPIO_InitPin(PORT_D , 5 ,OUTPUT);
GPIO_InitPin(PORT_D , 6 ,OUTPUT);
GPIO_InitPin(PORT_D , 7 ,OUTPUT);

   while(1){
        if(1 == GPIO_DigitalRead(PORT_D , 0)) {
            GPIO_DigitalWrite(PORT_D , 1 , LOW);
            GPIO_DigitalWrite(PORT_D , 2 , LOW);
            GPIO_DigitalWrite(PORT_D , 3 , LOW);
            GPIO_DigitalWrite(PORT_D , 4 , LOW);
            GPIO_DigitalWrite(PORT_D , 5 , LOW);
            GPIO_DigitalWrite(PORT_D , 6 , LOW);
            GPIO_DigitalWrite(PORT_D , 7 , LOW);
            Delay_ms(1000);
             GPIO_DigitalWrite(PORT_D , 1 , HIGH);
            GPIO_DigitalWrite(PORT_D , 2 , HIGH);
            GPIO_DigitalWrite(PORT_D , 3 , HIGH);
            GPIO_DigitalWrite(PORT_D , 4 , HIGH);
            GPIO_DigitalWrite(PORT_D , 5 , HIGH);
            GPIO_DigitalWrite(PORT_D , 6 , HIGH);
            GPIO_DigitalWrite(PORT_D , 7 , HIGH);
            Delay_ms(1000);

        }

   }
}

void GPIO_InitPin(int PORT , int PIN , int State){
    switch(PORT){
           case PORT_A:
                RCC_AHB1ENR = (1 << A);
                if(State == INPUT){
                   SET_BIT(GPIOA_MODER , 2*PIN);
                   CLR_BIT(GPIOA_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOA_MODER , 2*PIN);
                   CLR_BIT(GPIOA_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_B:
                RCC_AHB1ENR = (1 << B);
                if(State == INPUT){
                   SET_BIT(GPIOB_MODER , 2*PIN);
                   CLR_BIT(GPIOB_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOB_MODER , 2*PIN);
                   CLR_BIT(GPIOB_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_C:
                RCC_AHB1ENR = (1 << C);
                if(State == INPUT){
                   SET_BIT(GPIOC_MODER , 2*PIN);
                   CLR_BIT(GPIOC_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOC_MODER , 2*PIN);
                   CLR_BIT(GPIOC_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_D:
                RCC_AHB1ENR = (1 << D);
                if(State == INPUT){
                   SET_BIT(GPIOD_MODER , 2*PIN);
                   CLR_BIT(GPIOD_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOD_MODER , 2*PIN);
                   CLR_BIT(GPIOD_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
           case PORT_E:
                RCC_AHB1ENR = (1 << E);
                if(State == INPUT){
                   SET_BIT(GPIOE_MODER , 2*PIN);
                   CLR_BIT(GPIOE_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOE_MODER , 2*PIN);
                   CLR_BIT(GPIOE_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
          case PORT_F:
                RCC_AHB1ENR = (1 << F);
                if(State == INPUT){
                   SET_BIT(GPIOF_MODER , 2*PIN);
                   CLR_BIT(GPIOF_MODER , 2*PIN+1);
                }else if (State == OUTPUT){
                   SET_BIT(GPIOF_MODER , 2*PIN);
                   CLR_BIT(GPIOF_MODER , 2*PIN+1);
                }else{/*Nothing*/}
                break;
          default:
                  break;

    }
}

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
                break;
           case PORT_D:
                if(Logic == HIGH) {
                   SET_BIT(GPIOD_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOD_ODR , PIN);
                }else{/*Nothing*/}
                break;
                break;
           case PORT_E:
                if(Logic == HIGH) {
                   SET_BIT(GPIOE_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOE_ODR , PIN);
                }else{/*Nothing*/}
                break;
                break;
          case PORT_F:
                if(Logic == HIGH) {
                   SET_BIT(GPIOF_ODR , PIN);
                }
                else if(Logic == LOW){
                   CLR_BIT(GPIOF_ODR , PIN);
                }else{/*Nothing*/}
                break;
                break;
          default:
                  break;

    }
}

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
          case PORT_F:
                return GET_BIT(GPIOF_IDR , PIN);
                break;
          default:
                  break;

    }
}




