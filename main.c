/*
 * PID03.cpp
 *
 * Created: 2/6/2019 5:02:31 AM
 * Author : user
 */ 


#include <avr/io.h>
#include <avr/sfr_defs.h>



/* Replace with your library code */
uint8_t varL,varR;
int basespeed=255;
float kp=60.0,kd=0.0;
float pd;
int main(void)
{   float d,error,e1=0;
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS02);//(1<<CS00)|(1<<CS01);
	DDRB|=0b00001000;
	TCCR2|=(1<<WGM21)|(1<<WGM20)|(1<<COM21)|(1<<CS22)|(1<<CS21);//|(1<<CS20);
	DDRD|=0b10000000;
	while(1)
	{   
		int z[8]={0,0,0,0,0,0,0,0};
	 int lm,rm;
		int sum1=0,sum2=0;
		 for(int i=0;i<8;i++)
		 {if(bit_is_clear(PINA,i))
		  z[i]=1;
		  sum2+=z[i];
		 }
		  sum1=z[0]*(6)+z[1]*(4)+z[2]*(2)+z[3]*(0)+z[4]*(2)+z[5]*(4)+z[0]*(6)+z[0]*(8);
		 if(sum2==0)
		 sum2=1;
		
		float mk=(float)(sum1)/(float)(sum2);
		error=(mk-(4.5));    //proportional error
		d=(error)-e1;
		e1=error;
		
		pd=(kp*error)+(kd*d);
		lm=(basespeed)-(pd);
		rm=(basespeed)+(pd);
		
		if(lm>0)
		{   if(lm>255)
			lm=255;
			//	lforward();
			//PORTD=0b00000000;
			varL=0b00000100;//forward();
		}
		else{
			lm=-lm;
			if(lm>255)
			lm=255;
			//lbackward();
			//PORTD=0b00000000;
			varL=0b00001000;//backward();
		} 
		if(rm>0)
		{   if(rm>255)
			rm=255;
			//rforward();
			//PORTD=0b00000000;
			varR=0b00000001;//forward();
		}
		else
		{  rm=-rm;
			if(rm>255)
			rm=255;
			//rbackward();
		//	PORTD=0b00000000;
			varR=0b00000010;//backward();
			
		}
		PORTD=varL|varR;
		
	/*   if(lm>255)
		lm=255;
		if(lm<0)
		lm=0;
		
		if(rm>255)
		rm=255;
		if(rm<0)
		rm=0;
			PORTD=0b00101000;
	if(error==0)
	PORTD=0b00101000;
	if(error<0)
	PORTD=0b00100000;
	if(error>0)
	PORTD=0b00001000;*/
		OCR0= (int)lm;
		OCR2= (int)rm;
		 
	}
	
}



