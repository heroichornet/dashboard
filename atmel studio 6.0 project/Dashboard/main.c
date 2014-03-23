/*
 * Dashboard.c
 *
 * Created: 04.03.2014 23:56:45
 *  Author: michael
 */ 

#include <stdlib.h>
#include "includes/MyCommon.h"
#include "includes/GlobalIncludes.h"

int main(void){
	
	main_init();
	
	while(1){
		
		led_state_set(0xFFFF);
		led_state_set(0x0000);
		
	wdt_reset();
		EventHandleEvent();
	};

	main_deinit();
	
	return 0;
}

