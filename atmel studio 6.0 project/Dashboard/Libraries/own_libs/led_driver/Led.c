/*
 * Led.c
 *
 * Created: 05.03.2014 14:14:49
 *  Author: michael
 */ 

#include <stdint.h>
#include <avr/io.h>


#include "Led.h"

void led_init(void){
	
	/* ToDo: mark pins as output*/
	
	
	uint8_t i;

	for(i=0;i<LED_NUMBER;i++){
		LED_PORT(i)|=(0x01)<<LED_PIN(i);
	}


	led_state=0xFFFF;
	led_state_set(led_state);
	
}

void led_set(uint8_t led_id){	
	if(led_id>11) return; /* illegal id */
	LED_PORT(led_id)|=(0x01)<<LED_PIN(led_id);
}

void led_clear(uint8_t led_id){
	LED_PORT(led_id)|=(0x01)&LED_PIN(led_id);
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

uint8_t led_is_set(uint8_t led_id){
	return (uint8_t) LED_PORT(led_id)&((0x01)<<LED_PIN(led_id));
}


