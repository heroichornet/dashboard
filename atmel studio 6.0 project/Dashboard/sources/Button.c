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
	

	button_pressed_previous=0x0000;
	
	/* enable pull-ups */
	
	
	/* COL 1 OUTPUT HIGH */
	button_dd[COLOUMN_1_ID]|=((0x01)<<button_pin[COLOUMN_1_ID]);
	button_port[COLOUMN_1_ID]|=((0x01)<<button_pin[COLOUMN_1_ID]);
	/* COL 2 OUTPUT HIGH */
	button_dd[COLOUMN_2_ID]|=((0x01)<<button_pin[COLOUMN_2_ID]);
	button_port[COLOUMN_2_ID]|=((0x01)<<button_pin[COLOUMN_2_ID]);
	/* COL 3 OUTPUT HIGH */
	button_dd[COLOUMN_3_ID]|=((0x01)<<button_pin[COLOUMN_3_ID]);
	button_port[COLOUMN_3_ID]|=((0x01)<<button_pin[COLOUMN_3_ID]);
	
	
	/* ROW 1 INPUT, PULLUP */
	button_dd[ROW_1_ID]&=~((0x01)<<button_pin[ROW_1_ID]);
	button_port[ROW_1_ID]|=((0x01)<<button_pin[ROW_1_ID]);
	/* ROW 2 INPUT, PULLUP */
	button_dd[ROW_2_ID]&=~((0x01)<<button_pin[ROW_2_ID]);
	button_port[ROW_2_ID]|=((0x01)<<button_pin[ROW_2_ID]);
	/* ROW 3 INPUT, PULLUP */
	button_dd[ROW_3_ID]&=~((0x01)<<button_pin[ROW_3_ID]);
	button_port[ROW_3_ID]|=((0x01)<<button_pin[ROW_3_ID]);
	/* ROW 4 INPUT, PULLUP */
	button_dd[ROW_4_ID]&=~((0x01)<<button_pin[ROW_4_ID]);
	button_port[ROW_4_ID]|=((0x01)<<button_pin[ROW_4_ID]);
} /* end button_init */

void button_multiplex_cycle(void){
		
	/* COL 1 LOW */
	button_port[COLOUMN_1_ID]&=~((0x01)<<button_pin[COLOUMN_1_ID]);
	/* COL 2 HIGH */
	/* already HIGH */
	/* COL 3 HIGH */
	/* already HIGH */
	
	button_read_col(0);
	
	/* COL 1 HIGH */
	button_port[COLOUMN_1_ID]|=((0x01)<<button_pin[COLOUMN_1_ID]);
	/* COL 2 LOW */
	button_port[COLOUMN_2_ID]&=~((0x01)<<button_pin[COLOUMN_2_ID]);
	/* COL 3 HIGH */
	/* already HIGH */
	
	button_read_col(1);
		
	/* COL 1 HIGH */
	/* already high */
	/* COL 2 HIGH */
	button_port[COLOUMN_2_ID]|=((0x01)<<button_pin[COLOUMN_2_ID]);
	/* COL 3 LOW  */
	button_port[COLOUMN_3_ID]&=~((0x01)<<button_pin[COLOUMN_3_ID]);

	button_read_col(2);
	
	/* set COL 3 HIGH, so that all are high again*/
	button_port[COLOUMN_3_ID]|=((0x01)<<button_pin[COLOUMN_3_ID]);
	
	
	/* debounce: check if button states are the same since last cycle*/
	
	button_pressed_current&=button_pressed_previous;
	
} /* end button_multiplex_cycle */


void button_read_col(uint8_t col){
		
		/* ROW 1 READ */
		if(button_pin[ROW_1_ID]==0x01) {
			button_pressed_current|=((0x01))<<(0+col*BUTTON_ROW_NUMBER);
		}
	
		/* ROW 2 READ */
		if(button_pin[ROW_2_ID]==0x01) {
			button_pressed_current|=((0x01))<<(1+col*BUTTON_ROW_NUMBER);
		}
		
		/* ROW 3 READ */
		if(button_pin[ROW_3_ID]==0x01) {
			button_pressed_current|=((0x01))<<(2+col*BUTTON_ROW_NUMBER);
		}
		
		/* ROW 4 READ */
		if(button_pin[ROW_4_ID]==0x01) {
			button_pressed_current|=((0x01))<<(3+col*BUTTON_ROW_NUMBER);
		}
	
}/*end button_read_rows */


uint8_t button_get_button_state(uint8_t button_id){
	return (0x01)&(button_pressed_current>>(button_id));
}