#include <lpc17xx.h>
unsigned long int i,var,j;
void delay(unsigned int r1)
{
	unsigned int r;
	for (r=0;r<r1;r++);
}
void clk()
{
	var=0x00000001;
	for (i=0;i<4;i++)
	{
		LPC_GPIO2->FIOCLR=0x0000000F;
		LPC_GPIO2->FIOSET=var;
		var=var<<1;
		delay(15000);
	}
}
void anticlk()
{
	var=0x00000008;
	for (i=0;i<4;i++)
	{
		LPC_GPIO2->FIOCLR=0x0000000F;
		LPC_GPIO2->FIOSET=var;
		var=var>>1;
		delay(15000);
	}
}
int main()
{
	LPC_PINCON->PINSEL4=0x00000000;
	LPC_GPIO2->FIODIR=0x0000000F;
	while(1)
	{
		for (j=0;j<50;j++)
			clk();
		delay(65000);
		for (j=0;j<50;j++)
			anticlk();
		delay(65000);
	}
}
