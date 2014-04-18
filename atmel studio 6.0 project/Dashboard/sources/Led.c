/*
 * Led.c
 *
 * Created: 05.03.2014 14:14:49
 *  Author: michael
 */ 

#include <stdint.h>
#include <avr/io.h>


#include "../includes/Led.h"

void led_init(void){
	
	
	// Set Data Direction of LED I/O Pins 
	
	DDRC|=(0x01)<<LED_PIN_AMS;/* set data direction to output*/
	DDRA|=(0x01)<<LED_PIN_TV;/* set data direction to output*/
	DDRA|=(0x01)<<LED_PIN_RECUP;/* set data direction to output*/
	DDRA|=(0x01)<<LED_PIN_KOBI;/* set data direction to output*/
	DDRG|=(0x01)<<LED_PIN_AD;/* set data direction to output*/
	DDRC|=(0x01)<<LED_PIN_LV_LOW;/* set data direction to output*/
	DDRC|=(0x01)<<LED_PIN_IMD;/* set data direction to output*/
	DDRG|=(0x01)<<LED_PIN_BRAKE;/* set data direction to output*/
	DDRG|=(0x01)<<LED_PIN_OK;/* set data direction to output*/
	DDRD|=(0x01)<<LED_PIN_START;/* set data direction to output*/
	DDRA|=(0x01)<<LED_PIN_TC;/* set data direction to output*/
	
	// Set I/O Pins High (all leds on)	
	PORTC|=(0x01)<<LED_PIN_AMS;	/* turn on led */
	PORTA|=(0x01)<<LED_PIN_TV;/* turn on led */
	PORTA|=(0x01)<<LED_PIN_RECUP;/* turn on led */
	PORTA|=(0x01)<<LED_PIN_KOBI;/* turn on led */
	PORTG|=(0x01)<<LED_PIN_AD;/* turn on led */
	PORTC|=(0x01)<<LED_PIN_LV_LOW;/* turn on led */
	PORTC|=(0x01)<<LED_PIN_IMD;/* turn on led */
	PORTG|=(0x01)<<LED_PIN_BRAKE;/* turn on led */
	PORTG|=(0x01)<<LED_PIN_OK;/* turn on led */
	PORTD|=(0x01)<<LED_PIN_START;/* turn on led */
	PORTA|=(0x01)<<LED_PIN_TC;/* turn on led*/
	
	
	led_state=0xFFFF;
	led_state_set(led_state);
	
}

void led_set(uint8_t led_id){	
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
				PORTC|=(0x01)<<LED_PIN_AMS;	/* turn on led */
			break;
		case LED_ID_TV:
				PORTA|=(0x01)<<LED_PIN_TV;/* turn on led */
			break;
		case LED_ID_RECUP:
				PORTA|=(0x01)<<LED_PIN_RECUP;/* turn on led */
			break;
		case LED_ID_KOBI:
				PORTA|=(0x01)<<LED_PIN_KOBI;/* turn on led */
				break;
		case LED_ID_AD:
				PORTG|=(0x01)<<LED_PIN_AD;/* turn on led */
				break;
		case LED_ID_LV_LOW:
				PORTC|=(0x01)<<LED_PIN_LV_LOW;/* turn on led */
				break;
		case LED_ID_IMD:
				PORTC|=(0x01)<<LED_PIN_IMD;/* turn on led */
				break;
		case LED_ID_BRAKE:
				PORTG|=(0x01)<<LED_PIN_BRAKE;/* turn on led */
				break;
		case LED_ID_OK:
				PORTG|=(0x01)<<LED_PIN_OK;/* turn on led */
				break;
		case LED_ID_START:
				PORTD|=(0x01)<<LED_PIN_START;/* turn on led */
				break;
		case LED_ID_TC:
				PORTA|=(0x01)<<LED_PIN_TC;/* turn on led*/
		default:
				break;
		}				
				
				
}

void led_clear(uint8_t led_id){
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
				PORTC&=~(1<<LED_PIN_AMS);	/* turn off led */
				break;
		case LED_ID_TV:
				PORTA&=~(1<<LED_PIN_TV);/* turn off led */
				break;
		case LED_ID_RECUP:
				PORTA&=~(1<<LED_PIN_RECUP);/* turn off led */
				break;
		case LED_ID_KOBI:
				PORTA&=~(1<<LED_PIN_KOBI);/* turn off led */
				break;
		case LED_ID_AD:
				PORTG&=~(1<<LED_PIN_AD);/* turn off led */
				break;
		case LED_ID_LV_LOW:
				PORTC&=~(0x01)<<LED_PIN_LV_LOW;/* turn off led */
				break;
		case LED_ID_IMD:
				PORTC&=~(1<<LED_PIN_IMD);/* turn off led */
				break;
		case LED_ID_BRAKE:
				PORTG&=~(0x01)<<LED_PIN_BRAKE;/* turn off led */
				break;
		case LED_ID_OK:
				PORTG&=~(1<<LED_PIN_OK);/* turn off led */
				break;
		case LED_ID_START:
				PORTD&=~(1<<LED_PIN_START);/* turn off led */
				break;
		case LED_ID_TC:
				PORTA|=(0x01)<<LED_PIN_TC;/* turn off led*/
		default:
				break;
	}			
}				
			
uint8_t led_is_set(uint8_t led_id){
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
			return 0x01==(PORTC>>LED_PIN_AMS);	
			break;
		case LED_ID_TV:
			return 0x01==(PORTA>>LED_PIN_TV);
			break;
		case LED_ID_RECUP:
			return 0x01==(PORTA>>LED_PIN_RECUP);
			break;
		case LED_ID_KOBI:
			return 0x01==(PORTA>>LED_PIN_KOBI);
			break;
		case LED_ID_AD:
			return 0x01==(PORTA>>LED_PIN_AD);
			break;
		case LED_ID_LV_LOW:
			return 0x01==(PORTC>>LED_PIN_LV_LOW);
			break;
		case LED_ID_IMD:
			return 0x01==(PORTC>>LED_PIN_IMD);
			break;
		case LED_ID_BRAKE:
			return 0x01==(PORTG>>LED_PIN_BRAKE);
			break;
		case LED_ID_OK:
			return 0x01==(PORTG>>LED_PIN_OK);
			break;
		case LED_ID_START:
			return 0x01==(PORTD>>LED_PIN_START);
			break;
		case LED_ID_TC:
			return 0x01==(PORTA>>LED_PIN_TC);
			break;
		default:
		break;
	}
}



void led_toggle(uint8_t led_id){
	if(led_is_set(led_id)){
		led_clear(led_id);
	}else{
		led_set(led_id);
	}
}


void led_state_set(uint16_t led_new_state){
	uint8_t i;
	for(i=0;i<LED_NUMBER;i++){
		if(led_new_state&(1<<i)){
			led_set(i);
		}
	}
}

uint16_t led_state_return(void){
		uint8_t i;
		uint16_t led_state;
		for(i=0;i<LED_NUMBER;i++){
			led_state|=led_is_set(i)<<i;
		}
	return led_state;
}


