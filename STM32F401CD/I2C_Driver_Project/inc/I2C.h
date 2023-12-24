/************************************************************
* @Author : AhmedSamy
* @File: I2C.h
* @Platform(MCU) : STM32F401CD
* @Date : 19-12-2023
*************************************************************/

#ifndef I2C_H
#define I2C_H

/*============         Section : Includes        ============*/
 #include "GPIO.h"


/*============     Section: Macro Declarations   ============*/

/*============       User Configurations         ============*/
#define OWN_ADDRESS            0x04



/*============        Registers Mapping         ============*/
/*RCC APB1 peripheral clock enable register*/ 

#define RCC_APB1ENR   (*((unsigned long volatile *)(0x40023840) ) )

#define I2C1_CR1      (*((unsigned long volatile *)(0x40005400) ) )

#define I2C1_OAR1     (*((unsigned long volatile *)(0x40005408) ) )

#define I2C1_OAR2     (*((unsigned long volatile *)(0x4000540C) ) )

#define I2C1_DR       (*((unsigned long volatile *)(0x40005410) ) )

#define I2C1_SR1      (*((unsigned long volatile *)(0x40005414) ) )

#define I2C1_SR2      (*((unsigned long volatile *)(0x40005418) ) )

#define I2C1_CCR      (*((unsigned long volatile *)(0x4000541C) ) )

#define I2C1_TRISE    (*((unsigned long volatile *)(0x40005420) ) )

#define I2C1_FLTR     (*((unsigned long volatile *)(0x40005424) ) )

#define I2C1_FLTR_OFFSET       0x24

#define I2C1_FLTR_PTR  (*(volatile byte*)(I2C1_Base + I2C1_FLTR_OFFSET))

/* ------------- Section: Data Type Declarations ------------- */
typedef unsigned char        uint8_t;
typedef unsigned int         uint16_t;
typedef unsigned long        uint32_t;

/* ------------- Section: Macro Functions Declarations ------------- */

/**
• I2C1 (PB6/PB7) • I2C2 (PB10/PB3) • I2C3 (PA8/PB4)
*/

/* peripheral clock enable to Configure @I2C1*/
#define RCC_EN_I2C1_PERIPHRAL()         (SET_BIT(RCC_APB1ENR , 21))
/*Enable Port B to Configure @I2C1*/
#define RCC_EN_I2C1_PORT()              (RCC_AHB1ENR |= (1 << PORT_B))
#define I2C1_GPIO_ALTERNATE()             (GPIOB_MODER |=  (1<<13) | (1<<15) )
/*AF4(I2C1..3)*/
#define I2C1_GPIO_ALTERNATE_FUNCTION()    (GPIOB_AFRL |=  (1<<30) | (1<<26) )

/* peripheral clock enable to Configure @I2C2*/
#define RCC_EN_I2C2_PERIPHRAL()         (SET_BIT(RCC_APB1ENR , 22))
/*Enable Port B to Configure @I2C2*/
#define RCC_EN_I2C2_PORT()              (RCC_AHB1ENR = (1 << PORT_B) )
#define GPIO_ALTERNATE_I2C2             (GPIOB_MODER |=  (1<<19) | (1<<21) )

/* peripheral clock enable to Configure @I2C3*/
#define RCC_EN_I2C3_PERIPHRAL()         (SET_BIT(RCC_APB1ENR , 23))
/*Enable Port B Clock to Configure @I2C3*/
#define RCC_EN_I2C3_PORT()              (RCC_AHB1ENR = (1 << PORT_B) | (1 << PORT_A) )


/* ------------- Section: Function Declarations -------------*/

void I2C1_init_begin();
void I2C1_Master_Init(uint8_t Address);
void I2C1_Slave_Init(uint8_t ownAddress);
void I2C1_Write(uint8_t Data);
void onReceive(void (*function)(void));
void onRequest(void (*function)(void));
void setClock(uint8_t freq);
uint8_t available(void);
uint8_t I2C1_Read();
void beginTransmission(int address);
void I2C1_endTransmission(void);
void I2C1_end(void);
void requestFrom(uint8_t address, uint8_t quantity, uint8_t array[], uint8_t size);
void I2C1_enableNoiseFilter(uint8_t DNF);


#endif // I2C_H
