/*
 * Led.h
 *
 * Created: 05.03.2014 14:15:48
 *  Author: michael
 */ 


#ifndef LED_H_
#define LED_H_

uint16_t led_state;

#define LED_NUMBER				(11)

/* Error LEDS */

#define LED_ID_AMS				(0)
#define LED_ID_LV_LOW			(1)
#define LED_ID_IMD				(2)
#define LED_ID_OK				(3)
#define LED_ID_BRAKE			(4)


/* Button LEDS */

#define LED_ID_TV				(5)
#define LED_ID_TC				(6)
#define LED_ID_RECUP			(7)
#define LED_ID_KOBI				(8)
#define LED_ID_AD				(9)
#define LED_ID_START			(10)


#define LED_PIN_AMS				(1)
#define LED_PIN_TV				(1)
#define LED_PIN_TC				(2)
#define LED_PIN_RECUP			(3)
#define LED_PIN_KOBI			(4)
#define LED_PIN_AD				(2)
#define LED_PIN_LV_LOW			(4)
#define LED_PIN_IMD				(0)
#define LED_PIN_BRAKE			(1)
#define LED_PIN_OK				(0)
#define LED_PIN_START			(7)



uint8_t led_pins[LED_NUMBER];
	
uint8_t led_port[LED_NUMBER];

uint8_t led_dd[LED_NUMBER];




void led_init(void);
void led_set(uint8_t led_id);
void led_clear(uint8_t led_id);
void led_toggle(uint8_t led_id);
void led_state_set(uint16_t led_new_state);
uint16_t led_state_return(void);
uint8_t led_is_set(uint8_t led_id);





#endif /* LED_H_ */