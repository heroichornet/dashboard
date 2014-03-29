/*
 * Buzzer.c
 *
 * Created: 06.03.2014 09:55:53
 *  Author: michael
 */ 

#include <stdint.h>
#include <avr/io.h>
#include "../includes/Buzzer.h"

void buzzer_init( void )
{
	PORTA|=(0x01)<<BUZZER_PIN;
}

void buzzer_on( void )
{
	PORTA|=(0x01)<<BUZZER_PIN;
}

void buzzer_off( void )
{
	PORTA&=~(0x01)<<BUZZER_PIN;
}

void buzzer_buzz( uint8_t time_ms )
{
	/* QUICK shitty implementation */
	/* ToDO use timer */
	
	buzzer_on();
	int i;
	for(i=0;i<time_ms*100;i++){
		
	}
	
	buzzer_off();
}

void buzzer_puls( uint8_t freq_ms, uint8_t time_ms )
{
	
}
