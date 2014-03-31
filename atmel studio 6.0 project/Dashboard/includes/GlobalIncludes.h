/*
 * GlobalIncludes.h
 *
 * Created: 26.02.2012 23:54:24
 *  Author: Phil
 */ 


#ifndef GlobalIncludes_H_
#define GlobalIncludes_H_

/* +--------------------------------+ */
/* | Libraries						| */
/* +--------------------------------+ */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/iocanxx.h>
#include <util/atomic.h>
#include <util/twi.h>

/* +--------------------------------+ */
/* | Specifics						| */
/* +--------------------------------+ */

#include "compiler.h"
#include "config.h"
#include "Watchdog.h"
#include "Event.h"
#include "can_drv.h"
#include "can_lib.h"
#include "CAN.h"
#include "Error.h"
#include "Timer.h"

/* +--------------------------------+ */
/* | Definitionen					| */
/* +--------------------------------+ */



// Debugging definitions
#define DEBUG	(0)

// CAN Defines
#define CAN_BAUDRATE	(CAN_500)
#define CAN_ND	(0x00) // CAN_NO_DATA
#define CAN_TRUE 0x01
#define CAN_FALSE 0x00

// ADC Defines
#define ADC_VOLTAGE_REF	(1)
#define ADC_LEFT_ADJUST	(FALSE)
#define ADC_NUM_AVGS	(1)

// Timer Defines
#define TMR1_PRESCALER		((0<<CS32) | (1<<CS31) | (0<<CS30)) //1 Tick = PRSC/OSC_CLCK= 8 / 12MHz = 0.6667 us
#define OCR1A_PERIOD_CNT	(0x1D4C) // 5ms/200Hz		Software Ticker 0x4E20 for PRSC=8 (0x09C4 for PRSC=64)
#define OCR1B_PERIOD_CNT	(0x3A98) // 10ms/100Hz
#define OCR1C_PERIOD_CNT	(0x7530) // 20ms/50Hz
#define TMR3_PRESCALER		((0<<CS32) | (1<<CS31) | (1<<CS30)) //1 Tick = PRSC/OSC_CLCK= 64 / 12 MHz = 5.33 us
#define OCR3A_PERIOD_CNT	(0x493E) // 0.2ms/5kHz		Software Ticker 0x4E20 for PRSC=8 (0x09C4 for PRSC=64)
#define OCR3B_PERIOD_CNT	(0x927C) // 200ms/5Hz
#define OCR3C_PERIOD_CNT	(0xB720) // 250ms/4Hz


// EEPROM Memory addresses
#define EE_MODE						(0)
#define EE_SERIAL					(1)
#define EE_FLASH_SIZE				(2)
#define EE_WDRESET_COUNT			(3)
#define EE_IO_MODE1					(4)
#define EE_IO_MODE2					(5)
#define EE_IO_MODE3					(6)
#define EE_CAN_BAUDRATE				(7)
#define EE_SEND_FREQUENCY			(8)
#define EE_RECOUP_BALANCE_VAL		(9)
#define EE_VN200_SEND_MODE			(10)


/************************************************************************/
/* Define the Module, this Code is used                                 */
/************************************************************************/

// Activate/deactivate peripherals
		
#define HAS_BUZZER  (1)
#define HAS_LEDS    (1)
#define HAS_BUTTONS (1)
		
// Activate/deactivate CAN components

#define HAS_CAN_RX	(1)
#define HAS_200HZ	(1)
#define HAS_100HZ	(0)
#define HAS_50HZ	(1)
#define HAS_10HZ	(0)
	
/* RX Frames */
	
/* RX */
#if HAS_CAN_RX
		
	#define REQUEST_ID_MOTOR_TEMP (0)
	#define REQUEST_ID_ACTOR	  (1)
	#define REQUEST_ID_LV_AKKU	  (2)
		
	#define CAN_RX_ID (0x501)
	#define CAN_RX_LEN (8)
			
	/* static cmd String for CAN RX */
	static st_cmd_t dashboard_rx;
			
	/* general RX Frame, Request ID on first byte*/

	static union Dashboard_RX_general_un{
		U8 dataBuf[CAN_RX_LEN];
		struct Dashboard_RX_st{
			U8 REQUEST_ID;
			U8 ERRCODE;
			U8 PARAM3;
			U8 PARAM4;
			U8 PARAM5;
			U8 PARAM6;
			U8 PARAM7;
			U8 PARAM8;
		} dataStruct;
	} dashboard_rx_general_data;

	
		
	/* Request ID Motortemp */

	static union Dashboard_RX_motortemp_un{
		U8 dataBuf[CAN_RX_LEN];
		struct Dashboard_RX_motortemp_st{
			U8 REQUEST_ID;
			U8 ERRCODE;
			U8 MOTTEMP_REAR_LEFT;
			U8 MOTTEMP_REAR_RIGHT;
			U8 MOTTEMP_FRONT_RIGHT;
			U8 MOTTEMP_FRONT_LEFT;
			U8 PARAM7;
			U8 PARAM8;
		} dataStruct;
	} dashboard_rx_motortemp_data;

		
	/* Request ID Actor */
	/* Buzzer & LED */

	static union Dashboard_RX_actor_un{
		U8 dataBuf[CAN_RX_LEN];
		struct Dashboard_RX_actor_st{
			U8 REQUEST_ID;
			U8 ERRCODE;
			U8 LED;
			U8 BUZ;
			U8 SOC;
			U8 LV_VOLTAGE;
			U8 PARAM7;
			U8 PARAM8;
		} dataStruct;
	} dashboard_rx_actor_data;

		
	/* Request ID LV Akku */
	/* SOC & LV Voltage */
	static union Dashboard_RX_lvakku_un{
		U8 dataBuf[CAN_RX_LEN];
		struct Dashboard_RX_lvakku_st{
			U8 REQUEST_ID;
			U8 ERRCODE;
			U8 SOC;
			U8 LV_VOLTAGE;
			U8 PARAM5;
			U8 PARAM6;
			U8 PARAM7;
			U8 PARAM8;
		} dataStruct;
	} dashboard_rx_lvakku_data;


#endif // HAS_CAN_RX
	
/* TX Frame 1 */
#define	CAN_TX_50_ID	(0x503)
#define CAN_TX_50_LEN	(2)
static union Dashboard_TX_50_un{
	U8 dataBuf[CAN_TX_50_LEN];
	struct Dashboard_50_st {
		U8 REQUEST_ID;
		U8 KEYS;
		U8 MOTOR_POWER_FRONT;
		U8 MOTOR_POWER_REAR;
		U8 TORQUE_VECTORING;
		U8 TRACTION_CONTROL;
		U8 PARAM7;
		U8 PARAM8;
	} dataStruct;
} dashboard_50_data;
static st_cmd_t dashboard_50_tx;
	
/* TX Frame 2 */
#define	CAN_TX_200_ID	(0x504)
#define CAN_TX_200_LEN	(2)
static union Dashboard_TX_200_un{
	U8 dataBuf[CAN_TX_200_LEN];
	struct Dashboard_200_st {
		U8 ACCELERATION;
		U8 DRS;
		U8 PARAM3;
		U8 PARAM4;
		U8 PARAM5;
		U8 PARAM6;
		U8 PARAM7;
		U8 PARAM8;
	} dataStruct;
} dashboard_200_data;
static st_cmd_t dashboard_200_tx;




#endif /* GlobalIncludes_H_ */


