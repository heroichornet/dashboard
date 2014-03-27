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
	uint8_t port[]={
		[ROW_1_ID] = PORTE,
		[ROW_2_ID] = PORTE,
		[ROW_3_ID] = PORTC,
		[ROW_4_ID] = PORTC,
		[COLOUMN_1_ID] = PORTE,
		[COLOUMN_2_ID] = PORTE,
		[COLOUMN_3_ID] =PORTB
	};
	
	uint8_t pin[]={
		[ROW_1_ID] = 4,
		[ROW_2_ID] = 5,
		[ROW_3_ID] = 6,
		[ROW_4_ID] = 3,
		[COLOUMN_1_ID] = 6,
		[COLOUMN_2_ID] = 7,
		[COLOUMN_3_ID] = 0
	};
	uint8_t dd[]={
		[ROW_1_ID] = DDRE,
		[ROW_2_ID] = DDRE,
		[ROW_3_ID] = DDRC,
		[ROW_4_ID] = DDRC,
		[COLOUMN_1_ID] = DDRE,
		[COLOUMN_2_ID] = DDRE,
		[COLOUMN_3_ID] = DDRB
	};

	
	button_port=port;
	button_pin=pin;
	button_dd=dd;
	

	button_pressed=0x00;
	
	/* enable pull-ups */
	
	
	/* COL 1 OUTPUT HIGH */
	button_port[COLOUMN_1_ID]&=~((0x01)<<button_pin[COLOUMN_1_ID]);
	
	button_port[COLOUMN_1_ID]&=~((0x01)<<button_pin[COLOUMN_1_ID]);
	/* COL 2 OUTPUT HIGH */
	button_port[COLOUMN_2_ID]&=~((0x01)<<button_pin[COLOUMN_2_ID]);
	/* COL 3 OUTPUT HIGH */
	button_port[COLOUMN_3_ID]&=~((0x01)<<button_pin[COLOUMN_3_ID]);
	
	/* ROW 1 INPUT, PULLUP */

	/* ROW 2 INPUT, PULLUP */
	/* ROW 3 INPUT, PULLUP */
	/* ROW 4 INPUT, PULLUP */
} /* end button_init */

void button_multiplex_cycle(void){
	
	/* COL 1 LOW */
	/* COL 2 HIGH */
	/* COL 3 HIGH */
	/* ROW 1 READ */
	/* ROW 2 READ */
	/* ROW 3 READ */
	/* ROW 4 READ */
	
	/* COL 1 HIGH */
	/* COL 2 LOW */
	/* COL 3 HIGH */
	/* ROW 1 READ */
	/* ROW 2 READ */
	/* ROW 3 READ */
	/* ROW 4 READ */
	
	/* COL 1 HIGH */
	/* COL 2 HIGH */
	/* COL 3 LOW  */
	/* ROW 1 READ */
	/* ROW 2 READ */
	/* ROW 3 READ */
	/* ROW 4 READ */
	
	
} /* end button_multiplex_cycle */