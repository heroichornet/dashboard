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


#ifndef DISPLAY_H_
#define DISPLAY_H_

/* Pin info */

/* SPI Start on PORTB0 */
/* SPI Clock on PORTB1 */
/* SPI MOSI on PORTB2 */
/* SPI MISO on PORTB3 */

/* This is the front end for controlling the display */

#define BRIGHTNESS_100 0;
#define BRIGHTNESS_75 1;
#define BRIGTHNESS_50 2;
#define BRIGTHNESS_25 3;

typedef char display_string_t[40];
typedef char display_line_t[20];

uint8_t selected_menu;
uint8_t selected_menu_pre_error;
uint8_t display_current_error;
display_string_t display_string;	
	


#define DISPLAY_MENU_NUMBER				(16)


#define DISPLAY_MENU_HOME				(0)
#define DISPLAY_MENU_SOC				(1)
#define DISPLAY_MENU_MIN_AV_MAX_VOLT	(2)
#define DISPLAY_MENU_MIN_AV_MAX_TEMP	(3)
#define DISPLAY_MENU_LV_VOLTAGE			(4)
#define DISPLAY_MENU_MOTOR_TEMP_REAR	(5)
#define DISPLAY_MENU_MOTOR_TEMP_FRONT	(6)
#define DISPLAY_MENU_MOTOR_POWER_FRONT	(7)
#define DISPLAY_MENU_MOTOR_POWER_REAR	(8)
#define DISPLAY_MENU_TRACTION_CONTROL	(9)
#define DISPLAY_MENU_TORQUE_VECTORING	(10)
#define DISPLAY_MENU_ACCLERATION_MODE	(11)
#define DISPLAY_MENU_ERROR				(12)
#define DISPLAY_MENU_SELECT_PLAYER		(13)
#define DISPLAY_MENU_BRAKE_BALANCE		(14)
#define	DISPLAY_MENU_INVERTER_TEMP		(15)


#define DISPLAY_MENU_BUTTON_TEST		(51)
#define DISPLAY_MENU_TSAL				(52)


void display_update(uint8_t request_id, uint8_t value1,uint8_t value2,uint8_t value3, uint8_t value4, uint8_t value5,uint8_t error);

void display_show(display_string_t s);

void display_clear(void);

void display_init(void);

void display_deinit(void);

void display_brigthness(uint8_t b);

void display_up(void);

void display_down(void);

void display_plus(void);

void display_minus(void);

void display_starting(uint8_t);



#endif /* DISPLAY_H_ */
