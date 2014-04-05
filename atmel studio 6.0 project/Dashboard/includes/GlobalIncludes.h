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
#define TMR1_PRESCALER		((0<<CS32) | (0<<CS31) | (1<<CS30)) //1 Tick = PRSC/OSC_CLCK= 1 / 12MHz = 83.3 ns
#define OCR1A_PERIOD_CNT	(0x960) //  200us/5kHz		
#define OCR1B_PERIOD_CNT	(0x2EE0) //  1us/1kHz
#define OCR1C_PERIOD_CNT	(0x5DC0) // 2us/500Hz
#define TMR3_PRESCALER		((0<<CS32) | (1<<CS31) | (1<<CS30)) //1 Tick = PRSC/OSC_CLCK= 64 / 12 MHz = 5.33 us
#define OCR3A_PERIOD_CNT	(0x4970) //  0.1ms/10Hz		
#define OCR3B_PERIOD_CNT	(0x92E0) //  200ms/5Hz
#define OCR3C_PERIOD_CNT	(0xB798) //  250ms/4Hz


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
/* Define Parameters for Build               */
/************************************************************************/

// Activate/deactivate peripherals
		
#define HAS_BUZZER  (1)
#define HAS_LEDS    (1)
#define HAS_BUTTONS (0)
#define HAS_DISPLAY (1)
		
// Activate/deactivate CAN components

#define HAS_CAN_RX	(1)
#define HAS_CAN_TX	(1)
#define HAS_5KHZ	(1)
#define HAS_1KHZ	(0)
#define HAS_500HZ	(0)
#define HAS_10HZ	(1)
#define HAS_5HZ		(0)
#define HAS_4HZ		(0)


/* Request IDs for Dashboard <-> VCU Connection */ 

#define REQUEST_SOC					(0)
#define REQUEST_CELL_VOLTAGE		(1)
#define REQUEST_TEMPERATURE			(2)
#define REQUEST_LV_VOLTAGE			(3)
#define REQUEST_MOTOR_TEMP_REAR		(4)
#define REQUEST_MOTOR_TEMP_FRONT	(5)
#define REQUEST_MOTOR_POWER_REAR	(4)
#define REQUEST_MOTOR_POWER_FRONT	(5)
#define REQUEST_TRACTION_CONTROL	(6)
#define REQUEST_TORQUE_VECTORING	(7)
#define REQUEST_ACCLERATION_MODE	(8)


	
/* RX Frames */
	
/* RX */
#if HAS_CAN_RX
	
		
	#define CAN_RX_ID (0x501)
	#define CAN_RX_LEN (8)
			
	/* static cmd String for CAN RX */
	static st_cmd_t dashboard_rx;

	static union Dashboard_RX_general_un{
		U8 dataBuf[CAN_RX_LEN];
		struct Dashboard_RX_st{
			U8 LEDS;
			U8 ERRCODE;
			U8 REQUEST_ID;
			U8 VALUE1;
			U8 VALUE2;
			U8 VALUE3;
			U8 VALUE4;
			U8 VALUE5;
		} dataStruct;
	} dashboard_rx_general_data;


#endif // HAS_CAN_RX

#if HAS_CAN_TX

	/* TX Frame 1 */
	#define	CAN_TX_10_ID	(0x502)
	#define CAN_TX_10_LEN	(8)
	static union Dashboard_TX_10_un{
		U8 dataBuf[CAN_TX_10_LEN];
		struct Dashboard_10_st {
			U8 REQUEST_ID;
			U8 ERROR_CODE;
			U8 KEYS;
			U8 VALUE1;
			U8 VALUE2;
			U8 VALUE3;
			U8 VALUE4;
			U8 VALUE5;
		} dataStruct;
	} dashboard_10_data;
	static st_cmd_t dashboard_10_tx;
	
#endif /* end HAS_CAN_TX */

#endif /* GlobalIncludes_H_ */


