#include "stm32f3xx.h"                  // Device header
#include <stdbool.h>

//Check if Button was pushed
#define PushButtonCheck (GPIOA->IDR & GPIO_IDR_0)
//Toggle LED
#define ToggleLed (GPIOE->ODR^=GPIO_ODR_15)
/*
 Define frequency of blinking led
*/
#define LedBlink1 700// the lowest frequency
#define LedBlink2 500
#define LedBlink3 200

/*
 enum State is used for defining possible machine states 
*/
typedef enum{
	LowSpeed,
	MediumSpeed,
	HighSpeed,
  ButtonClick,
  ButtonRecognize
}State;

/*
	Struct MachineState is used to know which state is now
*/
typedef struct{
	State ActualState;
  State OldState;
}MachineState;
/*
	Button will be checked many times before it will be shown as pushed (defined by ButtonClick)
*/
#define ButtonClick 40
uint8_t ButtonState=0;

/*
	Variable to measure time 
*/
typedef struct{
	int time;
	int BlinkTime;
	bool Flag;
}MeasureTime;
MeasureTime TimeLed={0,LedBlink3,false};

// Min time which have to past to change Machine State 
#define Delay 60
/*
		Declaration of functions
*/
void UpdateMachineState(MachineState *ms);
void ButtonConfig();
void LedConfig();


int main(void){
  
  MachineState ms={HighSpeed,HighSpeed};
	
  SysTick_Config(SystemCoreClock / 1000);
  ButtonConfig();
  LedConfig();
while(1)
{
  if (PushButtonCheck) 
    {
      ms.ActualState=ButtonClick;
      UpdateMachineState(&ms);
    }
  if(ButtonState>ButtonClick) 
    {
      ms.ActualState=ButtonRecognize;
      UpdateMachineState(&ms);
    }
			
  if (TimeLed.time>Delay && TimeLed.Flag==true) 
    {
      ms.ActualState = ms.OldState;
      UpdateMachineState(&ms);//to avoid that one state is omitted, it's used delay time
    }
  if(TimeLed.time>TimeLed.BlinkTime)	
    {
      ToggleLed;
      TimeLed.time=0;
    }
			
}
		
}

void UpdateMachineState(MachineState *ms){
  
  switch(ms->ActualState) {
    case LowSpeed:
			ms->ActualState = MediumSpeed;
      ms->OldState= MediumSpeed;
			TimeLed.BlinkTime=LedBlink2;
      TimeLed.Flag=false;
        break;

    case MediumSpeed:
			ms->ActualState = HighSpeed;
      ms->OldState= HighSpeed;
			TimeLed.BlinkTime=LedBlink3;
      TimeLed.Flag=false;
        break;

    case HighSpeed:
			ms->ActualState = LowSpeed;
      ms->OldState= LowSpeed;
			TimeLed.BlinkTime=LedBlink1;
      TimeLed.Flag=false;
        break;
    case ButtonClick:
			ms->ActualState = ms->OldState;
      ButtonState++;
        break; 
    case ButtonRecognize:
      TimeLed.Flag=true;
      TimeLed.time=0;
      ButtonState=0;
        break;     
    }
}

void ButtonConfig(){
	//PA0 button
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;//enable clock for port A
	//tryb input (reset state)
	
}

void LedConfig(){
	//diode LED PE15
	RCC->AHBENR|=RCC_AHBENR_GPIOEEN;//enable clock for port E
	GPIOE->MODER|=GPIO_MODER_MODER15_0;//output

}
/*
	Interrupt from SysTick to measure time. It's happened every 1 ms
*/
void SysTick_Handler(){
	(TimeLed.time)++;
}