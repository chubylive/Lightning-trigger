/*
 * GccApplication1.c
 *
 * Created: 8/13/2013 10:45:53 PM
 *  Author: chuby
 */ 


#include <avr/io.h>
#include "IRControl.h"
#include "adc.h"
uint16_t adc_val;		//adc value 
uint16_t curLightVal;	//reading from sensor
uint8_t switchPin = 2;   // reduce sensitivity switch is connected to pin 2
uint8_t buttonState;     // variable to hold the button state
uint8_t val;             // variable for reading the pin status
uint8_t switch2Pin = 3;  // increase sensitivity switch is connected to pin 3
uint8_t button2State;    // variable to hold the button state
uint8_t val2;            //variable for reading the pin status

uint8_t TRIGGER_THRESHOLD = 200;  // base sensor adjustment after reset or power up
void calculate_treshold(uint16_t sample_num);
void collect_sample(uint16_t *buff, uint16_t buff_len );
void calculate_treshold(uint16_t sample_num);

uint8_t get_avrg_diff(uint16_t *buff_sample, uint16_t *buff_avrg,  uint16_t avrg_len);


void setup()
{
	IR_Control_Init();
	adc_init();
	PORTA |= _BV(PA1) | _BV(PA2); // setup pa1 and pa2 as inputs with pull up register
	buttonState = (PINA & _BV(PA1));
	button2State = (PINA & _BV(PA2));
	
	
	
}

void collect_sample(uint16_t *buff, uint16_t buff_len ){
	uint16_t idx;
	for (idx = 0; idx < buff_len; idx++){
		buff[idx] = adc_val;
		_delay_ms(50);
	}
}

uint8_t get_avrg_diff(uint16_t *buff_sample, uint16_t *buff_avrg,  uint16_t avrg_len){
	uint16_t idx, jdx, kdx;
	uint16_t avrg = 0;
	for (idx = 0, jdx = 1; idx < avrg_len; idx++){
		buff_avrg[avrg_len] = buff_sample[idx] - buff_sample[jdx++];
	}
	for (kdx = 0; kdx < avrg_len; kdx++){
		avrg +=  buff_avrg[kdx];
	}
	
	return avrg/avrg_len;	
	
}

void calculate_treshold(uint16_t sample_num){
	uint16_t sample_buffer[sample_num];
	uint16_t average_buffer[sample_num - 1];
	
	//collect sample in to smp buff.
	collect_sample(sample_buffer, sample_num);
	uint16_t avrg_chg = get_avrg_diff(sample_buffer,average_buffer, (sample_num -1) );
	//put diff of 1 + idxsmp and idxsmp into average buf
	// calculate average. 
	TRIGGER_THRESHOLD = avrg_chg;
	
}

int main(void)
{
	setup();
//	calculate_treshold(20);
    for(;;)
    {
// 		val = (PINA & _BV(PA1));
// 		val2 = (PINA & _BV(PA2));
// 		
// 		if ( val != buttonState)
// 		{
// 			TRIGGER_THRESHOLD +=2;
// 			if (TRIGGER_THRESHOLD > 150)
// 			{
// 				TRIGGER_THRESHOLD = 150;
// 			}
// 		}
// 		buttonState = val;
// 
// 		if (val2 != button2State)
// 		{
// 			TRIGGER_THRESHOLD--;
// 			if (TRIGGER_THRESHOLD < 1)
// 			{
// 				TRIGGER_THRESHOLD = 1;
// 			}
// 		}
// 		
// 		button2State = val2;
// 		
// 		uint16_t newLightVal = adc_val;
// 		
// 		if((newLightVal - curLightVal) > TRIGGER_THRESHOLD){
			shutter_now();
 			_delay_ms(5500);
// 		}
// 		
// 		curLightVal = adc_val;  
	}
}

ISR( ADC_vect){
	ADCSRA |= _BV(ADIF);
	adc_val = ADC;
}

