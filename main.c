#include "stm32f303xc.h"

#define NbOfClick 5
void delay(void);


int main(void){
	int button_on;
	//dioda PE15
	RCC->AHBENR=RCC_AHBENR_GPIOEEN;//wlaczam zegar dla portu E
	GPIOE->MODER|=GPIO_MODER_MODER15_0;//tryb output
	
	//przycisk PA0
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;//wlaczam zegar dla portu A
	//tryb input (reset state)
	//przycisk jest w trybie pull down (hardware)
	
	while(1){
		button_on=0;
		delay();//opoznienie,aby ominac czas, w ktorym jest debouncing
		for(int i=0;i<NbOfClick;i++){//sprawdzam 30 razy czy przycisk zostal wcisniety
			if((GPIOA->IDR & GPIO_IDR_0)==1) button_on++;// sprawdzam czy na pinie PA0 jest stan wysoki	
			}
		if(button_on==NbOfClick){//jesli za kazdym razem byl wcisniety zmien stan na przeciwny
		//Sprawdzam jaki stan panuje na pinie PE15 zeby zmienic na przeciwny
			if(GPIOE->ODR & GPIO_ODR_15){
				GPIOE->ODR&=~GPIO_ODR_15;//jest stan wysoki-> zmieniam na niski
			}
			else{
			GPIOE->ODR|=GPIO_ODR_15;//jest stan niski-> zmieniam na wysoki
			}
			while((GPIOA->IDR & GPIO_IDR_0)==1);//czekaj dopoki uzytkownik nie zwolni przycisku
		}
		
		
}
	return 0;
}

void delay(void){
for(int i=0;i<0xFF00;i++);
}

