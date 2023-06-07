#include "stm32f3xx.h"                  // Device header


void button_config(void);
void timer1_config(void);
void timer2_config(void);
void timer16_config(void);
int main(void){

	button_config();
	timer1_config();
	timer2_config();
	timer16_config();
  while(1){}
}	
void button_config(void){
	//dioda LED PE15
	RCC->AHBENR|=RCC_AHBENR_GPIOEEN;//wlaczam zegar dla portu E
	GPIOE->MODER|=GPIO_MODER_MODER15_0;//tryb output
	//dioda LED PE14
	GPIOE->MODER|=GPIO_MODER_MODER14_0;//tryb output
	//dioda LED PE13
	GPIOE->MODER|=GPIO_MODER_MODER13_0;//tryb output
	//dioda LED PE12
		GPIOE->MODER|=GPIO_MODER_MODER12_0;//tryb output
	//PA0 przycisk
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;//wlaczam zegar dla portu A
	//tryb input (reset state)
	//przycisk jest no pull up no pull down, ale hardware trybie pull down 
	//GPIOA->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR0_0|GPIO_OSPEEDER_OSPEEDR0_1;
	
	RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN;//wlaczam zegar dla SYSCFG
	//EXTI0 domyslnie jako PA0
	
	//konfiguracja przerwania
	 EXTI->RTSR|=EXTI_RTSR_TR0;//przerwanie za zbocze narastajace
	 NVIC_SetPriority(EXTI0_IRQn,1);
	 EXTI->IMR |= EXTI_IMR_MR0;//przerwanie jest  niemaskowalne
	 NVIC_EnableIRQ(EXTI0_IRQn);
	
}
void timer1_config(void){
 //przerwanie co 200ms//5Hz
	RCC->APB2ENR|=RCC_APB2ENR_TIM1EN;//wlaczam zegar dla Timer1
	//reset state upcounting mode DIR=0; UDIS=0 UEV interrupt jest aktywowane 
	TIM1->EGR|=TIM_EGR_UG;//po przepelnieniu timer zaczyna liczyc od zera dla trybu upcounting
	TIM1->CR1|=TIM_CR1_URS;//ustawia ze przerwanie jest wyzwalane tylko przez przepelnienie/wyzerowanie licznika 
	//f_timer=f_clock/(ARR+1)(PSC+1)(CKD+1)// f_clock=8Mhz
	TIM1->ARR=9999;
	TIM1->PSC=159;
	TIM1->SR&=~TIM_SR_UIF;//czyszcze flge update interrupt flag tak na wszelki wypadek
	TIM1->DIER |= TIM_DIER_UIE;// Update interrupt enabled
	TIM1->CR1|=TIM_CR1_ARPE;//TIMx_ARR register is buffered
	//konfiguracja przerwania
	NVIC_SetPriority(TIM1_UP_TIM16_IRQn,1);
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
	
	TIM1->CR1|=TIM_CR1_CEN;//Counter enabled
}
void timer2_config(){
//przerwanie co 700ms//ok. 1.43Hz
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;//wlaczam zegar dla Timer2
	//reset state upcounting mode DIR=0; UDIS=0 UEV interrupt jest aktywowane 
	TIM2->EGR|=TIM_EGR_UG;//po przepelnieniu timer zaczyna liczyc od zera dla trybu upcounting
	TIM2->CR1|=TIM_CR1_URS;//ustawia ze przerwanie jest wyzwalane tylko przez przepelnienie/wyzerowanie licznika 
	//t_timer=t_clock*((ARR+1)(PSC+1)(CKD+1))// f_clock=8Mhz t_clock=0,125us
	TIM2->ARR=9999;
	TIM2->PSC=559;
	TIM2->SR&=~TIM_SR_UIF;//czyszcze flge update interrupt flag tak na wszelki wypadek
	TIM2->DIER |= TIM_DIER_UIE;// Update interrupt enabled
	TIM2->CR1|=TIM_CR1_ARPE;//TIMx_ARR register is buffered
	//konfiguracja przerwania
	NVIC_SetPriority(TIM2_IRQn,1);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM2->CR1|=TIM_CR1_CEN;//Counter enabled
}
void timer16_config(){
//przerwanie co 1500ms
	RCC->APB2ENR|=RCC_APB2ENR_TIM16EN;//wlaczam zegar dla Timer16
	//reset state upcounting mode DIR=0; UDIS=0 UEV interrupt jest aktywowane 
	TIM16->EGR|=TIM_EGR_UG;//po przepelnieniu timer zaczyna liczyc od zera dla trybu upcounting
	TIM16->CR1|=TIM_CR1_URS;//ustawia ze przerwanie jest wyzwalane tylko przez przepelnienie/wyzerowanie licznika 
	//f_timer=f_clock/(ARR+1)(PSC+1)(CKD+1)// f_clock=8Mhz
	TIM16->ARR=9999;
	TIM16->PSC=1199;
	TIM16->SR&=~TIM_SR_UIF;//czyszcze flge update interrupt flag tak na wszelki wypadek
	TIM16->DIER |= TIM_DIER_UIE;// Update interrupt enabled
	TIM16->CR1|=TIM_CR1_ARPE;//TIMx_ARR register is buffered
	TIM16->CR1|=TIM_CR1_CEN;//Counter enabled
}

 void EXTI0_IRQHandler(){
	 if((EXTI->PR & EXTI_PR_PR0)){
	  GPIOE->ODR^=GPIO_ODR_15;//jest stan wysoki-> zmieniam na niski
		 EXTI->PR|=EXTI_PR_PR0; //czyszcze flage przerwania
	 }
 
 }
 void TIM1_UP_TIM16_IRQHandler() {
 if(TIM1->SR & TIM_SR_UIF){
  GPIOE->ODR^=GPIO_ODR_14;//jest stan wysoki-> zmieniam na niski
	TIM1->SR&=~TIM_SR_UIF;//czyszcze flge update interrupt flag 
 }
	if(TIM16->SR & TIM_SR_UIF){
  GPIOE->ODR^=GPIO_ODR_12;//jest stan wysoki-> zmieniam na niski
	TIM16->SR&=~TIM_SR_UIF;//czyszcze flge update interrupt flag  
 }
 }
 void TIM2_IRQHandler(){
 if(TIM2->SR & TIM_SR_UIF){
  GPIOE->ODR^=GPIO_ODR_13;//jest stan wysoki-> zmieniam na niski
	TIM2->SR&=~TIM_SR_UIF;//czyszcze flge update interrupt flag 
 }
 }