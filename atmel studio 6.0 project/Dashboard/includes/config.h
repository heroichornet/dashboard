/*
 * config.h
 *
 * Created: 27.02.2012 10:14:08
 *  Author: Phil
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include "..\includes\GlobalIncludes.h"

/**
	@brief		Frequenz vom CPU in Hz
*/
#define F_CPU	12000000			// 12 MHz
#define FOSC	12000				//Frequenz des Oszilators in kHz 
#ifndef CAN_BAUDRATE
#define CAN_BAUDRATE (CAN_500)
#endif
#endif /* CONFIG_H_ */