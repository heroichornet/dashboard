/*
 * WDT.h
 *
 * Created: 07.03.2014 17:13:55
 *  Author: User
 */ 


#ifndef WDT_H_
#define WDT_H_

#include <avr/wdt.h>
#include "GlobalIncludes.h"

void InitWDT(void);
Bool CheckWDT(void);


#endif /* WDT_H_ */