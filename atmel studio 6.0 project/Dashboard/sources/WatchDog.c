/*
 * WDT.c
 *
 * Created: 07.03.2014 17:14:11
 *  Author: User
 */ 

#include "../includes/WatchDog.h"

void InitWDT(void){
	//wdt_enable(WDTO_120MS);
}

Bool CheckWDT(void){
	if(MCUSR&(1<<WDRF)){
		MCUSR&=~(1<<WDRF);
		AddError(ERROR_WDT);
	}
}

