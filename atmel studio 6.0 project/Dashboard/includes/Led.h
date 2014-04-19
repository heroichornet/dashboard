//******************************************************************************
//! @file Led.H
//!
//! Led Driver for 11 leds
//!
//! @brief This Library is used to drive 11 LEDs
//!
//!
//! @version 1.0
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef LED_H_
#define LED_H_

uint16_t led_state;


#define LED_NUMBER				(11)

/* Error LEDS */

#define LED_ID_AMS				(1)
#define LED_ID_LV_LOW			(10)
#define LED_ID_IMD				(2)
#define LED_ID_OK				(3)
#define LED_ID_BRAKE			(4)


/* Button LEDS */

#define LED_ID_TV				(6)
#define LED_ID_TC				(5)
#define LED_ID_RECUP			(7)
#define LED_ID_KOBI				(8)
#define LED_ID_AD				(9)
#define LED_ID_START			(0)




uint8_t led_pins[LED_NUMBER];
	
uint8_t led_port[LED_NUMBER];

uint8_t led_dd[LED_NUMBER];



//------------------------------------------------------------------------------
//  @fn led_init
//!
//! This function initalizes the leds
//!
//! @warning none
//!
//! @param  none
//!
//! @return  none
//!
//------------------------------------------------------------------------------
void led_init(void);
//------------------------------------------------------------------------------
//  @fn led_set
//!
//! This function sets a specific LED with a specific ID
//!
//! @warning none
//!
//! @param  led_id I
//!
//! @return  none
//!
//------------------------------------------------------------------------------
void led_set(uint8_t led_id);
void led_clear(uint8_t led_id);
void led_toggle(uint8_t led_id);
void led_state_set(uint16_t led_new_state);
uint16_t led_state_return(void);
uint8_t led_is_set(uint8_t led_id);





#endif /* LED_H_ */