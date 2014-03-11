/*
 * CProgram1.c
 *
 * Created: 20.03.2012 09:48:09
 *  Author: Phil
 */ 

#include "..\includes\GlobalIncludes.h"
#include "..\includes\FCALC_Frequency.h"

	/*
	 * EICRB
	 * 00 Low Level
	 * 01 Any Logic Change
	 * 10 Falling Edge
	 * 11 Rising Edge
	 *
	 * EICRB = (0<<ISC71) | (1<<ISC70) | (0<<ISC61) | (1<<ISC60);
	**/

//void doLastabwurf_M_PE6(void){
	//FCALC_Precision_M_PE6 = 1; // used to shift in order to have same interface to remaining system.
	//EICRB = EICRB  | (1<<ISC61) | (1<<ISC60);
//}
//
//void goPrecise_M_PE6(void){
	//FCALC_Precision_M_PE6 = 0;
	//EICRB = EICRB & ~((1<<ISC61) | (1<<ISC60));
	//EICRB = EICRB  | (0<<ISC61) | (1<<ISC60);
//}
//
//void doLastabwurf_M_PE7(void){
	//FCALC_Precision_M_PE7 = 1; // used to shift in order to have same interface to remaining system.
	//EICRB = EICRB  | (1<<ISC71) | (1<<ISC70);
//}
//
//void goPrecise_M_PE7(void){
	//FCALC_Precision_M_PE7 = 0;
	//EICRB = EICRB & ~((1<<ISC71) | (1<<ISC70));
	//EICRB = EICRB  | (0<<ISC71) | (1<<ISC70);
//}

U8 FCALC_GFD_Period_Decode(void){
	U16 localFrequencyCopy = 0;
	EnterCritical();
	localFrequencyCopy = M_PE6_TimeInterval;
	ExitCritical();
	if(0 == localFrequencyCopy){
		return 0;
	}
	else{
		if(localFrequencyCopy > 0x4130){ // Frequency border 15 Hz
			return 10;
		}
		if(localFrequencyCopy > 0x2700){ // Frequency border 25 Hz
			return 20;
		}
		if(localFrequencyCopy > 0x1C20){ // Frequency border 35 Hz
			return 30;
		}
		if(localFrequencyCopy > 0x15A0){ // Frequency border 45 Hz
			return 40;
		}
		return 50;
	}
}

U8 FCALC_GFD_DutyCycle_Decode(U8 frequency){
	U16 local_DutyCycleCopy = 0;
	EnterCritical();
	local_DutyCycleCopy = M_PE6_Frequency_calc_DutyCycle;
	ExitCritical();
	
	switch (frequency)
	{
		case 50:
			return 100-local_DutyCycleCopy / 50;
			break;
		case 40:
			return 100-local_DutyCycleCopy / 62;
			break;
		case 30:
			return 100-local_DutyCycleCopy / 83;
			break;
		case 20:
			return 100-local_DutyCycleCopy / 125;
			break;
		case 10:
			return 100-local_DutyCycleCopy / 250;
			break;
		default:
			return 0;
	}
}
