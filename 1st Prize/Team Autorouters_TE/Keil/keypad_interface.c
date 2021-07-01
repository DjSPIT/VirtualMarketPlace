#include<reg52.h>
#include<stdio.h>
#include<string.h>
#include "LCD_8_bit.h"

#define keyport P1
#define dac P0 //Port P0 address
sbit RS 		= P3^3;
sbit RW 		= P3^4;
sbit ENABLE = P3^5;
unsigned char keypad[4][4] = {{'7','8','9','/'},
															{'4','5','6','x'},
															{'1','2','3','-'},
															{' ','0','=','+'} };

unsigned char colloc, rowloc;


unsigned char key_detect()
{
		keyport=0xF0;							
			do
			{
				keyport = 0xF0;				
				colloc = keyport;
				colloc&= 0xF0;				
		}while(colloc != 0xF0);		
			do
			{
				do
				{
					delay(20);									/* 20ms key debounce time */
					colloc = (keyport & 0xF0);	/* read status of column */
				}while(colloc == 0xF0);				/* check for any key press */
		
				delay(1);
				colloc = (keyport & 0xF0);
			}while(colloc == 0xF0);
while(1)
	{
		/* now check for rows */
			keyport= 0xFE;									/* check for pressed key in 1st row */
			colloc = (keyport & 0xF0);
			if(colloc != 0xF0)
			{
				rowloc = 0;
				break;
			}

			keyport = 0xFD;									/* check for pressed key in 2nd row */
			colloc = (keyport & 0xF0);
			if(colloc != 0xF0)
			{
				rowloc = 1;
				break;
			}
			
			keyport = 0xFB;									/* check for pressed key in 3rd row */
			colloc = (keyport & 0xF0);
			if(colloc != 0xF0)
			{
				rowloc = 2;
				break;
			}

			keyport = 0xF7;									/* check for pressed key in 4th row */
			colloc = (keyport & 0xF0);
			if(colloc != 0xF0)
			{
				rowloc = 3;
				break;
			}	
	}
	
		if(colloc == 0xE0)
		{
				return(keypad[rowloc][0]);
		}		
		else if(colloc == 0xD0)
		{
			return(keypad[rowloc][1]);
		}	
		else if(colloc == 0xB0)
		{
			return(keypad[rowloc][2]);
		}	
		else
		{
			return(keypad[rowloc][3]);
		}	
}


int main(void)
{
int dacval = 128;
	dac = dacval;
	LCD_Init();
	LCD_String_xy(1,0,"Short circuit");
	LCD_String_xy(2,0,"Designathon");
delay(100);
LCD_Command(0x01);
	LCD_String_xy(1,0,"8: inc , 2: dec");

	while(1){
		LCD_Command(0xc0);
		if(key_detect()== '8'){
				LCD_Command(0x01);
			LCD_String_xy(2,0,"Incremented 10%");
			dacval += 10 ;
		}
		else if(key_detect()== '2'){
				LCD_Command(0x01);
			LCD_String_xy(2,0,"Decremented 10%");
			dacval -= 10;
		}
		else{
LCD_String_xy(2,0,"Short circuit");

	}
		if(dacval >255) dacval = 0;
dac = dacval;		
}}