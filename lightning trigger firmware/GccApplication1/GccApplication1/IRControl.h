/*
 * IncFile1.h
 *
 * Created: 8/14/2013 12:04:11 PM
 *  Author: chuby
 */ 


#ifndef IRCONTROL_H_
#define IRCONTROL_H_


#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

void IR_Control_Init();
void shutter_now();
void tuggle_focus();
#endif /* INCFILE1_H_ */