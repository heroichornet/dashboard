/*
 * Error.h
 *
 * Created: 06.03.2014 11:04:04
 *  Author: User
 */ 


#ifndef ERROR_H_
#define ERROR_H_

#include "CAN.h"

typedef enum{
	ERROR_CAN_ACCEPTED=(1<<0),
	ERROR_CAN_SEND=(1<<1),
	ERROR_CANQUEUE_FULL=(1<<2),
	ERROR_CANTIMEOUT=(1<<3),
	ERROR_EVENTQUEUE_FULL=(1<<4),
	ERROR_WDT=(1<<5),
	ERROR_TEST=(1<<6)
} ERROR_Code;

void InitError(U8* errorCodeTx);
void AddError(ERROR_Code er);
void ClearErrors(void);

#endif /* ERROR_H_ */