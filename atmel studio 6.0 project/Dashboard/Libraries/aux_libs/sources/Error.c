/*
 * Error.c
 *
 * Created: 06.03.2014 11:12:16
 *  Author: User
 */ 

#include "../includes/Error.h"
#include "../includes/compiler.h"

static U8* errorCode;

void InitError(U8* errorCodeTx){
	errorCode=errorCodeTx;
	CheckWDT();
}

void AddError(ERROR_Code er){
	(*errorCode)|=er;
}

void ClearErrors(void){
	(*errorCode)=0;
}