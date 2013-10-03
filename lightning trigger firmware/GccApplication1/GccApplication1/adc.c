/*
 * CFile2.c
 *
 * Created: 8/14/2013 2:45:55 AM
 *  Author: chuby
 */ 
#include "adc.h"

void adc_init(){
	ADMUX |= _BV(REFS0);
	
	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) |_BV(ADPS1) | _BV (ADPS2) | _BV (ADATE);
	DIDR0 |= _BV(ADC0D);
	
	sei();	
	
	adc_start();
}

void adc_start(){
	ADCSRA |= _BV(ADSC);
}
 
