/*
 * Led.h
 *
 * Created: 05.03.2014 14:15:48
 *  Author: michael
 */ 


#ifndef LED_H_
#define LED_H_

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

#define LED_ADDRESS(LED_ID_AMS)  PORTC1
#define LED_ADDRESS(LED_ID_TV) PORTA1
#define LED_ADDRESS(LED_ID_TC) PORTA2
#define LED_ADDRESS(LED_ID_RECUP) PORTA3
#define LED_ADDRESS(LED_ID_KOBI) PORTA4
#define LED_ADDRESS(LED_ID_AD) PORTG2
#define LED_ADDRESS(LED_ID_LV_LOW) PORTC4
#define LED_ADDRESS(LED_ID_LV_AMS) PORTC1
#define LED_ADDRESS(LED_ID_IMD) PORTC0
#define LED_ADDRESS(LED_ID_BRAKE) PORTG1
#define LED_ADDRESS(LED_ID_OK) PORTG0
#define LED_ADDRESS(LED_ID_START) PORTD7

#define LED_PORT(LED_ID_AMS) PORTC
#define LED_PORT(LED_ID_TV) PORTA
#define LED_PORT(LED_ID_TC) PORTA
#define LED_PORT(LED_ID_RECUP) PORTA
#define LED_PORT(LED_ID_KOBI) PORTA
#define LED_PORT(LED_ID_AD) PORTG
#define LED_PORT(LED_ID_LV_LOW) PORTC
#define LED_PORT(LED_ID_AMS) PORTC
#define LED_PORT(LED_ID_IMD) PORTC
#define LED_PORT(LED_ID_BRAKE) PORTG
#define LED_PORT(LED_ID_OK) PORTG
#define LED_PORT(LED_ID_START) PORTD




void led_init(void);
void led_set(uint8_t led_id);
void led_clear(uint8_t led_id);
void led_toggle(uint8_t led_id);
void led_state_set(uint16_t led_new_state);
uint16_t led_state_return(void);
uint8_t led_is_set(uint8_t led_id);







#endif /* LED_H_ */