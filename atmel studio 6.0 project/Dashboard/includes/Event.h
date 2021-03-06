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
//! @todo 1. Adjust RX and TX Frames to match CAN Database
//! @bug
//******************************************************************************


#ifndef EVENT_H_
#define EVENT_H_

#define EVENT_QUEUE_SIZE 16

typedef enum {
	EVENT_INIT,
	EVENT_50HZ,
	EVENT_25HZ,
	EVENT_200HZ,
	EVENT_10HZ,
	EVENT_5HZ,
	EVENT_4HZ,
	EVENT_CANERROR,
	EVENT_CANTIMEOUT,
	EVENT_CANTX,
	EVENT_CANRX,
	EVENT_NOF_EVENTS,
} EVENT_Handle;

void EventInit(void);

void EventAddEvent(EVENT_Handle event);

EVENT_Handle EventGetNextEvent(void);

void EventHandleEvent(void);

#endif /* EVENT_H_ */
