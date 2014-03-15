/*
 * Dashboard.c
 *
 * Created: 04.03.2014 23:56:45
 *  Author: michael
 */ 

#include <stdlib.h>
//#include "includes/MyCommon.h"

int main(void){
	

	
	buzzer_init();
	
	while(1){
		buzzer_buzz();
	}	
	/*
	while(1){
		wdt_reset();
		EventHandleEvent();
	}
	*/
	
	return 0;
}
