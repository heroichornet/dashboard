/*
 * Event.c
 *
 *  Created on: 20.10.2011
 *      Author: Morris
 */

#include "../includes/Event.h"
#include "../includes/GlobalIncludes.h"
#include "../includes/adc.h"
//#include "RecupBalance.h"
//#include "adc.h"
#include <stdlib.h>

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

#if MCM==MCM_FRONT
static void MCMFront(void){
	switch(event_queue[event_queue_tail]){
		case EVENT_INIT:
		CANGetStruct(&mcm_front_200_tx,mcm_front_200_data.dataBuf,CAN_TX_200_ID,CAN_TX_200_LEN);
		CANGetStruct(&mcm_front_10_tx,mcm_front_10_data.dataBuf,CAN_TX_10_ID,CAN_TX_10_LEN);
		InitError(&mcm_front_200_data.dataStruct.errorCode);
		mcm_front_current_ADC=0;
		ADStart(mcm_front_current_ADC);
		sei();
		break;
		case EVENT_200HZ:
		CANAddSendData(&mcm_front_200_tx);
		break;
		case EVENT_10HZ:
		if(PINB&0x01){
			mcm_front_10_data.dataStruct.BOTS=CAN_TRUE;
		}else{
			mcm_front_10_data.dataStruct.BOTS=CAN_FALSE;
		}
		if(PIND&0x01){
			mcm_front_10_data.dataStruct.preBOTS=CAN_TRUE;
		}else{
			mcm_front_10_data.dataStruct.preBOTS=CAN_FALSE;
		}
		CANAddSendData(&mcm_front_10_tx);
		if(PORTA&0x08){
			PORTA=PORTA&(~0x08);
		}else{
			PORTA=PORTA|0x08;
		}
		break;
		case EVENT_ADCDONE:
		switch(mcm_front_current_ADC){
			case 0:
			mcm_front_200_data.dataStruct.steeringangle=ADGetVal();
			mcm_front_current_ADC++;
			break;
			case 1:
			mcm_front_200_data.dataStruct.throttlep=ADGetVal()>>2;
			mcm_front_current_ADC++;
			break;
			case 2:
			mcm_front_200_data.dataStruct.throttlem=ADGetVal()>>2;
			mcm_front_current_ADC++;
			break;
			case 3:
			mcm_front_10_data.dataStruct.brakePressureF=ADGetVal()>>2;
			mcm_front_current_ADC++;
			break;
			case 4:
			mcm_front_200_data.dataStruct.brakeforce=ADGetVal()>>2;
			mcm_front_current_ADC++;
			break;
			case 5:
			mcm_front_10_data.dataStruct.brakePressureR=ADGetVal()>>2;
			mcm_front_current_ADC=0;
			break;
		}
		ADStart(mcm_front_current_ADC);
		break;
		case EVENT_CANERROR:
		CANAbortCMD();
		break;
		case EVENT_CANTX:
		if(CANGetCurrentTx()==&mcm_front_200_tx){//ErrorCode gesendet
			ClearErrors();
		}
		CANSendNext();
		break;
		default:
		break;
	}
}
#endif

