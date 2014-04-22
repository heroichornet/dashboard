/*
 * MyCommon.h
 *
 * Created: 06.03.2014 23:04:51
 *  Author: michael
 */ 

#ifndef MYCOMMON_H_
#define MYCOMMON_H_



#include <avr/io.h>
#include "GlobalIncludes.h"


#define DASHBOARD_STATE_STARTING (0)
#define DASHBOARD_STATE_RUNNING	 (1)

uint8_t dashboard_state;


void main_init(void);
void main_deinit(void);
void ports_init(void);



#endif /* MYCOMMON_H_ */