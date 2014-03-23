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
	
	
	uint8_t led_id;

	led_pins[LED_ID_AMS]=LED_PIN_AMS;
	led_pins[LED_ID_TV]=LED_PIN_TV;
	led_pins[LED_ID_TC]=LED_PIN_TC;
	led_pins[LED_ID_RECUP]=LED_PIN_RECUP;
	led_pins[LED_ID_KOBI]=LED_PIN_KOBI;
	led_pins[LED_ID_AD]=LED_PIN_AD;
	led_pins[LED_ID_LV_LOW]=LED_PIN_LV_LOW;
	led_pins[LED_ID_IMD]=LED_PIN_IMD;
	led_pins[LED_ID_BRAKE]=LED_PIN_IMD;
	led_pins[LED_ID_OK]=LED_PIN_OK;
	led_pins[LED_ID_START]=LED_PIN_START;
	
	led_dd[LED_ID_AMS]=LED_PIN_AMS;
	led_dd[LED_ID_TV]=LED_PIN_TV;
	led_dd[LED_ID_TC]=LED_PIN_TC;
	led_dd[LED_ID_RECUP]=LED_PIN_RECUP;
	led_dd[LED_ID_KOBI]=LED_PIN_KOBI;
	led_dd[LED_ID_AD]=LED_PIN_AD;
	led_dd[LED_ID_LV_LOW]=LED_PIN_LV_LOW;
	led_dd[LED_ID_IMD]=LED_PIN_IMD;
	led_dd[LED_ID_BRAKE]=LED_PIN_IMD;
	led_dd[LED_ID_OK]=LED_PIN_OK;
	led_dd[LED_ID_START]=LED_PIN_START;
	
	led_port[LED_ID_AMS]=LED_PIN_AMS;
	led_port[LED_ID_TV]=LED_PIN_TV;
	led_port[LED_ID_TC]=LED_PIN_TC;
	led_port[LED_ID_RECUP]=LED_PIN_RECUP;
	led_port[LED_ID_KOBI]=LED_PIN_KOBI;
	led_port[LED_ID_AD]=LED_PIN_AD;
	led_port[LED_ID_LV_LOW]=LED_PIN_LV_LOW;
	led_port[LED_ID_IMD]=LED_PIN_IMD;
	led_port[LED_ID_BRAKE]=LED_PIN_IMD;
	led_port[LED_ID_OK]=LED_PIN_OK;
	led_port[LED_ID_START]=LED_PIN_START;
	
	
	
	for(led_id=0;led_id<LED_NUMBER;led_id++){
		/* set data direction to output*/
		led_dd[led_id]|=((0x01)<<led_pins[led_id]);
		/* turn on led */
		led_port[led_id]|=((0x01)<<led_pins[led_id]);
	}


	led_state=0xFFFF;
	led_state_set(led_state);
	
}

void led_set(uint8_t led_id){	
	if(led_id>11) return; /* illegal id */
	led_port[led_id]|=((0x01)<<led_pins[led_id]);
}

void led_clear(uint8_t led_id){
	led_port[led_id]&=~((0x01)<<led_pins[led_id]);
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
	return (uint8_t) led_port[led_id]&((0x01)<<led_pins[led_id]);
}