#if MCM==MCM_LVBOX
static void MCMLVBox(void){
	switch(event_queue[event_queue_tail]){
		case EVENT_INIT:
		CANGetStruct(&mcm_lvbox_10_tx,mcm_lvbox_10_data.dataBuf,CAN_TX_10_ID,CAN_TX_10_LEN);
		CANGetStruct(&mcm_lvbox_rx,mcm_lvbox_rx_data.dataBuf,CAN_RX_ID,CAN_RX_LEN);
		InitError(&mcm_lvbox_10_data.dataStruct.errorCode);
		mcm_lvbox_current_ADC=0;
		ADStart(mcm_lvbox_current_ADC);
		sei();
		CANStartRx(&mcm_lvbox_rx);
		break;
		case EVENT_10HZ:
		if(PIND&0x01){
			mcm_lvbox_10_data.dataStruct.IMDF=CAN_TRUE;
		}else{
			mcm_lvbox_10_data.dataStruct.IMDF=CAN_FALSE;
		}
		CANAddSendData(&mcm_lvbox_10_tx);
		/*if(PORTA&0x08){
			PORTA=PORTA&(~0x08);
		}else{
			PORTA=PORTA|0x08;
		}*/
		break;
		case EVENT_ADCDONE:
		switch(mcm_lvbox_current_ADC){
			case 0:
			mcm_lvbox_10_data.dataStruct.lvTemp=ADGetVal()>>2;
			mcm_lvbox_current_ADC++;
			break;
			case 1:
			mcm_lvbox_10_data.dataStruct.coolTemp2=ADGetVal()>>2;
			mcm_lvbox_current_ADC++;
			break;
			case 2:
			mcm_lvbox_10_data.dataStruct.lvCell3=ADGetVal()>>2;
			mcm_lvbox_current_ADC++;
			break;
			case 3:
			mcm_lvbox_10_data.dataStruct.lvCell2=ADGetVal()>>2;
			mcm_lvbox_current_ADC++;
			break;
			case 4:
			mcm_lvbox_10_data.dataStruct.lvCell1=ADGetVal()>>2;
			mcm_lvbox_current_ADC++;
			break;
			case 5:
			mcm_lvbox_10_data.dataStruct.coolTemp1=ADGetVal()>>2;
			mcm_lvbox_current_ADC=0;
			break;
		}
		ADStart(mcm_lvbox_current_ADC);
		break;
		case EVENT_CANERROR:
		CANAbortCMD();
		break;
		case EVENT_CANTX:
		if(CANGetCurrentTx()==&mcm_lvbox_10_tx){//ErrorCode gesendet
			ClearErrors();
		}
		CANSendNext();
		break;
		case EVENT_CANRX:
		CANGetData(&mcm_lvbox_rx);
		if(mcm_lvbox_rx_data.dataStruct.pumpe1==CAN_FALSE){
			PORTB&=(~0x01);
		}else{
			PORTB|=0x01;
		}
		if(mcm_lvbox_rx_data.dataStruct.pumpe2==CAN_FALSE){
			PORTB&=(~0x02);
		}else{
			PORTB|=0x02;
		}
		break;
		default:
		break;
	}
}
#endif

#if MCM==MCM_REAR
static void MCMRear(void){
	//CANStartRx(&mcm_rear_rx);
	switch(event_queue[event_queue_tail]){
		case EVENT_INIT:
		CANGetStruct(&mcm_rear_10_tx,mcm_rear_10_data.dataBuf,CAN_TX_10_ID,CAN_TX_10_LEN);
		CANGetStruct(&mcm_rear_rx,mcm_rear_rx_data.dataBuf,CAN_RX_ID,CAN_RX_LEN);
		InitError(&mcm_rear_10_data.dataStruct.errorCode);
		sei();
		CANStartRx(&mcm_rear_rx);
		break;
		case EVENT_10HZ:
		if(PIND&0x01){
			mcm_rear_10_data.dataStruct.preMS=CAN_TRUE;
		}else{
			mcm_rear_10_data.dataStruct.preMS=CAN_FALSE;
		}
		if(PIND&0x02){
			mcm_rear_10_data.dataStruct.preENRE=CAN_TRUE;
		}else{
			mcm_rear_10_data.dataStruct.preENRE=CAN_FALSE;
		}
		if(PORTA&0x08){
			PORTA=PORTA&(~0x08);
		}else{
			PORTA=PORTA|0x08;
		}
		CANAddSendData(&mcm_rear_10_tx);
		break;
		case EVENT_CANERROR:
		CANAbortCMD();
		break;
		case EVENT_CANTX:
		if(CANGetCurrentTx()==&mcm_rear_10_tx){//ErrorCode gesendet
			ClearErrors();
		}
		CANSendNext();
		break;
		case EVENT_CANRX:
		CANGetData(&mcm_rear_rx);
		if(mcm_rear_rx_data.dataStruct.ENRE==CAN_FALSE){
			PORTB&=(~0x01);
		}else{
			PORTB|=0x01;
		}
		if(mcm_rear_rx_data.dataStruct.brakeLight==CAN_FALSE){
			PORTB&=(~0x02);
			PORTA=PORTA&(~0x08);
		}else{
			PORTB|=0x02;
			PORTA=PORTA|0x08;
		}
		break;
		default:
		break;
	}
}
#endif

