/*
 * MyCommon.c
 *
 * Created: 06.03.2014 23:04:18
 *  Author: michael
 */ 


#include "../includes/MyCommon.h"
#include "../includes/GlobalIncludes.h"


/* Note to I/O Pin Registers */
/* DDRxn high = Output
/* DDRxn low  = Input
/* PORTxn high = pull up, if Input  
/* PORTxn low = no pull up, if Input
/* PORTxn high = driven high, if output
/* PORTxn low = driven low, if output
*/

void main_init(){

	/* Init Ports */
	// Default Pin config for PORT A,B,C,D,E,F (Input with pull up)
	DDRA=0x00;
	DDRB=0x00;
	DDRC=0x00;
	DDRE=0x00;
	DDRF=0x00;
	DDRG&=~(0b00011111); // Port G Pins 7,8 and 6 not written
	
	PORTA=0xFF;
	PORTB=0xFF;
	PORTC=0xFF;
	PORTD=0xFF;
	PORTE=0xFF;
	PORTF=0xFF;
	PORTG|=(0b00011111); // Port G Pins 7,8 and 6 not written
	

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

	#if HAS_200HZ|HAS_100HZ|HAS_50HZ
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

	#if HAS_50HZ
	TIMER_Timer1_OCR1C_on();
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
	
	#if HAS_BUZZER
		buzzer_init();	
	#endif
	
	#if HAS_LEDS
		led_init();
	#endif
		

}

void main_deinit(){
	
}
