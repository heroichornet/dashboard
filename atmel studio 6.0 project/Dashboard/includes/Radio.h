//******************************************************************************
//! @file Radio.H
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


#ifndef RADIO_H_
#define RADIO_H_


#define RADIO_PIN (2)
#define RADIO_PORT (PORTD)
#define RADIO_DDR (DDRD)



void radio_init(void);
void radio_on(void);
void radio_off(void);



#endif /* RADIO_H_ */