#if MCM==MCM_HVBOX
static void MCMHVBox(void){
	switch(event_queue[event_queue_tail]){
		case EVENT_INIT:
		CANGetStruct(&mcm_hvbox_10_tx,mcm_hvbox_10_data.dataBuf,CAN_TX_10_ID,CAN_TX_10_LEN);
		CANGetStruct(&mcm_hvbox_rx,mcm_hvbox_rx_data.dataBuf,CAN_RX_ID,CAN_RX_LEN);
		InitError(&mcm_hvbox_10_data.dataStruct.errorCode);
		sei();
		CANStartRx(&mcm_hvbox_rx);
		break;
		case EVENT_10HZ:
		if(PINB&0x02){
			mcm_hvbox_10_data.dataStruct.HVDI=CAN_TRUE;
		}else{
			mcm_hvbox_10_data.dataStruct.HVDI=CAN_FALSE;
		}
		if(PIND&0x02){
			mcm_hvbox_10_data.dataStruct.IMD=CAN_TRUE;
		}else{
			mcm_hvbox_10_data.dataStruct.IMD=CAN_FALSE;
		}
		if(PINE&0x02){
			mcm_hvbox_10_data.dataStruct.BPD=CAN_TRUE;
		}else{
			mcm_hvbox_10_data.dataStruct.BPD=CAN_FALSE;
		}
		if(PIND&0x20){
			mcm_hvbox_10_data.dataStruct.MS=CAN_TRUE;
		}else{
			mcm_hvbox_10_data.dataStruct.MS=CAN_FALSE;
		}
		if(PIND&0x40){
			//BMS
		}else{
			
		}
		CANAddSendData(&mcm_hvbox_10_tx);
		/*if(PORTA&0x08){
			PORTA=PORTA&(~0x08);
		}else{
			PORTA=PORTA|0x08;
		}*/
		break;
		case EVENT_CANERROR:
		CANAbortCMD();
		break;
		case EVENT_CANTX:
		if(CANGetCurrentTx()==&mcm_hvbox_10_tx){//ErrorCode gesendet
			ClearErrors();
		}
		CANSendNext();
		break;
		case EVENT_CANRX:
		CANGetData(&mcm_hvbox_rx);
		if(mcm_hvbox_rx_data.dataStruct.showBPD==CAN_FALSE){
			PORTB&=(~0x04);
		}else{
			PORTB|=0x04;
		}
		if(mcm_hvbox_rx_data.dataStruct.AIRp==CAN_FALSE){
			PORTB&=(~0x08);
		}else{
			PORTB|=0x08;
		}
		if(mcm_hvbox_rx_data.dataStruct.preCharge==CAN_FALSE){
			PORTD&=(~0x01);
		}else{
			PORTD|=0x01;
		}
		if(mcm_hvbox_rx_data.dataStruct.Fan1==CAN_FALSE){
			PORTE&=(~0x01);
		}else{
			PORTE|=0x01;
		}
		if(mcm_hvbox_rx_data.dataStruct.Fan2==CAN_FALSE){
			PORTE&=(~0x10);
		}else{
			PORTE|=0x10;
		}
		break;
		default:
		break;
	}
}
#endif

