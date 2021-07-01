#include<reg51.h>
#include<stdio.h>
#define display_port P3      //Data pins connected to port 3 on microcontroller
#define toDAC P2				  
sbit rs = P3^0;  //RS pin connected to pin 0 of port 3
sbit rw = P3^1;  // RW pin connected to pin 1 of port 3
sbit e =  P3^2;  //E pin connected to pin 2 of port 3
sbit C4 = P1^0;  // Connecting keypad to Port 1
sbit C3 = P1^1;
sbit C2 = P1^2;
sbit C1 = P1^3;
sbit R4 = P1^4;
sbit R3 = P1^5;
sbit R2 = P1^6;
sbit R1 = P1^7;

unsigned int key;
void msdelay(unsigned int time);
void lcd_cmd(unsigned char command);
void lcd_char_data(unsigned char disp_data);
void lcd_string_data(const char *p);
void lcd_init();
int row_finder1();
int row_finder2();
int row_finder3();
int row_finder4();
int keypad();


void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)
	{  
			for(j=0;j<1275;j++);
	}
}
void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = (command & 0xF0);
    rs= 0;
    rw=0;
    e=1;
    msdelay(20);
    e=0;
	msdelay(20);
	display_port = ((command<<4) & 0xF0);
    rs= 0;
    rw=0;
    e=1;
    msdelay(20);
    e=0;
}
void lcd_char_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = (disp_data & 0xF0);
    rs= 1;
    rw=0;
    e=1;
    msdelay(20);
    e=0;
	msdelay(20);
  display_port = ((disp_data<<4) & 0xF0);
    rs= 1;
    rw=0;
    e=1;
    msdelay(20);
    e=0;
    
}


void lcd_string_data(const char *p)
{
	while(*p!='\0')
	{
		lcd_char_data(*p);
		p++;
		msdelay(20);
	}
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x28);  // for 2 lines and 5X7 matrix of LCD(4 bit mode)
    msdelay(20);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(20);
    lcd_cmd(0x01);  //clear screen
    msdelay(20);
    lcd_cmd(0x80);  // bring cursor to position 1 of line 1
    msdelay(20);
}
int row_finder1() //Function for finding the row for column 1
{
int key;
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;
if(R1==0)
{
	key='7';
  lcd_char_data('7'); 
}
else if(R2==0)
{
	key='4';
  lcd_char_data('4');
}
else if(R3==0)
{
	key='1';
  lcd_char_data('1');
}
else if(R4==0)
{	key='%';
  lcd_char_data('%');
}
return key;
}
int row_finder2() //Function for finding the row for column 2
{
int key;
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;
if(R1==0)
{	
	key='8';
lcd_char_data('8');
}
else if(R2==0)
{	
	key='5';
lcd_char_data('5');
}
else if(R3==0)
{
	key='2';
lcd_char_data('2');
}	
else if(R4==0)
{	
	key='0';
lcd_char_data('0');
}
return key;
}
int row_finder3() //Function for finding the row for column 3
{
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;
if(R1==0)
{
	key='9';
lcd_char_data('9');
}
else if(R2==0)
{
	key='6';
lcd_char_data('6');
}
else if(R3==0)
{	
	key='3';
lcd_char_data('3');
}
else if(R4==0)
{
	key='=';
lcd_char_data('=');
}
return key;
}
int row_finder4() //Function for finding the row for column 4
{

R1=R2=R3=R4=1;
C1=C2=C3=C4=0;
if(R1==0)
{
lcd_char_data('/');
}
if(R2==0)
{
lcd_char_data('*');
}
if(R3==0)
{
lcd_char_data('-');
}
if(R4==0)
{
lcd_char_data('+');
}
return key;
}

int keypad()
{
int x;
while(1)
    {  
								
          msdelay(30); 
          C1=C2=C3=C4=1;
          R1=R2=R3=R4=0;
          if(C1==0)
					{
          x=row_finder1();
						break;
					}
          else if(C2==0)
          {
						x=row_finder2();
						break;
          }
					else if(C3==0)
					{
						x=row_finder3();
						break;
					}
					else if(C4==0)
					{
						x=row_finder4();
				    break;
					}				
			
    }
		return x;	
}
void main()
{
	int lcd_arr[3];
	int i;
	unsigned int n;
  lcd_init();
	lcd_string_data("ShortCircuit2021");
	while(1)
	{
	lcd_cmd(0xC0); 					// force cursor to begin on 2nd line
	msdelay(20);
	n=0;
	for(i=0;i<=2;i++)
		{
		 lcd_arr[i]=keypad();
			
		}				
  n=(lcd_arr[0]*100)+(lcd_arr[1]*10)+lcd_arr[2]+48;
  toDAC=n;
	msdelay(100);
	}				 			 
}