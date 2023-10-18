#include<LPC17xx.h>
void EINT3_IRQHandler(void);
unsigned char int3_flag=0;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL4 |= 0x04000000;	//P2.13 as EINT3 and P2.12-GPIO for LED1
	LPC_PINCON->PINSEL4 &= 0xFCFFFFFF;
	LPC_GPIO2->FIODIR = 0x00001000;		
	LPC_GPIO2->FIOSET = 0x00001000;	
	LPC_SC->EXTINT = 0x00000008;		 //Enable external interrupt 3
	LPC_SC->EXTMODE = 0x00000008;		 //Edge senitive
	LPC_SC->EXTPOLAR = 0x00000000;	 //Falling edge sensitive
	NVIC_EnableIRQ(EINT3_IRQn);			
	while(1);
 }
void EINT3_IRQHandler(void)
{
	LPC_SC->EXTINT = 0x00000008;	//cleares the interrupt
	if(int3_flag == 0x00)				//when flag is '0' off the LED
	{
		LPC_GPIO2->FIOCLR = 0x00001000;
		int3_flag = 0xFF;
	}							
	else                       //when flag is FF on the LED
	{
		LPC_GPIO2->FIOSET = 0x00001000;
		int3_flag = 0x00;
	}
}
