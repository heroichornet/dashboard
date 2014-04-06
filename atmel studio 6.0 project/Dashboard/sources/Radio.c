//******************************************************************************
//! @file Radio.c
//!
//! This library drives the Radio transmitter device using an N-MOSFET
//!
//! @brief This library drives the Radio transmitter device
//!
//!
//! @version 1.0
//!
//! @todo
//! @bug
//******************************************************************************


#include <stdint.h>
#include <avr/io.h>
#include "../includes/Radio.h"

void radio_init(void){
	RADIO_DDR|=1<<RADIO_PIN;
	RADIO_PORT&=~(1<<RADIO_PIN);
}

void radio_on(void){
	RADIO_PORT|=(1<<RADIO_PIN);
}

void radio_off(void){
	RADIO_PORT&=~(1<<RADIO_PIN);
}


