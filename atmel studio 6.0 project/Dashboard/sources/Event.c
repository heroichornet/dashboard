/*
 * Event.c
 *
 *  Created on: 20.10.2013
 *      Author: Michael
 */


#include "../includes/Event.h"
#include "../includes/GlobalIncludes.h"
#include <stdlib.h>
#include "../includes/Led.h"
#include "../includes/Button.h"
#include "../includes/Display.h"



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
			

			if(((PORTD>>3)&1)==1){
					PORTD&=~(1<<3);
			}else{
					PORTD|=(1<<3);
			}
			
			//CAN Stuff
			//Fill TX Frame
			dashboard_10_data.dataStruct.ERRORCODE=0xFF;
			dashboard_10_data.dataStruct.REQUEST_ID=selected_menu;
			dashboard_10_data.dataStruct.KEYS_1=0xFF;
			dashboard_10_data.dataStruct.KEYS_2=0xFF;			
			// Send tx Frame
			CANAddSendData(&dashboard_10_tx);
						
	
			//Led Update 
			led_state_set(led_state);
							
		
			//update menu
			
			uint8_t i=0;
			


			
		return;
		break;
		case EVENT_50HZ:
			/* Multiplex */
			#if HAS_BUTTONS
				button_multiplex_cycle();	
				
				for(i;i<12;i++){
					if(button_press[BUTTON_ID_UP]==1){
						button_press[i]=0;
						
						selected_menu++;
						selected_menu%11;
						display_update(selected_menu,0,i,0,0,0);
					}
				}
					
			#endif	
			
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

