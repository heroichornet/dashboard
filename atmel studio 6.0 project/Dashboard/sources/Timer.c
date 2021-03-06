/*
 * Timer.c
 *
 * Created: 27.02.2012 08:32:04
 *  Author: Morris
 */ 

/* +--------------------------------+ */
/* | Includes						| */
/* +--------------------------------+ */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/iocanxx.h>
#include <util/atomic.h>
#include <util/twi.h>
#include "..\includes\compiler.h"
#include "..\includes\Timer.h"
#include "..\includes\GlobalIncludes.h"
//#include "Event.h"
/* +--------------------------------+ */
/* | Prototypes						| */
/* +--------------------------------+ */

/* +--------------------------------+ */
/* | Global Variables				| */
/* +--------------------------------+ */

static U8 Timer0_Prescaler;

/* +--------------------------------+ */
/* | Interrupt Service Routines		| */
/* +--------------------------------+ */


ISR(TIMER0_OVF_vect){
	EventAddEvent(EVENT_CANTIMEOUT);
	TCCR0A=0x00;
	return;
}


ISR(TIMER1_COMPA_vect){
	OCR1A+=OCR1A_PERIOD_CNT;
	EventAddEvent(EVENT_50HZ);
	return;
}

ISR(TIMER1_COMPB_vect){
	OCR1B+=OCR1B_PERIOD_CNT;
	EventAddEvent(EVENT_25HZ);
	return;
}

ISR(TIMER1_COMPC_vect){
	OCR1C+=OCR1C_PERIOD_CNT;
	EventAddEvent(EVENT_200HZ);
	return;
}

ISR(TIMER3_COMPA_vect){
	OCR3A+=OCR3A_PERIOD_CNT;
	EventAddEvent(EVENT_10HZ);
	return;
}

ISR(TIMER3_COMPB_vect){
	OCR3B+=OCR3B_PERIOD_CNT;
	EventAddEvent(EVENT_5HZ);
	return;
}

ISR(TIMER3_COMPC_vect){
	OCR3C+=OCR3C_PERIOD_CNT;
	EventAddEvent(EVENT_4HZ);
	return;
}

ISR(TIMER1_OVF_vect){}

ISR(TIMER3_OVF_vect){}


/* +--------------------------------+ */
/* | CODE							| */
/* +--------------------------------+ */

void Timer0_init(U8 prescaler){
	Timer0_Prescaler=prescaler;
	TCCR0A=0x00;
	TIMSK0=0x01;
}

void Timer0_Start(){
	TCNT0=0x00;
	TCCR0A=Timer0_Prescaler;
}

void Timer0_Stop(){
	TCCR0A=0x00;
}

void Timer1_init(U8 prescaler, Bool interruptOverflow){
	/*
	000 no Clock source
	001 CLK = BusCLK
	010 CLK = BusCLK/8
	011 CLK = BusCLK/64
	100 /256
	101 /1024
	*/
	TCCR1B = prescaler;
	
	TIMSK1 = (interruptOverflow<<TOIE1);
}

void Timer3_init(U8 prescaler, Bool interruptOverflow){
	/*s
	000 no Clock source
	001 CLK = BusCLK
	010 CLK = BusCLK/8
	011 CLK = BusCLK/64
	100 /256
	101 /1024
	*/
	TCCR3B = prescaler;

	
	TIMSK3 = (interruptOverflow<<TOIE3);
}

void TIMER_Timer1_OCR1A_on(void){
	OCR1A = TCNT1 + OCR1A_PERIOD_CNT;
	TIMSK1 = TIMSK1 | (1<<OCIE1A);
}

void TIMER_Timer1_OCR1B_on(void){
	OCR1B = TCNT1 + OCR1B_PERIOD_CNT;
	TIMSK1 = TIMSK1 | (1<<OCIE1B);
}

void TIMER_Timer1_OCR1C_on(void){
	OCR1C = TCNT1 + OCR1C_PERIOD_CNT;
	TIMSK1 = TIMSK1 | (1<<OCIE1C);
}

void TIMER_Timer3_OCR3A_on(void){
	OCR3A = TCNT3 + OCR3A_PERIOD_CNT;
	TIMSK3 = TIMSK3 | (1<<OCIE3A);
}

void TIMER_Timer3_OCR3B_on(void){
	OCR3B = TCNT3 + OCR3B_PERIOD_CNT;
	TIMSK3 = TIMSK3 | (1<<OCIE3B);
}

void TIMER_Timer3_OCR3C_on(void){
	OCR3C = TCNT3 + OCR3C_PERIOD_CNT;
	TIMSK3 = TIMSK3 | (1<<OCIE3C);
}


