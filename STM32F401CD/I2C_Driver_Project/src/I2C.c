/************************************************************
* @Author : AhmedSamy
* @File: I2C.c
* @Platform(MCU) : STM32F401CD
* @Date : 19-12-2023
*************************************************************/
#include "I2C.h"
/*ADDRESS_CONFIG = -1 FOR MASKER Neither FOR Slave*/
char ADDRESS_CONFIG = -1;
uint16_t temp;

void I2C1_init_begin(){
     /* peripheral clock enable to Configure @I2C1*/
      RCC_EN_I2C1_PERIPHRAL();
      /*Enable Port B to Configure @I2C1*/
      RCC_EN_I2C1_PORT();
      /*Configure the Alternate pin to be AF4 For I2C Peripheral*/
      I2C1_GPIO_ALTERNATE();
      I2C1_GPIO_ALTERNATE_FUNCTION();
      
      /*set ch 6 & 7 as pull up*/
      GPIOB_PUPDR |= ( (1<<12) | (1<<14) );
      /*set ch 6 & 7 as open drain */
      GPIOB_OTYPER|= ( (1<<6) | (1<<7) );
      
      /*Disable I2CPeripheral <Bit 0 PE>*/
      SET_BIT(I2C1_CR1,0);
      
      /*Addressing 7 Bit mode <BIT 15 ADDMODE>*/
      CLR_BIT(I2C1_OAR1, 15);

      
    /* Master Configuration (Assuming ADDRESS_CONFIG is -1 for master) */
    if (ADDRESS_CONFIG == -1) {
        I2C1_Master_Init(OWN_ADDRESS);
    }
    /* Slave Configuration */
    else {
        // You can add slave-specific configuration here if needed
        I2C1_Slave_Init((uint8_t)OWN_ADDRESS);
    }

}
void I2C1_Master_Init(uint8_t Address){
     uint32_t ccr_value ;
     uint8_t read_sr = 0;
    /*
    * Set the clock frequency in the CR2 register (Fast Mode, 400 kHz)
    * Formula: (PCLK1 / (2 * CCR_value))
    * In this case, CCR_value = PCLK1 / (2 * 400000)
    * Fm mode:             PCLK1 = 45MHz
    *    DUTY = 1: (to reach 400 kHz)
    *    Thigh = 9 * CCR * TPCLK1
    *    Tlow = 16 * CCR * TPCLK1
    */


    /* Set Peripheral Clock frequency (APB1 = 45 MHz) in CR2 register */
    I2C1_CR2 |= (1 << 0) | (1 << 2) | (1 << 3) | (1 << 5);

    /*Fast Mode Select <Bit 15 F/S>*/
    SET_BIT(I2C1_CCR ,15);
    
    /*1: Fm mode Tlow/Thigh = 16/9 (see CCR) <Bit 14 DUTY> */
    SET_BIT(I2C1_CCR ,14);
    
    ccr_value = (uint16_t)5u;
    I2C1_CCR |= ccr_value;

    /* Set the Rise Time register*/
    I2C1_TRISE |= (uint8_t)14u;
    
    
    /* Enable the ACK*/
    SET_BIT(I2C1_CR1 , 10);
    /* Generate START   */
    SET_BIT(I2C1_CR1 , 8);

    /* Polling until SB bit to be set*/
    while (!(I2C1_SR1 & (1<<0)));

    /*Send the Slave Address to the DR Register */
    I2C1_DR = Address;  
    while (!(I2C1_SR1 & (1<<1)));
    /* read SR1 and SR2 to clear the ADDR bit*/
    read_sr = I2C1_SR1 | I2C1_SR2;
    
    /* Enable I2C Peripheral <Bit 0 PE> */
    SET_BIT(I2C1_CR1, 0);

}

void I2C1_Slave_Init(uint8_t ownAddress){
    /*Set the slave address in OAR1 register */
    I2C1_OAR1 = (ownAddress << 1) | (1 << 14);  // 7-bit addressing
    
    /* Set Peripheral Clock frequency (APB1 = 45 MHz) in CR2 register */
    I2C1_CR2 |= (1 << 0) | (1 << 2) | (1 << 3) | (1 << 5);

    /* Enable I2C Peripheral <Bit 0 PE> */
    SET_BIT(I2C1_CR1, 0);

    /* Enable Acknowledgment  <Bit 10 ACK> */
    SET_BIT(I2C1_CR1, 10);
    

}

void I2C1_Write(uint8_t Data)
{
     /* Polling for TXE bit to set*/
     while (!(I2C1_SR1 & (1<<7)));
     CLR_BIT(I2C1_CR1, 8);
     /*Write Data to be sent in Data Register*/
     I2C1_DR = (uint8_t)Data;
     /*Polling while BTF=0 but when BTF=1; Data byte transfer succeeded*/
     while (!(I2C1_SR1 & (1<<2)));

}

