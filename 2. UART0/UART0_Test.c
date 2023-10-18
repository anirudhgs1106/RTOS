#include<LPC17xx.h>
#include"UART0.h"
unsigned char recv_buf[50], recv_data=0, recv_index=0,space='\n';
unsigned char rx0_flag=0, tx0_flag=0;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	UART0_Init();
	while(1)
	{
		while(rx0_flag == 0x00);
		rx0_flag = 0x00;
		LPC_UART0->THR = recv_data;
		while(tx0_flag == 0x00);
		tx0_flag = 0x00;
		while(!(LPC_UART0->LSR, 0x5u));
    LPC_UART0->THR = space;
		while(!(LPC_UART0->LSR, 0x5u));
    LPC_UART0->THR = recv_data;
	}
}
void UART0_Init(void)
{
	LPC_SC->PCONP |= (1<<3);
	LPC_PINCON->PINSEL0 &= ~0x000000F0;
	LPC_PINCON->PINSEL0 |= 0x00000050;
	LPC_UART0->LCR = 0x00000083;	//enable divisor latch, parity disable, 1 stop bit, 8bit word length
	LPC_UART0->DLM = 0X00; 
	LPC_UART0->DLL = 0x13;      	//select baud rate 9600 bps
	LPC_UART0->LCR = 0X00000003;
	LPC_UART0->FCR = 0x07;
	LPC_UART0->IER = 0X03;	   		//select Transmit and receive interrupt
	NVIC_EnableIRQ(UART0_IRQn);		
}
void UART0_IRQHandler(void)
{
	unsigned long Int_Stat;
	Int_Stat = LPC_UART0->IIR;		//reading the data from interrupt identification register
	Int_Stat = Int_Stat & 0x06;		
	if((Int_Stat & 0x02)== 0x02)	//transmit interrupt
		tx0_flag = 1;
	else if( (Int_Stat & 0x04) == 0x04)  //receive data available
	{
		recv_data = LPC_UART0->RBR;
		rx0_flag = 1;
	}
}
