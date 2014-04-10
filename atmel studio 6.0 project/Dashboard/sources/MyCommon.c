/*
 * MyCommon.c
 *
 * Created: 06.03.2014 23:04:18
 *  Author: michael
 */ 


#include "../includes/MyCommon.h"
#include "../includes/GlobalIncludes.h"
#include "../includes/Buzzer.h"
#include "../includes/Led.h"
#include "../includes/Button.h"




void main_init(){


	ports_init();
	
	CANInit();

	#if HAS_50HZ|HAS_200HZ|HAS_50HZ
	Timer1_init(TMR1_PRESCALER,FALSE);
	#endif

	#if HAS_10HZ|HAS_5HZ|HAS_4HZ
	Timer3_init(TMR3_PRESCALER,FALSE);
	#endif

	#if HAS_50HZ
	TIMER_Timer1_OCR1A_on();
	#endif

	#if HAS_25HZ
	TIMER_Timer1_OCR1B_on();
	#endif

	#if HAS_200HZ
	TIMER_Timer1_OCR1C_on();
	#endif

	#if HAS_10HZ
	TIMER_Timer3_OCR3A_on();
	#endif

	#if HAS_BUZZER
	buzzer_init();
	TIMER_Timer3_OCR3C_on();
	#endif
	
	#if HAS_LEDS
	led_init();
	#endif
	
	#if HAS_BUTTONS
	button_init();
	#endif
	
	#if HAS_DISPLAY
	display_init();
	#endif
	
	#if HAS_RADIO
	radio_init();
	#endif
	
	InitWDT();
	
	EventAddEvent(EVENT_INIT);
	
		
}

void main_deinit(){
	
}

void ports_init(void){
	
	/* Note to I/O Pin Registers
	     DDRxn high = Output
	     DDRxn low  = Input
	     PORTxn high = pull up, if Input
	     PORTxn low = no pull up, if Input
	     PORTxn high = driven high, if output
	     PORTxn low = driven low, if output
	*/
	
	
	/* Init Ports */
	// Default Pin config for PORT A,B,C,D,E,F (Input with pull up)
	DDRA=0x00;
	DDRB=0x00;
	DDRC&=~(0b10011111);;
	DDRD=0xFF;
	DDRE=0x00;
	DDRF=0x00;
	DDRG&=~(0b00011111); // Port G Pins 7,8 and 6 not written
	
	PORTA=0xFF;
	PORTB=0xFF;
	PORTC=0xFF;
	PORTD|=(0b10011111);
	PORTE=0xFF;
	PORTF=0xFF;
	PORTG|=(0b00011111); // Port G Pins 7,8 and 6 not written
	
}
