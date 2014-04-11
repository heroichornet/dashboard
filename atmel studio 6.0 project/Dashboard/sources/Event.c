/*
 * Event.c
 *
 *  Created on: 20.10.2013
 *      Author: Michael
 */


#include <util/delay_basic.h>
#include "../includes/Event.h"
#include "../includes/GlobalIncludes.h"
#include <stdlib.h>
#include "../includes/Led.h"
#include "../includes/Button.h"
#include "../includes/Display.h"
#include "../includes/Buzzer.h"





EVENT_Handle event_queue[EVENT_QUEUE_SIZE];
U8 event_queue_head, event_queue_tail;

void EventInit(void){
	event_queue_head=0;
	event_queue_tail=0;
}

void EventAddEvent(EVENT_Handle event){
	if((event_queue_head+1)%EVENT_QUEUE_SIZE!=event_queue_tail){
		event_queue[event_queue_head]=event;
		event_queue_head=(event_queue_head+1)%EVENT_QUEUE_SIZE;
	}else{
		AddError(ERROR_EVENTQUEUE_FULL);
	}
}

EVENT_Handle EventGetNextEvent(void){
	EVENT_Handle e=EVENT_NOF_EVENTS;
	if(event_queue_head!=event_queue_tail){
		e=event_queue[event_queue_tail];
	}
	return e;
}


void Dashboard(void){
	
	switch(event_queue[event_queue_tail]){
		case EVENT_INIT:
			/* make structs for can  */
			/* Tx Structs */
			/* Tx Frame 1 */
			CANGetStruct(&dashboard_10_tx,dashboard_10_data.dataBuf,CAN_TX_10_ID,CAN_TX_10_LEN);
			/* Rx Structs*/
			/* Rx Frame*/
			CANGetStruct(&dashboard_rx,dashboard_rx_general_data.dataBuf,CAN_RX_ID,CAN_RX_ID);
			
			sei(); /* enable interrupts*/
			/* start Rx */
			/* Frame 1 */
			CANStartRx(&dashboard_rx);
			
			return;
		break;
		case EVENT_10HZ:
			

	
						
	
			


			
		return;
		break;
		case EVENT_50HZ:
			/* Multiplex */
			#if HAS_BUTTONS
				button_multiplex_cycle();				
			#endif	

			
			dashboard_10_data.dataStruct.REQUEST_ID=selected_menu;
			
			
			dashboard_10_data.dataStruct.KEYS_1=button_key1;

			dashboard_10_data.dataStruct.KEYS_2=button_key2;

			
			// Send tx Frame
			CANAddSendData(&dashboard_10_tx);
			
			
		return;
		break;
		case EVENT_4HZ:
	
		if(buzz_cycles!=0){
			if(buzzer_count<=2){
				buzzer_off();
				buzzer_count--;
			}else{
				buzzer_count--;
			}
			if(buzzer_count==0){
				buzzer_count=4;
				buzzer_on();
				buzz_cycles--;
			}
		}else{
			buzzer_off();
		}								
				
		return;
		break;
		case EVENT_CANERROR:
			/* Catch Can Errors*/
			CANAbortCMD();
		return;
		break;
		case EVENT_CANTX:
			CANSendNext();
		break;
		case EVENT_CANRX:
			// ToDo use RX to build display
			CANGetData(&dashboard_rx);
			// check for communication error
			/*if(selected_menu!=dashboard_rx_general_data.dataStruct.REQUEST_ID){
				display_update(DISPLAY_MENU_ERROR,ERROR_BAD_REQUEST_ID,0,0,0,0);
			}*/
			uint8_t id=dashboard_rx_general_data.dataStruct.REQUEST_ID;
			
			if(id=0xFF){
				buzzer_buzz_ready_to_drive();
				display_update(DISPLAY_MENU_TSAL,0,0,0,0,0);
				break;
			}
			
			if(dashboard_rx_general_data.dataStruct.LEDS&1){
				led_set(LED_ID_AMS);
			}else{
				led_clear(LED_ID_AMS);
			}
			if((dashboard_rx_general_data.dataStruct.LEDS>>1)&1){
				led_set(LED_ID_LV_LOW);
			}else{
				led_set(LED_ID_LV_LOW);
			}
			if((dashboard_rx_general_data.dataStruct.LEDS>>2)&1){
				led_set(LED_ID_IMD);
			}else{
				led_clear(LED_ID_IMD);
			}	
			if((dashboard_rx_general_data.dataStruct.LEDS>>3)&1){
				led_set(LED_ID_OK);
			}else{
				led_clear(LED_ID_OK);			
			}
			if((dashboard_rx_general_data.dataStruct.LEDS>>4)&1){
				led_set(LED_ID_BRAKE);
			}else{
				led_clear(LED_ID_BRAKE);
			}
			if((dashboard_rx_general_data.dataStruct.LEDS>>5)&1){
				buzzer_buzz_ready_to_drive();
			}
			if((dashboard_rx_general_data.dataStruct.LEDS>>6)&1){
				led_set(LED_ID_START);
			}else{
				led_clear(LED_ID_START);							
			}
				
			display_update(dashboard_rx_general_data.dataStruct.REQUEST_ID,dashboard_rx_general_data.dataStruct.VALUE1,dashboard_rx_general_data.dataStruct.VALUE2,dashboard_rx_general_data.dataStruct.VALUE3,dashboard_rx_general_data.dataStruct.VALUE4,dashboard_rx_general_data.dataStruct.VALUE5);
		

		return;
		break;
		default:
		break;
	}
}


void EventHandleEvent(void){
	if(event_queue_head!=event_queue_tail){
		Dashboard();		
		event_queue_tail=(event_queue_tail+1)%EVENT_QUEUE_SIZE;
	}
}

