/*
 * CFile2.c
 *
 * Created: 8/14/2013 2:45:55 AM
 *  Author: chuby
 */ 

void adc_init(uint8_t freq){
	ADMUX |= _BV(REFS0);
	
	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) |_BV(ADPS1)) | _BV)(ADPS2) | _BV(ADATE);
	sei();	
}