uint8_t I2C1_Read(){
    uint8_t read_sr = 0, DataReceived = 0;
    
    /* clear the ACK bit*/
    CLR_BIT(I2C1_CR1,10);
    
    /* read SR1 and SR2 to clear the ADDR bit*/
    read_sr = I2C1_SR1 | (I2C1_SR2 << 8);
    
    /* Stop I2C*/
    SET_BIT(I2C1_CR1 , 9);
   
    /* wait for RxNE to set*/
    while (!(I2C1_SR1 & (1<<6)));
    
    /* Read the data from the DATA REGISTER*/
    DataReceived = I2C1_DR;
        
    return DataReceived;
 }
 
void requestFrom(uint8_t address, uint8_t quantity, uint8_t array[], uint8_t size)
{
     uint32_t temp;
     uint8_t i = 0;
     
    /* Generate START condition */
    SET_BIT(I2C1_CR1, 8); // Start bit

    /* Wait for the START bit to be set */
    while (!(I2C1_SR1 & (1 << 0)));

    /* Send slave address with read bit (1) */
    I2C1_DR = (address << 1) | 1; // Address with read bit
    while (!(I2C1_SR1 & (1 << 1))); // Wait for ADDR bit

    /* Clear ADDR by reading SR1 */
    temp = I2C1_SR1;

    /* Disable ACK after the first byte to be received */
    if (quantity == 1)
    {
        CLR_BIT(I2C1_CR1, 10); // Disable ACK
    }

    /* Receive data bytes */
    for ( i = 0; i < size - 1; i++)
    {
        while (!(I2C1_SR1 & (1 << 2))); // Wait for BTF
        CLR_BIT(I2C1_CR1, 10); // Disable ACK
        array[i] = I2C1_DR; // Read data byte
    }

    /* Wait for the last byte */
    while (!(I2C1_SR1 & (1 << 2))); // Wait for BTF
    SET_BIT(I2C1_CR1, 9); // Generate STOP condition
    array[size - 1] = I2C1_DR; // Read the last byte
}

void beginTransmission(int address)
{
     uint32_t temp;
    
    /* Start condition */
    I2C1_CR1 |= (1 << 8); // Start condition

    /* Wait till SB == 1 */
    while (!(I2C1_SR1 & (1 << 0)));

    /* Read SR1 */
    temp = I2C1_SR1;

    /* Send slave address */
    I2C1_DR |= (address << 0);

    /* Wait till ADDR == 1 */
    while (!(I2C1_SR1 & (1 << 1)));

    /* Read SR1 & SR2 to clear ADDR */
    temp = I2C1_SR1;
    temp = I2C1_SR2;
}

void I2C1_endTransmission(void){
       /*stop generation */
      I2C1_CR1 |= (1<<9);      
      
      /* Polling until the STOP condition to be sent as
      it Cleared by hardware after detecting a Stop condition on the bus*/
      while (I2C1_SR2 & (1<<0)); //

      /* Clear the STOP bit*/
      CLR_BIT(I2C1_CR1,9);
}
void I2C1_end(void)
{
 /*Disable I2C Peripheral clk*/
 CLR_BIT(RCC_APB1ENR , 21);
}

void onReceive(void (*function)(void))
{
  uint8_t receivedData;
  /* Set the handler pointer to the given function and execute it */
  void (*handler)(void) = function;
  /* Wait until ADDR == 1 and RxNE == 1 (Start condition detected) */
  while (!(I2C1_SR1 & (1 << 1)) & !(I2C1_SR1 & (1 << 6)));


  handler();

  /* Read data from the Data Register (DR) */
  receivedData = (uint8_t)I2C1_DR;

  /* Generate STOP condition */
  I2C1_CR1 |= (1 << 9);
}

void onRequest(void (*function)(void))
{
     uint16_t temp;
     /* Set the handler pointer to the given function and execute it */
     void (*handler)(void) = function;
    /* Wait for ADDR bit (Address matched) and Tx bit (Transmitter mode) to be set */
    while (!(I2C1_SR1 & (1 << 1)) && !(I2C1_SR1 & (1 << 7)));

    /* Set the function pointer to the provided function */
    handler = function;

    /* Execute the provided function */
    handler();

    /* Read DR register */
    temp = I2C1_DR;

    /* Generate STOP condition */
    I2C1_CR1 |= (1 << 9);
}

/* Check if data is available in the receive buffer */
uint8_t available(void)
{
    /* Check if RxNE (Receive buffer not empty) bit is set */
    if (I2C1_SR1 & (1 << 6))
    {
        return 1; // Data is available
    }
    else
    {
        return 0; // No data available
    }
}

/* Set the clock frequency for I2C communication */
void setClock(uint8_t freq)
{
    /* Set the frequency in CR2 register */
    I2C1_CR2 |= (freq << 0);
}

void I2C1_enableNoiseFilter(uint8_t DNF){
     /*it 4 ANOFF: Analog noise filter OFF
     0: Analog noise filter enable*/
     CLR_BIT(I2C1_FLTR,4);
     /*Bits 3:0 DNF[3:0]: Digital noise filter*/
     I2C1_FLTR |= DNF;
}
