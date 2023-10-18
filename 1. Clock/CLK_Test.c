#include <LPC17xx.h>
#include <stdio.h>

int main(void)
{
	while(1)
	{
		LPC_PINCON->PINSEL3 &= ~0x00C00000;	
		LPC_PINCON->PINSEL3 |= 0x00400000;	//clkout pin as P1.27
		LPC_SC->CLKOUTCFG = 0x00000131;		//main oscillator clock source, divide by 4, enable the clkout
	}
 }
