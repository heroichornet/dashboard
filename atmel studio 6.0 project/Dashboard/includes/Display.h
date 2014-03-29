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


void display_show(display_string s);

void display_clear(void);

void display_init(void);

void display_deinit(void);

void display_brigthness(uint8_t b);

#endif /* DISPLAY_H_ */
