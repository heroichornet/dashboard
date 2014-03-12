/*
 * CAN_Interface.h
 *
 * Created: 27.02.2012 10:53:28
 *  Author: Phil
 */ 


#ifndef CAN_INTERFACE_H_
#define CAN_INTERFACE_H_

#include "compiler.h"
#include "..\includes\adc_drv.h"
#include "..\includes\CAN.h"

#define CAN_QUEUE_SIZE 5

typedef enum {
	CAN_Ready,
	CAN_Send
} CAN_Queue_Status;

void CANInit(void);
void CANGetStruct(st_cmd_t* st,U8* datapt, U16 ID, U8 lenght);
void CANStartRx(st_cmd_t* Rx);
void CANGetData(st_cmd_t* Rx);
void CANAddSendData(st_cmd_t* Tx);
st_cmd_t* CANGetCurrentTx(void);
void CANSendNext(void);
void CANAbortCMD(void);
//void CANSendDataWait(st_cmd_t* Tx);
void CANRestartReceive(st_cmd_t* Rx);

#endif
/* CAN_INTERFACE_H_ */