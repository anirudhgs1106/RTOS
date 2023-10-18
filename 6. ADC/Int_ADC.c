#include<LPC17xx.h>
#include<stdio.h>
#define	Ref_Vtg 3.300
#define	Full_Scale 0xFFF			//12 bit ADC
int main(void)
{
	unsigned long adc_temp;
	unsigned int i;
	//float in_vtg;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_SC->PCONP |= (1<<15);          //Power for GPIO block
  LPC_PINCON->PINSEL1 &= ~(0x11<<14);
  LPC_PINCON->PINSEL1 |= 0x01<<14;	//P0.23 as AD0.0
	LPC_SC->PCONP |= (1<<12);			    //Enable ADC

	while(1)
	{
		LPC_ADC->ADCR = 0x01200001; //ADC0.0, start conversion and operations	
		for(i=0;i<2000;i++);			  //Delay for conversion
		while((adc_temp = LPC_ADC->ADGDR) == 0x80000000);	//Indicates completion of conversion
		adc_temp = LPC_ADC->ADGDR;
		adc_temp >>= 4;
		adc_temp &= 0x00000FFF;			//12 bit ADC
		for(i=0;i<2000;i++);       //Delay for conversion
	}
}

