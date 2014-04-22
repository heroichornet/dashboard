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
	
	DDRD|=(0x01)<<(7);/* set data direction to output*/
	DDRA|=(0x01)<<(1);/* set data direction to output*/
	DDRA|=(0x01)<<(3);/* set data direction to output*/
	DDRA|=(0x01)<<(4);/* set data direction to output*/
	DDRG|=(0x01)<<(2);/* set data direction to output*/
	DDRC|=(0x01)<<(4);/* set data direction to output*/
	DDRC|=(0x01)<<(0);/* set data direction to output*/
	DDRG|=(0x01)<<(1);/* set data direction to output*/
	DDRG|=(0x01)<<(0);/* set data direction to output*/
	DDRC|=(0x01)<<(1);/* set data direction to output*/
	DDRA|=(0x01)<<(2);/* set data direction to output*/
	
	// turn off all leds to start with	
	led_clear_all();
	
}

void led_set(uint8_t led_id){	
	if(led_id>11) return; /* illegal id */
	
	switch(led_id){
		case LED_ID_AMS:
				PORTD|=(0x01)<<(7);	/* turn on led */
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
				PORTG|=(0x01)<<(0);/* turn on led */
				break;
		case LED_ID_START:
				PORTC|=(0x01)<<(1);/* turn on led */
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
				PORTD&=~(1<<(7));	/* turn off led */
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
				PORTG&=~(1<<(0));/* turn off led */
				break;
		case LED_ID_START:
				PORTC&=~(1<<(1));/* turn off led */
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
			return 0x01==(PORTD>>(7));	
			break;
		case LED_ID_TC:
			return 0x01==(PORTA>>(1));
			break;
		case LED_ID_RECUP:
			return 0x01==(PORTA>>(3));
			break;
		case LED_ID_AD:
			return 0x01==(PORTA>>(4));
			break;
		case LED_ID_KOBI:
			return 0x01==(PORTG>>(2));
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
			return 0x01==(PORTG>>(0));
			break;
		case LED_ID_START:
			return 0x01==(PORTC>>(1));
			break;
		case LED_ID_TV:
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




void led_percent_bar(uint8_t percent){
//input between 0 and 100 , rounded to 10%

	uint8_t rp=percent/10; //rounded percent
	
	
	if(rp<19){
		//clear all leds
		led_clear_all();
	}
	
	if(rp>19){
		// turn on IMD and AD
		led_set(LED_ID_IMD);
		led_set(LED_ID_AD);
	}
	
	if(rp>39){
		// turn on LV LOW and KOBI	
		led_set(LED_ID_LV_LOW);
		led_set(LED_ID_KOBI);
	}		
	
	if(rp>59){
		//turn on AMS and RECUP
		led_set(LED_ID_AMS);
		led_set(LED_ID_RECUP);
	}		
	
	if(rp>79){
		//turn on OK and TV
		led_set(LED_ID_OK);
		led_set(LED_ID_TV);
	}
	
	if(rp>99){
		//turn on Brake and TC
		led_set(LED_ID_BRAKE);
		led_set(LED_ID_TC);
	}		
		
	
	
	
}

void led_clear_all(void){
	uint8_t j=0;
	for(j;j<12;j++){
		led_clear(j);
	}
}