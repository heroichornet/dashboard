/*
 * Button.c
 *
 * Created: 06.03.2014 09:56:32
 *  Author: michael
 */ 

#include <stdint.h>
#include <avr/io.h>
#include "../includes/Button.h"


void button_init( void )
{

	button_pressed_previous=0x0000;
	
	/* enable pull-ups */
	
	MCUCR&=~(0x01)<<PUD;
	
	
	/* COL 1 OUTPUT HIGH */
	DDRE|=(0x01)<<COLOUMN_1_PIN;
	PORTE|=(0x01)<<COLOUMN_1_PIN;
	/* COL 2 OUTPUT HIGH */
	DDRE|=(0x01)<<COLOUMN_2_PIN;
	PORTE|=(0x01)<<COLOUMN_2_PIN;
	/* COL 3 OUTPUT HIGH */
	DDRB|=(0x01)<<COLOUMN_3_PIN;
	PORTB|=(0x01)<<COLOUMN_3_PIN;
	
	
	/* ROW 1 INPUT, PULLUP */
	DDRE&=~(0x01)<<ROW_1_PIN;
	PORTE|=(0x01)<<ROW_1_PIN;
	/* ROW 2 INPUT, PULLUP */
	DDRE&=~(0x01)<<ROW_2_PIN;
	PORTE|=(0x01)<<ROW_2_PIN;
	/* ROW 3 INPUT, PULLUP */
	DDRC&=~(0x01)<<ROW_3_PIN;
	PORTC|=(0x01)<<ROW_3_PIN;
	/* ROW 4 INPUT, PULLUP */
	DDRC&=~(0x01)<<ROW_4_PIN;
	PORTC|=(0x01)<<ROW_4_PIN;
	
} /* end button_init */

void button_multiplex_cycle(void){
		
	/* COL 1 LOW */
	PORTE&=~(0x01)<<COLOUMN_1_PIN;
	/* COL 2 HIGH */
	/* already HIGH */
	/* COL 3 HIGH */
	/* already HIGH */
	
	button_read_col(0);
	
	/* COL 1 HIGH */
	PORTE|=(0x01)<<COLOUMN_1_PIN;
	/* COL 2 LOW */
	PORTE&=~(0x01)<<COLOUMN_2_PIN;
	/* COL 3 HIGH */
	/* already HIGH */
	
	button_read_col(1);
		
	/* COL 1 HIGH */
	/* already high */
	/* COL 2 HIGH */
	PORTE|=(0x01)<<COLOUMN_2_PIN;
	/* COL 3 LOW  */
	PORTB&=~(0x01)<<COLOUMN_3_PIN;

	button_read_col(2);
	
	/* set COL 3 HIGH, so that all are high again*/
	PORTB|=(0x01)<<COLOUMN_3_PIN;
	
	
	/* debounce: check if button states are the same since last cycle*/
	
	button_pressed_current&=button_pressed_previous;
	
} /* end button_multiplex_cycle */


void button_read_col(uint8_t col){
		
		/* ROW 1 READ */
		button_pressed_current|=(0x01)<(0+col*BUTTON_ROW_NUMBER);
	
		/* ROW 2 READ */
		button_pressed_current|=(0x01)<<(1+col*BUTTON_ROW_NUMBER);
		
		/* ROW 3 READ */
		button_pressed_current|=(0x01)<<(2+col*BUTTON_ROW_NUMBER);
		
		/* ROW 4 READ */
		button_pressed_current|=(0x01)<<(3+col*BUTTON_ROW_NUMBER);
	
}/*end button_read_rows */


uint8_t button_get_button_state(uint8_t button_id){
	return (0x01)&(button_pressed_current>>(button_id));
}