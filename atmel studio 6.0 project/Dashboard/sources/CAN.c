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
	if(interrupts&(1<<AERR)){
		EventAddEvent(EVENT_CANERROR);
		CANSTMOB&=~(1<<AERR);
	}
	if(interrupts&(1<<TXOK)){
		EventAddEvent(EVENT_CANTX);
		CANSTMOB&=~(1<<TXOK);
	}
	if(interrupts&(1<<RXOK)){
		EventAddEvent(EVENT_CANRX);
		//can_get_status(RxT);
		//CANSTMOB&=~(1<<RXOK);
		CANGIE&=~(1<<ENIT);
	}
	return;
}

void CANInit(void){
	can_init(CAN_BAUDRATE);
	CANSTMOB=0;
	CANGIE|=((1<<ENRX)|(1<<ENTX)|(1<<ENERR)|(1<<ENIT));
	CANIE1=0x7F;
	CANIE2=0xFF;
	can_queue_head=0;
	can_queue_tail=0;
	can_Status=CAN_Ready;
	can_rx=0;
}

void CANGetStruct(st_cmd_t* st,U8* datapt, U16 ID, U8 length){
	st->pt_data=datapt;
	st->ctrl.ide=0;
	st->ctrl.rtr=0;
	st->id.std=ID;
	st->dlc=length;
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
}

void CANSendData(void){
	if(can_queue_head!=can_queue_tail){
		if(can_rx!=0){
			can_rx->cmd=CMD_ABORT;
			can_cmd(can_rx);
		}
		can_queue[can_queue_tail]->cmd=CMD_TX_DATA;
		if(can_cmd(can_queue[can_queue_tail])!=CAN_CMD_ACCEPTED){
			AddError(ERROR_CAN_ACCEPTED);
		}else{
			can_Status=CAN_Send;
		}		
	}else if(can_rx!=0){
		can_rx->cmd=CMD_RX_DATA;
		can_cmd(can_rx);
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
	can_queue[can_queue_tail]->cmd = CMD_ABORT;
	can_cmd(can_queue[can_queue_tail]);
	can_Status=CAN_Ready;
	can_queue_tail=(can_queue_tail+1)%CAN_QUEUE_SIZE;
	CANSendData();
}

void CANAbortCMD(void){
	if(can_Status==CAN_Send){
		can_queue[can_queue_tail]->cmd = CMD_ABORT;
		can_cmd(can_queue[can_queue_tail]);
		AddError(ERROR_CAN_SEND);
		can_Status=CAN_Ready;
		can_queue_tail=(can_queue_tail+1)%CAN_QUEUE_SIZE;
	}
}

/*void CANSendDataWait(st_cmd_t* Tx){
	U16 whilecounter = 0;
	U8 canstate = 0;
	Tx->cmd=CMD_TX_DATA;
	if(can_cmd(Tx)!=CAN_CMD_ACCEPTED){
		PORTA=PORTA|0x08;
	}
	canstate = can_get_status(Tx);
	while(canstate == CAN_STATUS_NOT_COMPLETED)
	{
		whilecounter++;
		if(whilecounter > 65000)
		{
			Tx->cmd = CMD_ABORT;
			can_cmd(Tx);
		}
		canstate = can_get_status(Tx);
	};
	if(canstate == CAN_STATUS_ERROR)
	{
	}
}*/

void CANRestartReceive(st_cmd_t* Rx){// Braucht es fieleicht nicht
	Rx->cmd = CMD_ABORT;
	can_cmd(Rx);
	while(can_get_status(Rx) == CAN_STATUS_NOT_COMPLETED);
	Rx->cmd = CMD_RX_DATA;
	can_cmd(Rx);
}

