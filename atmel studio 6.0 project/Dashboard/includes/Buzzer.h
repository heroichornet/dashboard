/*
 * Buzzer.h
 *
 * Created: 06.03.2014 09:56:19
 *  Author: michael
 */ 



#ifndef BUZZER_H_
#define BUZZER_H_


/* Buzzer ist on PINA0 */

#define BUZZER_PIN (0x00)


void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
void buzzer_buzz(uint8_t time_ms);
void buzzer_puls(uint8_t freq_ms, uint8_t time_ms);


#endif /* BUZZER_H_ */