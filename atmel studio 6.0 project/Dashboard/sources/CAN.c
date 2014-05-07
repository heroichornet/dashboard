/*
 * CAN_Interface.c
 *
 * Created: 27.02.2012 10:37:36
 *  Author: Phil
 */ 

/* +--------------------------------+ */
/* | Includes						| */
/* +--------------------------------+ */
#include "../includes/compiler.h"
#include "..\includes\adc_drv.h"
#include "..\includes\CAN.h"
/* +--------------------------------+ */
/* | Globale Variablen				| */
/* +--------------------------------+ */
/*static st_cmd_t TX_Send;
static U8 SendData[8];

static st_cmd_t RX_Receive;
static U8 ReceiveData[8];*/
st_cmd_t* can_queue[CAN_QUEUE_SIZE];
U8 can_queue_head, can_queue_tail;
CAN_Queue_Status can_Status;
st_cmd_t* can_rx;

/* +--------------------------------+ */
/* | CODE							| */
/* +--------------------------------+ */

ISR(CANIT_vect){
	U8 interrupts=CANSTMOB;
	if(interrupts&(1<<TXOK)){
		EventAddEvent(EVENT_CANTX);
		CANSTMOB&=~(1<<TXOK);
	}else{
		if(interrupts&(1<<RXOK)){
			EventAddEvent(EVENT_CANRX);
			CANGIE&=~(1<<ENIT);
		}else{
			CANSTMOB=0x00;
			CANGIE&=~(1<<ENERR);
			EventAddEvent(EVENT_CANERROR);
		}
	}
	return;
}

void CANInit(void){
	can_init(CAN_BAUDRATE);
	CANSTMOB=0;
	CANGIE=((1<<ENRX)|(1<<ENTX)|(1<<ENIT));
	CANIE1=0x7F;
	CANIE2=0xFF;
	can_queue_head=0;
	can_queue_tail=0;
	can_Status=CAN_Ready;
	can_rx=0;
}

void CANGetStruct(st_cmd_t* st,U8* datapt, U16 ID, U8 lenght){
	st->pt_data=datapt;
	st->ctrl.ide=0;
	st->ctrl.rtr=0;
	st->id.std=ID;
	st->dlc=lenght;
	st->id_mask=0x07FF;
}

void CANStartRx(st_cmd_t* Rx){
	can_rx=Rx;
	can_rx->cmd=CMD_RX_DATA;
	can_cmd(can_rx);
}

void CANGetData(st_cmd_t* Rx){
	can_get_status(Rx);
	CANGIE|=(1<<ENIT);
	if(can_Status==CAN_Pending){
		can_Status=CAN_Send;
		CANSend();
	}
}

void CANSendData(void){
	if(can_queue_head!=can_queue_tail){
		if(can_rx!=0){
			CANGIE&=~(1<<ENRX);
			can_rx->cmd=CMD_ABORT;
			can_cmd(can_rx);
			while(can_get_status(can_rx)==CAN_STATUS_NOT_COMPLETED);
		}
		if(CANGIE&(1<<ENIT)){
			can_Status=CAN_Send;
			CANSend();
		}else{
			can_Status=CAN_Pending;
		}	
	}else if(can_rx!=0){
		can_rx->cmd=CMD_RX_DATA;
		can_cmd(can_rx);
		CANGIE|=(1<<ENRX);
	}
}

void CANSend(void){
	can_queue[can_queue_tail]->cmd=CMD_TX_DATA;
	if(can_cmd(can_queue[can_queue_tail])!=CAN_CMD_ACCEPTED){
		can_Status=CAN_Ready;
		AddError(ERROR_CAN_ACCEPTED);
	}else{
		CANGIE|=(1<<ENERR);
		Timer0_Start();
	}
}

void CANAddSendData(st_cmd_t* Tx){
	if((can_queue_head+1)%CAN_QUEUE_SIZE!=can_queue_tail){
		can_queue[can_queue_head]=Tx;
		can_queue_head=(can_queue_head+1)%CAN_QUEUE_SIZE;
	}else{
		AddError(ERROR_CANQUEUE_FULL);
	}
	if(can_Status==CAN_Ready){
		CANSendData();
	}
}

st_cmd_t* CANGetCurrentTx(void){
	return can_queue[can_queue_tail];
}

void CANSendNext(void){
	Timer0_Stop();
#ifdef WDT_DELAY
	wdt_reset();
#endif
	can_queue[can_queue_tail]->cmd = CMD_ABORT;
	can_cmd(can_queue[can_queue_tail]);
	can_Status=CAN_Ready;
	can_queue_tail=(can_queue_tail+1)%CAN_QUEUE_SIZE;
	CANSendData();
}

void CANAbortCMD(void){
	if((can_Status==CAN_Send)||(can_Status==CAN_Pending)){
		Timer0_Stop();
		can_queue[can_queue_tail]->cmd=CMD_ABORT;
		can_cmd(can_queue[can_queue_tail]);
		AddError(ERROR_CAN_SEND);
		can_Status=CAN_Ready;
		can_queue_tail=(can_queue_tail+1)%CAN_QUEUE_SIZE;
	}
}


