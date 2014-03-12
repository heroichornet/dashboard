/*
 * Dashboard.c
 *
 * Created: 04.03.2014 23:56:45
 *  Author: michael
 */ 

#include "Libraries/aux_libs/"

int main(void){
	main_nit();
	while(1){
		wdt_reset();
		EventHandleEvent();
	}
}
