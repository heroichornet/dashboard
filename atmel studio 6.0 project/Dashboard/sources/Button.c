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
	
	MCUCR&=~(1<<PUD);
	
	
	/* COL 1 INPUT HIGH */
	DDRE|=~(1<<COLOUMN_1_PIN);
	PORTE|=(0x01)<<COLOUMN_1_PIN;
	/* COL 2 INPUT HIGH */
	DDRE|=~(1<<COLOUMN_2_PIN);
	PORTE|=(0x01)<<COLOUMN_2_PIN;
	/* COL 3 INPUT HIGH */
	DDRB|=~(1<<COLOUMN_3_PIN);
	PORTB|=(0x01)<<COLOUMN_3_PIN;
	
	
	/* ROW 1 INPUT, PULLUP */
	DDRE&=~(1<<ROW_1_PIN);
	PORTE|=1<<ROW_1_PIN;
	/* ROW 2 INPUT, PULLUP */
	DDRE&=~(1<<ROW_2_PIN);
	PORTE|=1<<ROW_2_PIN;
	/* ROW 3 INPUT, PULLUP */
	DDRC&=~(1<<ROW_3_PIN);
	PORTC|=1<<ROW_3_PIN;
	/* ROW 4 INPUT, PULLUP */
	DDRC&=~(1<<ROW_4_PIN);
	PORTC|=1<<ROW_4_PIN;
	
} /* end button_init */

void button_multiplex_cycle(void){
		
		
	col1_input_high();
	col2_input_high();
	col3_input_high();
	
	/* Cycle 1 */

	col2_input_high();
	col3_input_high();
	col1_low();
	
		
	button_read_col(0);

	/* Cycle 2 */

	
	col1_input_high();
	col3_input_high();
	col2_low();
	
	button_read_col(1);
	
	
	/* Cycle 3 */
	
	col1_input_high();
	col2_input_high();
	col3_low();	
	
	button_read_col(2);
	
			
	col1_input_high();
	col2_input_high();
	col3_input_high();
			
	
	
} /* end button_multiplex_cycle */


void button_read_col(uint8_t col){
		
		/* ROW 1 READ */
		uint8_t r1;
		uint8_t r2;
		uint8_t r3;
		uint8_t r4;
		
		r1=~((PINE>>4)&1);
		
		if(r1){
			button_pressed_current&=(r1)<<(0+col*BUTTON_ROW_NUMBER);
		}else{
			button_pressed_current|=(r1)<<(0+col*BUTTON_ROW_NUMBER);
		}
	
		/* ROW 2 READ */
		
		r2=~((PINE>>5)&1);		
		button_pressed_current|=(r2)<<(1+col*BUTTON_ROW_NUMBER);
		
		/* ROW 3 READ */
				
		r3=~((PINC>>6)&1);
		button_pressed_current|=(r3)<<(2+col*BUTTON_ROW_NUMBER);
		
		/* ROW 4 READ */
		r4=~((PINC3>>3)&1);
		button_pressed_current|=(r4)<<(3+col*BUTTON_ROW_NUMBER);
	
}/*end button_read_rows */


uint8_t button_get_button_state(uint8_t button_id){
	return (0x01)&(button_pressed_current>>(button_id));
}


void col1_input_high(void){
	/* COL 1 INPUT HIGH */
	DDRE&=~(1<<COLOUMN_1_PIN);
	PORTE|=(0x01)<<COLOUMN_1_PIN;
}

void col2_input_high(void){
	/* COL 2 INPUT HIGH */
	DDRE&=~(1<<COLOUMN_2_PIN);
	PORTE|=(0x01)<<COLOUMN_2_PIN;
}

void col3_input_high(void){
	/* COL 3 HIGH */
	DDRB&=~(1<<COLOUMN_3_PIN);
	PORTB|=(0x01)<<COLOUMN_3_PIN;
	
}	

void col1_low(void){
	/* COL 1 LOW */
	PORTE&=~(1<<COLOUMN_1_PIN);
	DDRE|=(0x01)<<COLOUMN_1_PIN;
}

void col2_low(void){
	/* COL 2 LOW */
	PORTE&=~(1<<COLOUMN_2_PIN);
	DDRE|=(0x01)<<COLOUMN_2_PIN;
}

void col3_low(void){
	/* COL 3 LOW  */
	PORTB&=~(1<<COLOUMN_3_PIN);
	DDRB|=(0x01)<<COLOUMN_3_PIN;

}