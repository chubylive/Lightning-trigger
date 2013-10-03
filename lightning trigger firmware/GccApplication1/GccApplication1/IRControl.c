/*
 * CFile1.c
 *
 * Created: 8/14/2013 1:01:09 AM
 *  Author: chuby
 */ 
/*******************************************
 *
 * Name.......:  AVR IRControl Lightning Trigger
 * Description:  A Lightning Trigger to control IR Triggered cameras 
 * via infrared (IR) wireless remote. 
 * Author.....:  Marc Kohlbauer
 * Version....:  3.0
 * Date.......:  2012-03-19
 * Project....:  http://www.hardpan.com/category/arduino/
 * Contact....:  marc@hardpan.com
 * License....:  This work is licensed under the Creative Commons 
 * Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * Keywords...:  arduino, library, camera, infrared, control,
 * lightning, trigger, wireless, IR, sensor, adjustable
 * History....:  07-06-013 V1.0 - IR Control
 *
 ********************************************/

#include "IRControl.h"

 
void IR_Control_Init(){
	TCCR1A = (1<<WGM11) | (1<< COM1A1); // non-inverting, Mode 14: Fast PWM
	TCCR1B = (1<< WGM13) | (1<<WGM12) | (1<<CS10); // prescaler = 1
	ICR1 = 210; // because ((16000000 / 38000) /1)-1 = 420
	            //	       ((F_CPU / F_PWM) / Prescaler) - 1
	OCR1A = 105; // 420 / 2 to get a 50% duty cycle

	  DDRA |= (1<<PA6); // set OC1A to output
	  DDRA |= (1<<DDA3); //set pin8 to be output to control led
	  PORTA |= (1<<PA3); //initialize with pin high(led off)
}


void shutter_now(){

  PORTA &= ~(1 << PA3);
 
  _delay_ms(13);
  PORTA |= (1 << PA3);

  _delay_ms(3);

for (int i = 0; i < 7; ++i)
{
  PORTA &= ~(1 << PA3);
  _delay_ms(1);
  PORTA |= (1 << PA3);
  _delay_ms(1);
}
  
	// low wait 13ms
	// high wait 3m
	// 7 pulse of 1ms on 1ms off
}
	
void tuggle_focus(){
  PORTA &= ~(1 << PA3);
  _delay_ms(13);
  PORTA |= (1 << PA3);

  _delay_ms(3);

  for (int i = 0; i < 5; ++i)
  {
   PORTA &= ~(1 << PA3);
   _delay_ms(1);
   PORTA |= (1 << PA3);
   _delay_ms(1);
  }
  
  PORTA &= ~(1 << PA3);
  _delay_ms(1);
  PORTA |= (1 << PA3);

  _delay_ms(3);

  PORTA &= ~(1 << PA3);
  _delay_ms(1);
  PORTA |= (1 << PA3);
}
