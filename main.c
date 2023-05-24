#include "stm32f3xx.h"                  // Device header

void clock_config(void);
static uint32_t msTicks;

void delay_ms(uint32_t ms);
int main(void){
	clock_config();
  SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	//taktowanie 72Mhz
	//dioda PE15
	RCC->AHBENR=RCC_AHBENR_GPIOEEN;//wlaczam zegar dla portu E
	GPIOE->MODER|=GPIO_MODER_MODER15_0;//tryb output
	//GPIOE->OSPEEDR&=~GPIO_OSPEEDER_OSPEEDR15;
		
	while(1){
		GPIOE->ODR^=GPIO_ODR_15;//jest stan wysoki-> zmieniam na niski
		delay_ms(3000);
}
	return 0;
}

void SysTick_Handler(){//przerwanie od SysTickTimer jest wywolywane co 1ms
	if(msTicks!=0){
     msTicks--;	
	}
}

void clock_config(void){
	// Wlacz HSE (High Speed External) oscylator// HSEBYP- bypass zegar jako kwarc
RCC->AHBENR=RCC_AHBENR_GPIOFEN;//wlaczam zegar dla portu F
	
RCC->CR |= RCC_CR_HSEBYP;
RCC->CR |= RCC_CR_HSEON;
	
// Czekaj, az HSE oscylator jest gotowy
while (!(RCC->CR & RCC_CR_HSERDY));

	
RCC->CFGR|=RCC_CFGR_PLLMUL9|RCC_CFGR_PPRE1_DIV2|RCC_CFGR_PLLSRC_HSE_PREDIV;//ustawia SYSCLK na 72Mhz, APB1 na 36MHz,zegar PLL jako HSE 
RCC->CR |= RCC_CR_PLLON;//wlaczenie petli PLL
while(!(RCC->CR & RCC_CR_PLLRDY));//sprawdzanie czy PLL jest gotowe  

FLASH->ACR|=FLASH_ACR_LATENCY_2;//48MHz<HCLK<=72MHz 
RCC->CFGR |= RCC_CFGR_SW_PLL;//zegar SYSCLK jako PLL_CLK czyli HSE*9=72MHz
while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);//petla wykonuje sie dopoki zegar nie jest ustawiony na PLL
//while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);//petla wykonuje sie dopoki zegar nie jest ustawiony na HSI
 
}

void delay_ms(uint32_t ms){
	msTicks=ms;
	while(msTicks);
}