#if MCM==MCM_AD
static void MCMAD(void){
	U16 result;
	switch(event_queue[event_queue_tail]){
		case EVENT_INIT:
		CANGetStruct(&mcm_ad_10_tx,mcm_ad_10_data.dataBuf,CAN_TX_10_ID,CAN_TX_10_LEN);
		CANGetStruct(&mcm_ad_rx,mcm_ad_rx_data.dataBuf,CAN_RX_ID,CAN_RX_LEN);
		InitError(&mcm_ad_10_data.dataStruct.errorCode);
		mcm_ad_rx_data.dataStruct.BoundD1=255;
		mcm_ad_rx_data.dataStruct.BoundGap=64;
		mcm_ad_rx_data.dataStruct.BoundD2=128;
		mcm_ad_rx_data.dataStruct.BoundOff2=64;
		mcm_ad_rx_data.dataStruct.ReBoundD1=255;
		mcm_ad_rx_data.dataStruct.ReBoundGap=64;
		mcm_ad_rx_data.dataStruct.ReBoundD2=128;
		mcm_ad_rx_data.dataStruct.ReBoundOff2=64;
		sei();
		CANStartRx(&mcm_ad_rx);
		break;
		case EVENT_PWM:
		mcm_ad_current_ADC=0;
		ADStart(mcm_ad_current_ADC);
		break;
		case EVENT_10HZ:
		CANAddSendData(&mcm_ad_10_tx);
		/*if(PORTA&0x08){
			PORTA=PORTA&(~0x08);
		}else{
			PORTA=PORTA|0x08;
		}*/
		break;
		case EVENT_ADCDONE:
		switch(mcm_ad_current_ADC){
			case 0:
			mcm_ad_10_data.dataStruct.SpeedSign=PINB&0x01;
			mcm_ad_10_data.dataStruct.Speed=ADGetVal();
			
			result=mcm_ad_10_data.dataStruct.Speed;
			if(mcm_ad_10_data.dataStruct.SpeedSign){
				if((result>>2)<mcm_ad_rx_data.dataStruct.BoundGap){
					result=((U32)result*(U32)mcm_ad_rx_data.dataStruct.BoundD1)>>9;
				}else{
					result=((U32)result*(U32)mcm_ad_rx_data.dataStruct.BoundD2)>>9;
					result+=mcm_ad_rx_data.dataStruct.BoundOff2;
				}
				TIMER_SetPWMVal(ad_LUT_Bound[result]);
			}else{
				if((result>>2)<mcm_ad_rx_data.dataStruct.ReBoundGap){
					result=((U32)result*(U32)mcm_ad_rx_data.dataStruct.ReBoundD1)>>9;
				}else{
					result=((U32)result*(U32)mcm_ad_rx_data.dataStruct.ReBoundD2)>>9;
					result+=mcm_ad_rx_data.dataStruct.ReBoundOff2;
				}
				TIMER_SetPWMVal(ad_LUT_ReBound[256-result]);
			}
			
			mcm_ad_current_ADC++;
			ADStart(mcm_ad_current_ADC);
			break;
			case 1:
			mcm_ad_10_data.dataStruct.Position=ADGetVal();
			//PORTA=PORTA|0x08;
			//PORTA=PORTA&(~0x08);
			break;
		}
		break;
		case EVENT_CANERROR:
		CANAbortCMD();
		break;
		case EVENT_CANTX:
		if(CANGetCurrentTx()==&mcm_ad_10_tx){//ErrorCode gesendet
			ClearErrors();
		}
		CANSendNext();
		break;
		case EVENT_CANRX:
		CANGetData(&mcm_ad_rx);
		break;
		default:
		break;
	}
}
#endif

void EventHandleEvent(void){
	if(event_queue_head!=event_queue_tail){
		#if MCM==MCM_FRONT
			MCMFront();
		#endif
		#if MCM==MCM_LVBOX
			MCMLVBox();
		#endif
		#if MCM==MCM_REAR
			MCMRear();
		#endif
		#if MCM==MCM_HVBOX
			MCMHVBox();
		#endif
		#if MCM==MCM_AD
			MCMAD();
		#endif
		event_queue_tail=(event_queue_tail+1)%EVENT_QUEUE_SIZE;
	}
}