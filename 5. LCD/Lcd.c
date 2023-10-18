#include <lpc17xx.h>
#include "lcd.h"
unsigned long int temp1=0, temp2=0 ;
unsigned char Msg1[14] = {"ANIRUDH"};
unsigned char Msg2[15] = {"G S"};
unsigned int i=0;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
  lcd_init();				//Initialise LCD
	delay_lcd(3200);
	
	temp1 = 0x81;			//Message1 on LCD's 1st line
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg1);
	
		
	temp1 = 0xC1;			//Message2 on LCD's 2nd line
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg2);
	delay_lcd(5000);
	
	while(1);
}
void lcd_init()  //LCD initialization
{
	unsigned char arr1[4]={0x30,0x30,0x30,0x20};
	unsigned char arr2[4]={0x28,0x0C,0x06,0x80};
	unsigned int i;
	//Ports initialized as GPIO
  LPC_PINCON->PINSEL3 &= 0xFFFF00FF;  //data lines - P1.20 to P1.23
	LPC_PINCON->PINSEL7 &= 0XFFF3FFFF;  //P3.25
  LPC_PINCON->PINSEL7 &= 0xFFCFFFFF;  //P3.26
	LPC_PINCON->PINSEL9 &= 0xFCFFFFFF;  //P4.28

	//Setting the directions as output
  LPC_GPIO1->FIODIR |= DT_CTRL;	// data lines - P1.20 to P1.23
	LPC_GPIO3->FIODIR |= RS_CTRL;	// RS - P3.25
  LPC_GPIO3->FIODIR |= RW_CTRL;	// RW - P3.26
	LPC_GPIO4->FIODIR |= EN_CTRL;	// P4.28 
        
  clear_ports();
	delay_lcd(3200);
 
	for (i=0;i<4;i++)
	{
		temp2=arr1[i];
		wr_cn();
		delay_lcd(30000);
	}
	temp1=arr2[0];
	lcd_com();
	delay_lcd(30000);
	for (i=1;i<4;i++)
	{
		temp1=arr2[i];
		lcd_com();
		delay_lcd(800);
	}
  return;
}

void lcd_com(void)
{
	temp2= temp1 & 0xF0;
	temp2 = temp2 << 16;				//data lines from 20 to 23
	wr_cn();
	temp2 = temp1 & 0x0F;
	temp2 = temp2 << 20; 
	wr_cn();
	delay_lcd(1000);
  return;
}

void wr_cn(void)                       
{ 	 
	clear_ports();
	LPC_GPIO1->FIOPIN = temp2;			// Assigning value to data lines    
	LPC_GPIO3->FIOCLR = RW_CTRL;		// clear RW bit 
  LPC_GPIO3->FIOCLR = RS_CTRL;		// clear RS bit
	LPC_GPIO4->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO4->FIOCLR  = EN_CTRL;		// EN =0
  return;
 }
 void lcd_data(void)
{             
	temp2 = temp1 & 0xF0;
  temp2 = temp2 << 16;
  wr_dn();
  temp2= temp1 & 0x0F;	
  temp2= temp2 << 20;
  wr_dn();
  delay_lcd(1000);	
  return;
} 
void wr_dn(void)
{  	  
	clear_ports();
	LPC_GPIO1->FIOPIN = temp2;			// Assigning value to data lines    
	LPC_GPIO3->FIOSET = RS_CTRL;		// set RS bit
	LPC_GPIO3->FIOCLR = RW_CTRL;		// clear RW bit
	LPC_GPIO4->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO4->FIOCLR  = EN_CTRL;	 // EN =0
  return;
 }
void delay_lcd(unsigned int r1)
{
  unsigned int r;
  for(r=0;r<r1;r++);
  return;
}
void clr_disp(void)
{
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
  return;
}
void clear_ports(void)  //Clearing lines at power on
{
	LPC_GPIO1->FIOCLR = DT_CTRL; //Clearing data lines
	LPC_GPIO3->FIOCLR = RS_CTRL;  //Clearing RS 
  LPC_GPIO3->FIOCLR = RW_CTRL;  //Clearing RW 
	LPC_GPIO4->FIOCLR = EN_CTRL; //Clearing Enable line     
  return;
}
void lcd_puts(unsigned char *buf1)
{
	unsigned int i=0;
	while(buf1[i]!='\0')
  {
		temp1 = buf1[i];
    lcd_data();
		i++;
    if(i==16)
		{
			temp1 = 0xC1;
			lcd_com();
		}
	}
	return;
}
