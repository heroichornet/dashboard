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
	
	DDRC|=(0x01)<<(7);/* set data direction to output*/
	DDRA|=(0x01)<<(1);/* set data direction to output*/
	DDRA|=(0x01)<<(3);/* set data direction to output*/
	DDRA|=(0x01)<<(4);/* set data direction to output*/
	DDRG|=(0x01)<<(2);/* set data direction to output*/
	DDRC|=(0x01)<<(4);/* set data direction to output*/
	DDRC|=(0x01)<<(0);/* set data direction to output*/
	DDRG|=(0x01)<<(1);/* set data direction to output*/
	DDRG|=(0x01)<<(1);/* set data direction to output*/
	DDRD|=(0x01)<<(1);/* set data direction to output*/
	DDRA|=(0x01)<<(2);/* set data direction to output*/
	
	// Set I/O Pins High (all leds on)	
	PORTC|=(0x01)<<(7);	/* turn on led */
	PORTA|=(0x01)<<(1);/* turn on led */
	PORTA|=(0x01)<<(3);/* turn on led */
	PORTA|=(0x01)<<(4);/* turn on led */
	PORTG|=(0x01)<<(2);/* turn on led */
	PORTC|=(0x01)<<(4);/* turn on led */
	PORTC|=(0x01)<<(0);/* turn on led */
	PORTG|=(0x01)<<(1);/* turn on led */
	PORTG|=(0x01)<<(1);/* turn on led */
	PORTD|=(0x01)<<(1);/* turn on led */
	PORTA|=(0x01)<<(2);/* turn on led*/
	
	
	led_state=0xFFFF;
	led_state_set(led_state);
	
}

void led_set(uint8_t led_id){	
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
				PORTC|=(0x01)<<(7);	/* turn on led */
			break;
		case LED_ID_TV:
				PORTA|=(0x01)<<(1);/* turn on led */
			break;
		case LED_ID_RECUP:
				PORTA|=(0x01)<<(3);/* turn on led */
			break;
		case LED_ID_KOBI:
				PORTA|=(0x01)<<(4);/* turn on led */
				break;
		case LED_ID_AD:
				PORTG|=(0x01)<<(2);/* turn on led */
				break;
		case LED_ID_LV_LOW:
				PORTC|=(0x01)<<(4);/* turn on led */
				break;
		case LED_ID_IMD:
				PORTC|=(0x01)<<(0);/* turn on led */
				break;
		case LED_ID_BRAKE:
				PORTG|=(0x01)<<(1);/* turn on led */
				break;
		case LED_ID_OK:
				PORTG|=(0x01)<<(1);/* turn on led */
				break;
		case LED_ID_START:
				PORTD|=(0x01)<<(1);/* turn on led */
				break;
		case LED_ID_TC:
				PORTA|=(0x01)<<(2);/* turn on led*/
		default:
				break;
		}				
				
				
}

void led_clear(uint8_t led_id){
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
				PORTC&=~(1<<(7));	/* turn off led */
				break;
		case LED_ID_TV:
				PORTA&=~(1<<(1));/* turn off led */
				break;
		case LED_ID_RECUP:
				PORTA&=~(1<<(3));/* turn off led */
				break;
		case LED_ID_KOBI:
				PORTA&=~(1<<(4));/* turn off led */
				break;
		case LED_ID_AD:
				PORTG&=~(1<<(2));/* turn off led */
				break;
		case LED_ID_LV_LOW:
				PORTC&=~(1<<(4));/* turn off led */
				break;
		case LED_ID_IMD:
				PORTC&=~(1<<(0));/* turn off led */
				break;
		case LED_ID_BRAKE:
				PORTG&=~(1<<(1));/* turn off led */
				break;
		case LED_ID_OK:
				PORTG&=~(1<<(1));/* turn off led */
				break;
		case LED_ID_START:
				PORTD&=~(1<<(1));/* turn off led */
				break;
		case LED_ID_TC:
				PORTA&=~(1<<(2));/* turn off led*/
		default:
				break;
	}			
}				
			
uint8_t led_is_set(uint8_t led_id){
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
			return 0x01==(PORTC>>(7));	
			break;
		case LED_ID_TV:
			return 0x01==(PORTA>>(1));
			break;
		case LED_ID_RECUP:
			return 0x01==(PORTA>>(3));
			break;
		case LED_ID_KOBI:
			return 0x01==(PORTA>>(4));
			break;
		case LED_ID_AD:
			return 0x01==(PORTA>>(2));
			break;
		case LED_ID_LV_LOW:
			return 0x01==(PORTC>>(4));
			break;
		case LED_ID_IMD:
			return 0x01==(PORTC>>(0));
			break;
		case LED_ID_BRAKE:
			return 0x01==(PORTG>>(1));
			break;
		case LED_ID_OK:
			return 0x01==(PORTG>>(1));
			break;
		case LED_ID_START:
			return 0x01==(PORTD>>(1));
			break;
		case LED_ID_TC:
			return 0x01==(PORTA>>(2));
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


