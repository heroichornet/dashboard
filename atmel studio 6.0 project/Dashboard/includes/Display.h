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

typedef char display_string[20];

#define DISPLAY_LINE_AMZ_GRIMSEL ' ',' ',' ',' ',' ',' ','A','M','Z',' ','g','r','i','m','s','e','l',' ',' ',' '
#define DISPLAY_LINE_ERROR ' ',' ',' ',' ',' ',' ','E','R','R','R','O','R',' ',' ',' ',' ',' ',' ',' ',' '
#define DISPLAY_LINE_SOC ' ',' ','S','T','A','T','E',' ','O','F',' ','C','H','A','R','G','E',' ',' ',' ',' '
#define DISPLAY_LINE_PERCENT(X,Y) ' ',' ',' ',' ',' ',' ',' ','X','Y','%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '
#define DISPLAY_LINE_CELL_VOLTAGE ' ',' ','M','I','N',' ','C','E','L','L','V','O','L','T','A','G','E',' ','MAX',' '
#define DISPLAY_LINE_MIN_AV_MAX_VOLT(A,B,C,D,E,F) ' ',' ','A','B','V',' ','C','D','V',' ',' ',' ',' ',' ',' ',' ','E','F','X',' '
#define DISPLAY_LINE_CELL_TEMP ' ',' ','M','I','N',' ','C','E','L','L','t','E','M','P',' ',' ','M','A','X',' '
#define DISPLAY_LINE_MIN_AV_MAX_TEMP(A,B,X,D,E,F) ' ',' ','A','B','C',' ',' ','X','D','C',' ',' ',' ',' ',' ',' ','E','F','C',' '
#define DISPLAY_LINE_MIN_MAX_TEMP(A,B,X,E,F,G) ' ','A','B','X','C',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','E','F','G','C',' '
#define DISPLAY_LINE_MOTOR_POWER_FRONT ' ',' ','M','O','T','O','R',' ','P','O','W','E','R',' ','F','R','O','N','T',' ',' '
#define DISPLAY_LINE_MOTOR_POWER_REAR ' ',' ','M','O','T','O','R',' ','P','O','W','E','R',' ','R','E','A','R',' ',' ',' '
#define DISPLAY_LINE_TRACTION_CONTROL(A,B,C,D,E,F,G,H,I,J) ' ',' ',' ',' ','A','B','C','D','E','F','G','H','I','J',' ',' ',' ',' ',' ',' '
#define DISPLAY_LINE_TORQUE_VECTORING ' ',' ','T','O','R','Q','U','E',' ',' ','V','E','C','T','O','R','I','N','G',' ',' '
#define DISPLAY_LINE_ACCELERATION_MODE ' ',' ','A','C','C','E','L','E','R','A','T','I','O','N',' ','M','O','D','E',' ',' '

void display_update(void);

void display_show(display_string s);

void display_clear(void);

void display_init(void);

void display_deinit(void);

void display_brigthness(uint8_t b);

void display_update(void);

void display_set_display_string(display_string s);

#endif /* DISPLAY_H_ */
