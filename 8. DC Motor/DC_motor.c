#include <lpc17xx.h>
unsigned int i;
void delay(unsigned int r1)
{
	unsigned int r;
	for (r=0;r<r1;r++);
}
void clk()
{
	LPC_GPIO4->FIOPIN=0x20000000;
}
void anticlk()
{
	LPC_GPIO4->FIOPIN=0x10000000;
}
void stop()
{
	LPC_GPIO4->FIOPIN=0x30000000;
}
int main()
{
	LPC_GPIO4->FIODIR=0x30000000;
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
