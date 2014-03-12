//***********************************************************************************
/**
	@file		
	@author		Klemenz Christof (2008/2009)
	@version	1.1
*/
//***********************************************************************************
#include "..\includes\GlobalIncludes.h"
#include "..\includes\adc.h"

ISR(ADC_vect){
	EventAddEvent(EVENT_ADCDONE);
	return;
}

void ADInit(U8 prescaler, Bool digitalInputDisable){
	ADCSRA = (1<<ADEN) | prescaler;
	ADMUX &= ~((1<<REFS0) | (1<<REFS1) | (1<<ADLAR));
	//ADMUX |= (1<<REFS0);
	if(digitalInputDisable==TRUE){
		DIDR0=0x3F; //Digital input disable
	}
	ADCSRA |= (1<<ADSC); //Start DataSheet:21.5.2
	while (ADCSRA & (1<<ADSC)); //Warten
	ADCSRA |= (1<<ADIE);
}

void ADStart(U8 channel){
	if(channel!=(ADMUX&0x07)){
		ADMUX |= channel;
		ADMUX &= ((~0x07)|channel);
	}
	ADCSRA |= (1<<ADSC); //Start
}

U16 ADGetVal(void){
	return ADC;
	// bei 5V: 1023*4*11/9 = 5001 => 5001mV
}

/*U16 AnalogInMean(U8 AnalogInPin, U8 AnzMessungen)
{
	U8 i;
	U16 Value = 0;

	//Falscher Inputkanal
	if(AnalogInPin < AnIn7 || AnalogInPin > AnIn0) return 0;
	
	if(AnzMessungen > 16) 		AnzMessungen = 16;
	else if (AnzMessungen <= 0) AnzMessungen = 1;

	for (i=0; i<AnzMessungen; i++)
	{
		Value += AnalogIn(AnalogInPin);
		_delay_us(400);
	}

	return (Value/AnzMessungen);

}*/
