/*
 * Button.c
 *
 * Created: 06.03.2014 09:56:32
 *  Author: michael
 */ 

#include <stdint.h>
#include "Button.h"


void button_init( void )
{
	button_pressed=0x00;
	/* ToDo: All pins on tri-state High impedance */
}
