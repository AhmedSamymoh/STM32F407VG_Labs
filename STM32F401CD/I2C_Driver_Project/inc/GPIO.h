/************************************************************
* @Author : AhmedSamy
* @File: GPIO.h
* @Platform(MCU) : STM32F401CD
* @Date : 17-12-2023
*************************************************************/
#ifndef GPIO_H
#define GPIO_H


#define         SET_BIT(REG , BIT)      (REG |= ( 1 << BIT ))
#define         CLR_BIT(REG , BIT)      (REG &= ~( 1 << BIT ))
#define         GET_BIT(REG , BIT)      ((REG >> BIT) & 0x01)

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

/* RCC Clock Register */
#define RCC_AHB1ENR   (*((unsigned long volatile *)(0x40023830) ) )

/*--------- Port_A I/O Registers -----*/
#define GPIOA_MODER   (*((unsigned long volatile *)(0x40020000) ) )
#define GPIOA_ODR     (*((unsigned long volatile *)(0x40020014) ) )
#define GPIOA_IDR     (*((unsigned long volatile *)(0x40020010) ) )

/*--------- Port_B I/O Registers -----*/
#define GPIOB_MODER   (*((unsigned long volatile *)(0x40020400) ) )
#define GPIOB_IDR     (*((unsigned long volatile *)(0x40020410) ) )
#define GPIOB_ODR     (*((unsigned long volatile *)(0x40020414) ) )

/*--------- Port_C I/O Registers -----*/
#define GPIOC_MODER   (*((unsigned long volatile *)(0x40020800) ) )
#define GPIOC_IDR     (*((unsigned long volatile *)(0x40020810) ) )
#define GPIOC_ODR     (*((unsigned long volatile *)(0x40020814) ) )

/*--------- Port_D I/O Registers -----*/
#define GPIOD_MODER   (*((unsigned long volatile *)(0x40020C00) ) )
#define GPIOD_IDR     (*((unsigned long volatile *)(0x40020C10) ) )
#define GPIOD_ODR     (*((unsigned long volatile *)(0x40020C14) ) )

/*--------- Port_E I/O Registers -----*/
#define GPIOE_MODER   (*((unsigned long volatile *)(0x40021000) ) )
#define GPIOE_IDR     (*((unsigned long volatile *)(0x40021010) ) )
#define GPIOE_ODR     (*((unsigned long volatile *)(0x40021014) ) )


void GPIO_InitPin(int PORT , int PIN , int State);

int GPIO_DigitalRead(int PORT , int PIN);

void GPIO_DigitalWrite(int PORT , int PIN , int Logic);

#endif // GPIO_H