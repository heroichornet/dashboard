//***********************************************************************************
/**
	@file		
	@author		Klemenz Christof (2008/2009)
	@version	1.1

	@brief		Funktionen für Analog-Digitalwandlung
*/
//***********************************************************************************
#ifndef ADC_H
#define ADC_H


#include "config.h"
#include <avr/io.h>
#include <util/delay.h>  
#include "compiler.h"

void ADInit(U8 prescaler, Bool digitalInputDisable);
void ADStart(U8 channel);
U16 ADGetVal(void);

//***********************************************************************************

/**
	@brief		Misst die analoge Spannung im Mittel am gewaehlten Port

	@param		AnalogInPin		waehlt, an welchem AD-Eingang man messen moechte
	@param		AnzMessungen	Anzahl Messungen die vorgenommen werden sollen und
								anschliessen gemittelt wird

	@return		Spannung in mV
*/
//U16 AnalogInMean(U8 AnalogInPin, U8 AnzMessungen);

#endif
