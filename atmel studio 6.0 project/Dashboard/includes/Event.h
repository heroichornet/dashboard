/**
 * \file
 * \brief 
 * \author 
 * \date
 *
 */

#ifndef EVENT_H_
#define EVENT_H_

#define EVENT_QUEUE_SIZE 16

typedef enum {
	EVENT_INIT,
	EVENT_200HZ,
	EVENT_100HZ,
	EVENT_50HZ,
	EVENT_10HZ,
	EVENT_5HZ,
	EVENT_4HZ,
	EVENT_CANERROR,
	EVENT_CANTX,
	EVENT_CANRX,
	EVENT_NOF_EVENTS,
	EVENT_5KHZ
} EVENT_Handle;

void EventInit(void);

void EventAddEvent(EVENT_Handle event);

EVENT_Handle EventGetNextEvent(void);

void EventHandleEvent(void);

#endif /* EVENT_H_ */
