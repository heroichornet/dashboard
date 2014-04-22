/*
 * Startup.c
 *
 * Created: 22.04.2014 08:26:44
 *  Author: michael
 */ 


#include "../includes/Startup.h"
#include "../includes/GlobalIncludes.h"
#include "../includes/MyCommon.h"
#include "../includes/Display.h"

uint8_t start_up_count=0;

void startup_sequence(void){
			start_up_count++;
			
			if((start_up_count%6)==0){
				display_starting((start_up_count/6)*10);
				led_percent_bar((start_up_count/6)*10);
			}
			
			if(start_up_count>=60){
				dashboard_state=DASHBOARD_STATE_RUNNING;
				selected_menu=DISPLAY_MENU_HOME;
				display_update(selected_menu,0,0,0,0,0,0);
				//clear all leds
				led_clear_all();
			}
}			