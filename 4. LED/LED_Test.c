#include<LPC17xx.h>
#include<stdio.h>
#define LED_TOGGLE (1<<7)							//7th bit is made high
unsigned int delay(int);
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL4 = 0x00000000;	 //P2 is made as GPIO
	LPC_GPIO2->FIODIR = 0x000000080;		 //P2.7 is output
	LPC_GPIO2->FIOCLR = 0x000000080;	 //Clear the P2.7 bit
	while(1)
	{
		LPC_GPIO2->FIOSET = LED_TOGGLE;					
		delay(100000);				
		LPC_GPIO2->FIOCLR =  LED_TOGGLE;					
		delay(100000);					
	}
}
unsigned int delay(int r1)
{
	int r2	;
	for(r2=0;r2<r1;r2++);
	return 0;
}
