/************************************************************
* @Author : AhmedSamy
* @File: TIMER2_PWM.c
* @Platform(MCU) : STM32F407VG
* @Date : 12-11-2023
*************************************************************/


#define TIM2_CCMR1   (*((unsigned long volatile *)(0x40000018) ) )

#define SET_BIT(REG , PIN)      (REG |= (1 << PIN))
#define CLR_BIT(REG , PIN)      (REG &= ~(1 << PIN))
#define GET_BIT(REG , PIN)      ((REG >> PIN) & (0X01))

void TIMER2_Initialization(void);
void TIMER2_DelayMs(int ms);
void TIMER2_PWM(int Carrier , int Reference);

void main() {
     /*Enable PORTA*/
     SET_BIT(RCC_AHB1ENR , 0);
     /*PA0 as @Alternate Function mode PIN*/
     CLR_BIT(GPIOA_MODER, 2* 0);
     SET_BIT(GPIOA_MODER, 2* 0 +1);
     /*PA0 as @Alternate LOW PIN*/
     SET_BIT(GPIOA_AFRL , 0);
     
     TIMER2_Initialization();
     TIMER2_PWM(1000 , 100);
}

void TIMER2_Initialization(void){
     /*Initialization Timer2*/
     SET_BIT(RCC_APB1ENR , 0);
     /*Prescaler*/
     TIM2_PSC = 15;
     /*Edge Aligned Mode*/
     CLR_BIT(TIM2_CR1 , 6);
     CLR_BIT(TIM2_CR1 , 5);
     /*Upcounter*/
     CLR_BIT(TIM2_CR1 , 4);
     /*Register is Buffered*/
     SET_BIT(TIM2_CR1 , 7);

}

void TIMER2_PWM(int Carrier , int Reference){

     /*Set Channel 1*/
     SET_BIT(TIM2_CCER ,0);
     /** PWM MODE : TIM2_CCMR1 <6:4> = 110 **/
     CLR_BIT(TIM2_CCMR1 , 4);
     SET_BIT(TIM2_CCMR1 , 5);
     SET_BIT(TIM2_CCMR1 , 6);
     
     /*Carrier*/
     TIM2_ARR = Carrier;
     /*Reference Duty Cycle = 50%*/
     TIM2_CCR1 = Reference;
     /*UG - Reinit The Counter*/
     SET_BIT(TIM2_EGR , 0);
     /*Start Count*/
     SET_BIT(TIM2_CR1 , 0);
}




void TIMER2_DelayMs(int ms){
     TIM2_ARR = ms;
     /*UG - Reinit The Counter*/
     SET_BIT(TIM2_EGR , 0);
     /*Clear The Interrupt Flag*/
     CLR_BIT(TIM2_SR , 0);
     /*Start Count*/
     SET_BIT(TIM2_CR1 , 0);

     /*Polling til the Flag is Rised*/
     while(!GET_BIT(TIM2_SR , 0));

     /*Stop Count*/
     CLR_BIT(TIM2_CR1 , 0);
     /*Clear The Interrupt Flag*/
     CLR_BIT(TIM2_SR , 0);
}
