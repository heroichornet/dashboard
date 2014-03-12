/*
 * Dashboard.c
 *
 * Created: 04.03.2014 23:56:45
 *  Author: michael
 */ 

#include "includes/MyCommon.h"

int main(void){
	main_init();
	while(1){
		wdt_reset();
		EventHandleEvent();
	}
}
