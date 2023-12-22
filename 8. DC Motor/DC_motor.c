#include <lpc17xx.h>
unsigned int i;
void delay(unsigned int r1)
{
	unsigned int r;
	for (r=0;r<r1;r++);
}
void clk()
{
	LPC_GPIO0->FIOSET=1<<24;
	LPC_GPIO0->FIOCLR=1<<25;
}

void anticlk()
{
	LPC_GPIO0->FIOCLR=1<<24;
	LPC_GPIO0->FIOSET=1<<25;
}
void stop()
{
	LPC_GPIO0->FIOSET=1<<24;
	LPC_GPIO0->FIOSET=1<<25;
}
int main()
{
	LPC_PINCON->PINSEL1=0x00000000;	
	LPC_GPIO0->FIODIR=(1<<24) | (1<<25);		 //Configure as output
	LPC_GPIO0->FIOCLR=(1<<24) | (1<<25);		 //Clear

	while(1)
	{
		for (i=0;i<50;i++)
			clk();
		delay(65000);
		for (i=0;i<50;i++)
			stop();
		delay(65000);
		for (i=0;i<50;i++)
			anticlk();
		delay(65000);
	}
}
