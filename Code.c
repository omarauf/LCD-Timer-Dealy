// Lcd pinout settings
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;

// Pin direction
sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;



void dealy(int dealy){
	int c_d;									//define a variable for counting down
	char text[12];								//string variable to print on LCD
	char lcd;									//final text to be written
	Lcd_Init();									//initialize the LCD screen
	Lcd_Cmd(_LCD_CURSOR_OFF);					//Turn off cursor
	dealy = dealy*10;							//convert the pointer to dealy 
	for(c_d=dealy ; c_d>0 ; c_d--){
		IntToStr(c_d, text);					//convert integer c_d to string of 7 characters
		lcd=Ltrim(text);						//remove empty characters from left
		Lcd_Out(1,3,"s");						//print "s" on the third digit of LCD
		Lcd_Out(1,1,lcd);						//finally print the count down second value
		Delay_ms(1000);							//dealy each loop 1s
		Lcd_Cmd(_LCD_CLEAR);					//clear LCD
	}
}


void screen(int step){									
	Lcd_Init();											//initialize the LCD screen
	Lcd_Cmd(_LCD_CURSOR_OFF);							//Turn off cursor
	switch(step){										//switch operation to determine which step to print (10s, 20s, 30s or 40s)
		case 1 : Lcd_Out(1, 1, "10s");break;
		case 2 : Lcd_Out(1, 1, "20s");break;
		case 3 : Lcd_Out(1, 1, "30s");break;
		case 4 : Lcd_Out(1, 1, "40s");break;
		default:break;
	}
}


int pointer =0;
void interrupt(){					//interrupt function
	if(INTCON.INTF==1){				//if RB0 interrupt occurred
		if(pointer!=4)				
			pointer++;				//increment the pointer
		else
			pointer=1;				//if pointer is 4 then make it 1
		screen(pointer);			//call screen function
	}
	INTCON.INTF=0;					//clear RB0 interrupt flag
	
	if(INTCON.RBIF==1){																	
		if(PORTB.F7==1){																	//if RB7 interrupt occurred
			switch(pointer){																//switch operation to determine which step to do (10s, 20s, 30s or 40s)
				case 1 : PORTD.F0=1;dealy(pointer);PORTD=0;screen(pointer);break;			//turn on port RD0 then call function delay for 10s then call screen function
                case 2 : PORTD.F0=1;dealy(pointer);PORTD=0;screen(pointer);break;			//turn on port RD0 then call function delay for 20s then call screen function
                case 3 : PORTD.F0=1;dealy(pointer);PORTD=0;screen(pointer);break;			//turn on port RD0 then call function delay for 30s then call screen function
                case 4 : PORTD.F0=1;dealy(pointer);PORTD=0;screen(pointer);break;			//turn on port RD0 then call function delay for 40s then call screen function
                default: break;
            }
		}
	}
	INTCON.RBIF=0;
}
		
void main(){
	TRISD=0;						//all RD port as output 
	PORTD=0;						//clear PORTD initially
	TRISB=0x81;						//RB0 and RB7 as input	
	PORTB=0;						//clear PORTB initially
	INTCON.INTE=1;					//Enable RB0/INT interrupt
	INTCON.RBIE=1;					//Enable RB4, RB5, RB6 and RB7 interrupt
	INTCON.GIE=1;					//Enable global interrupt
	OPTION_REG=0b11000000;			//and enable interrupt on rising edge at RB0 pin

	while(1){
				
	}
}