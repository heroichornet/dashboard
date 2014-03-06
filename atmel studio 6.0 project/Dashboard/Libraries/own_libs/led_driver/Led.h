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

#define LED_PIN(LED_ID_AMS)  1
#define LED_PIN(LED_ID_TV) 1
#define LED_PIN(LED_ID_TC) 2
#define LED_PIN(LED_ID_RECUP) 3
#define LED_PIN(LED_ID_KOBI) 4
#define LED_PIN(LED_ID_AD) 2
#define LED_PIN(LED_ID_LV_LOW) 4
#define LED_PIN(LED_ID_LV_AMS) 1
#define LED_PIN(LED_ID_IMD) 0
#define LED_PIN(LED_ID_BRAKE) 1
#define LED_PIN(LED_ID_OK) 0
#define LED_PIN(LED_ID_START) 7

#define LED_PORT(LED_ID_AMS) C
#define LED_PORT(LED_ID_TV) A
#define LED_PORT(LED_ID_TC) A
#define LED_PORT(LED_ID_RECUP) A
#define LED_PORT(LED_ID_KOBI) A
#define LED_PORT(LED_ID_AD) G
#define LED_PORT(LED_ID_LV_LOW) C
#define LED_PORT(LED_ID_AMS) C
#define LED_PORT(LED_ID_IMD) C
#define LED_PORT(LED_ID_BRAKE) G
#define LED_PORT(LED_ID_OK) G
#define LED_PORT(LED_ID_START) D

#define LED_DD(port) DDR##port##





void led_init(void);
void led_set(uint8_t led_id);
void led_clear(uint8_t led_id);
void led_toggle(uint8_t led_id);
void led_state_set(uint16_t led_new_state);
uint16_t led_state_return(void);
uint8_t led_is_set(uint8_t led_id);







#endif /* LED_H_ */