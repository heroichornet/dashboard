/*
 * Button.c
 *
 * Created: 06.03.2014 09:56:32
 *  Author: michael
 */ 

#include <stdint.h>
#include <avr/io.h>
#include "../includes/Button.h"
#include "../includes/Display.h"
#include "../includes/Led.h"

 uint8_t button_key1=0;
 uint8_t button_key2=0;

void button_init( void )
{

	
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
	
	uint8_t i;
	for(i=0;i<12;i++){
		button_released[i]=1;
	}
	
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
	
	uint8_t i=0;
	for(i;i<12;i++){
		if(button_previous_state[i]==0 && button_state[i]==1 && button_released[i]==1){
			button_press[i]=1;
			button_released[i]=0;
		}
		if(button_previous_state[i]==1 && button_state[i]==0 && button_released[i]==0){
			button_released[i]=1;
		}			
	}
	
	
	buttons_react();
	
	
	memcpy(button_previous_state,button_state,12);
	
} /* end button_multiplex_cycle */


void button_read_col(uint8_t col){
		
		#define BUTTON_COUNTER_VALUE 7
		
		uint8_t r1=0;
		uint8_t r2=0;
		uint8_t r3=0;
		uint8_t r4=0;
				
		/* ROW 1 READ */

		
		r1=PINE;
		
		if(!((r1>>ROW_1_PIN)&1)){
			button_state[0+col*BUTTON_ROW_NUMBER]=1;
		}else{
			button_state[0+col*BUTTON_ROW_NUMBER]=0;
		}
	
		/* ROW 2 READ */
		
		r2=PINE;
		if(!((r2>>ROW_2_PIN)&1)){		
			button_state[1+col*BUTTON_ROW_NUMBER]=1;
		}else{
			button_state[1+col*BUTTON_ROW_NUMBER]=0;
		}
		
		/* ROW 3 READ */
		
		r3=PINC;
		if(!((r3>>ROW_3_PIN)&1)){	
			button_state[2+col*BUTTON_ROW_NUMBER]=1;
		}else{
			button_state[2+col*BUTTON_ROW_NUMBER]=0;
			
		}
		
		/* ROW 3 READ */
				
		r4=PINC;
		if(!((r4>>ROW_4_PIN)&1)){
			button_state[3+col*BUTTON_ROW_NUMBER]=1;
			
		}else{
			button_state[3+col*BUTTON_ROW_NUMBER]=0;
		}
		

	
}/*end button_read_rows */


uint8_t button_get_button_state(uint8_t button_id){
	return button_state[button_id];
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

void buttons_react(void){

	
	if(button_press[BUTTON_ID_UP]){
		button_press[BUTTON_ID_UP]=0;
		display_down();
	}
	
	if(button_press[BUTTON_ID_DOWN]){
		button_press[BUTTON_ID_DOWN]=0;
		display_up();		
	}
	
	/* LEDS on BUTTONS */
	if(button_state[BUTTON_ID_TV]){
		led_set(LED_ID_TC);
	}else{
		led_clear(LED_ID_TC);
	}
	if(button_state[BUTTON_ID_TC]){
		led_set(LED_ID_TV);
	}else{
		led_clear(LED_ID_TV);
	}
	
	if(button_state[BUTTON_ID_RECUP]){
		led_set(LED_ID_RECUP);
	}else{
		led_clear(LED_ID_RECUP);
	}
	
	if(button_state[BUTTON_ID_AD]){
		led_set(LED_ID_KOBI);
	}else{
		led_clear(LED_ID_KOBI);
	}
	
	if(button_state[BUTTON_ID_KOBI]){
		led_set(LED_ID_AD);
	}else{
		led_clear(LED_ID_AD);
	}
		
		
	
	
	button_key1=0;
	if(button_state[BUTTON_ID_TMS]){
		button_key1|=1;
	}
	if(button_state[BUTTON_ID_TV]){
		button_key1|=1<<1;
	}
	if(button_state[BUTTON_ID_TC]){
		button_key1|=1<<2;
	}
	if(button_state[BUTTON_ID_RECUP]){
		button_key1|=1<<3;
	}
	if(button_state[BUTTON_ID_KOBI]){
		button_key1|=1<<4;
	}
	if(button_state[BUTTON_ID_AD]){
		button_key1|=1<<5;
	}
	
	button_key2=0;
	
	if(button_state[BUTTON_ID_PLUS]){
		button_key2|=1<<1;
	}
	if(button_state[BUTTON_ID_MINUS]){
		button_key2|=1;
	}
	
	if(button_state[BUTTON_ID_FLAPPY_DRS]){
		button_key2|=1<<2;
	}
	
	if(button_state[BUTTON_ID_FLAPPY_RADIO]){
		button_key2|=1<<3;
	}
	
	if(button_state[BUTTON_ID_UP]){
		button_key2|=1<<4;
	}
	
	if(button_state[BUTTON_ID_DOWN]){
		button_key2|=1<<5;
	}



	
}