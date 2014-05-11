/*
 * Buzzer.c
 *
 * Created: 06.03.2014 09:55:53
 *  Author: michael
 */ 

#include <stdint.h>
#include <avr/io.h>
#include "../includes/Buzzer.h"

#include <util/delay.h>

uint8_t buzzer_count=0;
uint8_t buzz_cycles=0;

void buzzer_init( void )
{
	DDRA|=(1)<<BUZZER_PIN;
	PORTA&=~((1)<<BUZZER_PIN);
}

void buzzer_on( void )
{
	PORTA|=1<<BUZZER_PIN;
}

void buzzer_off( void )
{
	PORTA&=~(1<<BUZZER_PIN);
}


void buzzer_buzz_ready_to_drive(){
	buzzer_on();
	buzz_cycles=18;
	buzzer_count=4;	
}

