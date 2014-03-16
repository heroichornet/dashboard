/*
 * Led.h
 *
 * Created: 05.03.2014 14:15:48
 *  Author: michael
 */ 


#ifndef LED_H_
#define LED_H_

#define HAS_LEDS (1)

uint16_t led_state;

#define LED_NUMBER 11

#define LED_ID_AMS 0
#define LED_ID_TV 1
#define LED_ID_TC 2
#define LED_ID_RECUP 3
#define LED_ID_KOBI 4
#define LED_ID_AD 5
#define LED_ID_LV_LOW 6
#define LED_ID_LV_AMS 7
#define LED_ID_IMD 8
#define LED_ID_BRAKE 9
#define LED_ID_OK 10
#define LED_ID_START 11

#define LED_PIN_AMS  0
#define LED_PIN_TV 1
#define LED_PIN_TC 2
#define LED_PIN_RECUP 3
#define LED_PIN_KOBI 4
#define LED_PIN_AD 2
#define LED_PIN_LV_LOW 4
#define LED_PIN_LV_AMS 1
#define LED_PIN_IMD 0
#define LED_PIN_BRAKE 1
#define LED_PIN_OK 0
#define LED_PIN_START 7

#define LED_PORT_AMS PORTC
#define LED_PORT_TV PORTA
#define LED_PORT_TC PORTA
#define LED_PORT_RECUP PORTA
#define LED_PORT_KOBI PORTA
#define LED_PORT_AD PORTG
#define LED_PORT_LV_LOW PORTC
#define LED_PORT_LV_AMS PORTC
#define LED_PORT_IMD PORTC
#define LED_PORT_BRAKE PORTG
#define LED_PORT_OK PORTG
#define LED_PORT_START PORTD

#define LED_DD_AMS DDRC
#define LED_DD_TV DDRA
#define LED_DD_TC DDRA
#define LED_DD_RECUP DDRA
#define LED_DD_KOBI DDRA
#define LED_DD_AD DDRG
#define LED_DD_LV_LOW DDRC
#define LED_DD_LV_AMS DDRC
#define LED_DD_IMD DDRC
#define LED_DD_BRAKE DDRG
#define LED_DD_OK DDRG
#define LED_DD_START DDRD

#define LED_PIN(LED_ID_AMS) LED_PIN_AMS
#define LED_PIN(LED_ID_TV) LED_PIN_TV
#define LED_PIN(LED_ID_TC) LED_PIN_TC
#define LED_PIN(LED_ID_RECUP) LED_PIN_RECUP
#define LED_PIN(LED_ID_KOBI) LED_PIN_KOBI
#define LED_PIN(LED_ID_AD) LED_PIN_AD
#define LED_PIN(LED_ID_LV_LOW) LED_PIN_LV_LOW
#define LED_PIN(LED_ID_IMD) LED_PIN_IMD
#define LED_PIN(LED_ID_BRAKE) LED_PIN_IMD
#define LED_PIN(LED_ID_OK) LED_PIN_OK
#define LED_PIN(LED_ID_START) LED_PIN_START

#define LED_PORT(LED_ID_AMS) LED_PORT_AMS
#define LED_PORT(LED_ID_TV) LED_PORT_TV
#define LED_PORT(LED_ID_TC) LED_PORT_TC
#define LED_PORT(LED_ID_RECUP) LED_PORT_RECUP
#define LED_PORT(LED_ID_KOBI) LED_PORT_KOBI
#define LED_PORT(LED_ID_AD) LED_PORT_AD
#define LED_PORT(LED_ID_LV_LOW) LED_PORT_LV_LOW
#define LED_PORT(LED_ID_IMD) LED_PORT_IMD
#define LED_PORT(LED_ID_BRAKE) LED_PORT_IMD
#define LED_PORT(LED_ID_OK) LED_PORT_OK
#define LED_PORT(LED_ID_START) LED_PORT_START

#define LED_DD(LED_ID_AMS) LED_DD_AMS
#define LED_DD(LED_ID_TV) LED_DD_TV
#define LED_DD(LED_ID_TC) LED_DD_TC
#define LED_DD(LED_ID_RECUP) LED_DD_RECUP
#define LED_DD(LED_ID_KOBI) LED_DD_KOBI
#define LED_DD(LED_ID_AD) LED_DD_AD
#define LED_DD(LED_ID_LV_LOW) LED_DD_LV_LOW
#define LED_DD(LED_ID_IMD) LED_DD_IMD
#define LED_DD(LED_ID_BRAKE) LED_DD_IMD
#define LED_DD(LED_ID_OK) LED_DD_OK
#define LED_DD(LED_ID_START) LED_DD_START



void led_init(void);
void led_set(uint8_t led_id);
void led_clear(uint8_t led_id);
void led_toggle(uint8_t led_id);
void led_state_set(uint16_t led_new_state);
uint16_t led_state_return(void);
uint8_t led_is_set(uint8_t led_id);







#endif /* LED_H_ */