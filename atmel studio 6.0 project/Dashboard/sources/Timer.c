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


/* +--------------------------------+ */
/* | Interrupt Service Routines		| */
/* +--------------------------------+ */

ISR(TIMER0_COMP_vect){
	return;
}

ISR(TIMER0_OVF_vect){
	return;
}

ISR(TIMER1_COMPA_vect){
	OCR1A+=OCR1A_PERIOD_CNT;
	EventAddEvent(EVENT_5KHZ);
	return;
}

ISR(TIMER1_COMPB_vect){
	OCR1B+=OCR1B_PERIOD_CNT;
	EventAddEvent(EVENT_1KHZ);
	return;
}

ISR(TIMER1_COMPC_vect){
	OCR1C+=OCR1C_PERIOD_CNT;
	EventAddEvent(EVENT_500HZ);
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


