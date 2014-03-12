/*
 * MyCommon.c
 *
 * Created: 06.03.2014 23:04:18
 *  Author: michael
 */ 


#include "MyCommon.h"
#include "../../aux_libs/includes/GlobalIncludes.h"


void main_init(){
	//LED
	DDRA=DDRA|0x08;
	PORTA=PORTA&(~0x08);
	
	#ifdef IO_PORTB_OR
	DDRB|=IO_PORTB_OR;
	DDRB&=IO_PORTB_AND;
	PORTB&=(~IO_PORTB_OR);
	#endif
	
	#ifdef IO_PORTD_OR
	DDRD|=IO_PORTD_OR;
	DDRD&=IO_PORTD_AND;
	PORTD&=(~IO_PORTD_OR);
	#endif
	
	#ifdef IO_PORTE_OR
	DDRE|=IO_PORTE_OR;
	DDRE&=IO_PORTE_AND;
	PORTE&=(~IO_PORTE_OR);
	#endif
	
	CANInit();
	
	#if HAS_200HZ|HAS_100HZ
	Timer1_init(TMR1_PRESCALER,FALSE);
	#endif

	#if HAS_10HZ
	Timer3_init(TMR3_PRESCALER,FALSE);
	#endif
	
	#if HAS_200HZ
	TIMER_Timer1_OCR1A_on();
	#endif

	#if HAS_100HZ
	TIMER_Timer1_OCR1B_on();
	#endif

	#if HAS_10HZ
	TIMER_Timer3_OCR3A_on();
	#endif

	#if HAS_ADC
	DDRF=0x00;
	PORTF=0x00;
	ADInit(MCM_ADC_PRESCALER, TRUE);
	#endif
	
	InitWDT();
	
	EventAddEvent(EVENT_INIT);
	
		
}

void main_deinit(){
	
}

