/*
 * display.h
 *
 *  Created on: Jan 22, 2014
 *      Author: michael
 */



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

typedef char display_string_t[20];
typedef char display_line_t[10];

uint8_t selected_menu;

display_string_t display_string;



#define DISPLAY_MENU_HOME (0)
#define DISPLAY_MENU_ERROR (1)
#define DISPLAY_MENU_SOC (2)
#define DISPLAY_MENU_CELL_VOLTAGE (3)
#define DISPLAY_MENU_MIN_AV_MAX_VOLT (4)
#define DISPLAY_MENU_MIN_AV_MAX_TEMP (5)
#define DISPLAY_MENU_MOTOR_POWER_FRONT (6)
#define DISPLAY_MENU_MOTOR_POWER_REAR (7)
#define DISPLAY_MENU_TRACTION_CONTROL (8)
#define DISPLAY_MENU_TORQUE_VECTORING (9)
#define DISPLAY_MENU_ACCLERATION_MODE (10)


void display_update(void);

void display_show(display_string_t s);

void display_clear(void);

void display_init(void);

void display_deinit(void);

void display_brigthness(uint8_t b);

void display_update(void);

void display_up(void);

void display_down(void);

void display_plus(void);

void display_minus(void);





#endif /* DISPLAY_H_ */
