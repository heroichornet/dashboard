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
#define TMR1_PRESCALER		((0<<CS32) | (1<<CS31) | (0<<CS30)) //1 Tick = PRSC/OSC_CLCK= 8 / 16MHz = 0.5 us
#define OCR1A_PERIOD_CNT	(0x2710) // 5ms/200Hz		Software Ticker 0x4E20 for PRSC=8 (0x09C4 for PRSC=64)
#define OCR1B_PERIOD_CNT	(0x4E20) // 10ms/100Hz
#define OCR1C_PERIOD_CNT	(0x9C40) // 20ms/50Hz
#define TMR3_PRESCALER		((0<<CS32) | (1<<CS31) | (1<<CS30)) //1 Tick = PRSC/OSC_CLCK= 64 / 16MHz = 4us
#define OCR3A_PERIOD_CNT	(0x61A8) // 100ms/10Hz		Software Ticker 0x4E20 for PRSC=8 (0x09C4 for PRSC=64)
#define OCR3B_PERIOD_CNT	(0xC350) // 200ms/5Hz
#define OCR3C_PERIOD_CNT	(0xF424) // 250ms/4Hz


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

#define MCM_FRONT	(1)
#define MCM_LVBOX	(2)
#define MCM_REAR	(3)
#define MCM_HVBOX	(4)
#define MCM_AD	(5)
#define MCM_AD_IS_REAR (0)
#define MCM_AD_IS_RIGHT (0)
#define DASHBOARD	(6)


#define MCM DASHBOARD

#if MCM==MCM_FRONT
	#define HAS_CAN_RX 0
	#define HAS_200HZ 1
	#define HAS_100HZ 0
	#define HAS_50HZ 0
	#define HAS_10HZ 1
	#define HAS_ADC 1
	
	#define IO_PORTB_OR (0x00)
	#define IO_PORTB_AND (0x7E)
	#define IO_PORTD_OR (0x00)
	#define IO_PORTD_AND (0xFE)

	#define CAN_TX_200_ID	(0x101)
	#define CAN_TX_200_LEN	(6)
	static union MCM_FRONT_TX_200_un{
		U8 dataBuf[CAN_TX_200_LEN];//CAN_TX_200_LEN
		struct MCM_FRONT_TX_200_st {
			U16 steeringangle;
			U8 throttlep;
			U8 throttlem;
			U8 brakeforce;
			U8 errorCode;
		} dataStruct;
	} mcm_front_200_data;
	static st_cmd_t mcm_front_200_tx;

	#define CAN_TX_10_ID	(0x102)
	#define CAN_TX_10_LEN	(4)
	static union MCM_FRONT_TX_10_un{
		U8 dataBuf[CAN_TX_10_LEN];
		struct MCM_FRONT_TX_10_st {
			U8 preBOTS;
			U8 BOTS;
			U8 brakePressureF;
			U8 brakePressureR;
		} dataStruct;
	} mcm_front_10_data;
	static st_cmd_t mcm_front_10_tx;

	#if HAS_CAN_RX
		#define CAN_RX_ID	(0x103)
		#define CAN_RX_LEN	(0)
		static union MCM_FRONT_RX_un{
			U8 dataBuf[CAN_RX_LEN];
			struct MCM_FRONT_RX_st{
			} dataStruct;
		} mcm_front_rx_data;
		static st_cmd_t mcm_front_rx;
	#endif
	
	// nADWerte*15*2^x/200kHz
	#define MCM_ADC_PRESCALER 3
	static U8 mcm_front_current_ADC;
#endif

#if MCM==MCM_LVBOX
	#define HAS_CAN_RX 1
	#define HAS_200HZ 0
	#define HAS_100HZ 0
	#define HAS_50HZ 0
	#define HAS_10HZ 1
	#define HAS_ADC 1
	
	#define IO_PORTB_OR (0x00)
	#define IO_PORTB_AND (0x7E)
	#define IO_PORTD_OR (0x03)
	#define IO_PORTD_AND (0xFF)

	#define CAN_TX_10_ID	(0x701)
	#define CAN_TX_10_LEN	(8)
	static union MCM_LVBOX_TX_10_un{
		U8 dataBuf[CAN_TX_10_LEN];
		struct MCM_LVBOX_TX_10_st {
			U8 coolTemp1;
			U8 coolTemp2;
			U8 lvCell1;
			U8 lvCell2;
			U8 lvCell3;
			U8 lvTemp;
			U8 IMDF;
			U8 errorCode;
		} dataStruct;
	} mcm_lvbox_10_data;
	static st_cmd_t mcm_lvbox_10_tx;

	#if HAS_CAN_RX
		#define CAN_RX_ID	(0x702)
		#define CAN_RX_LEN	(4)
		static union MCM_LVBOX_RX_un{
			U8 dataBuf[CAN_RX_LEN];
			struct MCM_LVBOX_RX_st{
				U8 pumpe1;
				U8 pumpe2;
				U8 IMDFActive;
				U8 IMDFReset;
			} dataStruct;
		} mcm_lvbox_rx_data;
		static st_cmd_t mcm_lvbox_rx;
	#endif
	
	// nADWerte*15*2^x/200kHz
	#define MCM_ADC_PRESCALER 7
	static U8 mcm_lvbox_current_ADC;
#endif

#if MCM==MCM_REAR
	#define HAS_CAN_RX 1
	#define HAS_200HZ 0
	#define HAS_100HZ 0
	#define HAS_50HZ 0
	#define HAS_10HZ 1
	#define HAS_ADC 0
	
	#define IO_PORTB_OR (0x03)
	#define IO_PORTB_AND (0x7F)
	#define IO_PORTD_OR (0x00)
	#define IO_PORTD_AND ~(0x03)

	#define CAN_TX_10_ID	(0x601)
	#define CAN_TX_10_LEN	(3)
	static union MCM_REAR_TX_10_un{
		U8 dataBuf[CAN_TX_10_LEN];
		struct MCM_RAER_TX_10_st {
			U8 preENRE;
			U8 preMS;
			U8 errorCode;
		} dataStruct;
	} mcm_rear_10_data;
	static st_cmd_t mcm_rear_10_tx;

	#if HAS_CAN_RX
		#define CAN_RX_ID	(0x602)
		#define CAN_RX_LEN	(2)
		static union MCM_REAR_RX_un{
			U8 dataBuf[CAN_RX_LEN];
			struct MCM_REAR_RX_st{
				U8 brakeLight;
				U8 ENRE;
			} dataStruct;
		} mcm_rear_rx_data;
		static st_cmd_t mcm_rear_rx;
	#endif
#endif

#if MCM==MCM_HVBOX
	#define HAS_CAN_RX 1
	#define HAS_200HZ 0
	#define HAS_100HZ 0
	#define HAS_50HZ 0
	#define HAS_10HZ 1
	#define HAS_ADC 0
	
	#define IO_PORTB_OR (0x0C)
	#define IO_PORTB_AND ~(0x82)
	#define IO_PORTD_OR (0x01)
	#define IO_PORTD_AND ~(0x02)
	#define IO_PORTE_OR (0x91)
	#define IO_PORTE_AND ~(0x62)
	
	#define CAN_TX_10_ID	(0x401)
	#define CAN_TX_10_LEN	(5)
	static union MCM_HVBOX_TX_10_un{
		U8 dataBuf[CAN_TX_10_LEN];
		struct MCM_RAER_TX_10_st {
			U8 IMD;
			U8 BPD;
			U8 HVDI;
			U8 MS;
			U8 errorCode;
		} dataStruct;
	} mcm_hvbox_10_data;
	static st_cmd_t mcm_hvbox_10_tx;

	#if HAS_CAN_RX
		#define CAN_RX_ID	(0x402)
		#define CAN_RX_LEN	(3)
		static union MCM_HVBOX_RX_un{
			U8 dataBuf[CAN_RX_LEN];
			struct MCM_HVBOX_RX_st{
				U8 preCharge;
				U8 AIRp;
				U8 Fan1;
				U8 Fan2;
				U8 showBPD;
			} dataStruct;
		} mcm_hvbox_rx_data;
		static st_cmd_t mcm_hvbox_rx;
	#endif
#endif

#if MCM==MCM_AD
		#include "AD.h"

		#define HAS_CAN_RX 1
		#define HAS_200HZ 0
		#define HAS_100HZ 0
		#define HAS_50HZ 0
		#define HAS_10HZ 1
		#define HAS_ADC 1
		#define HAS_PWM

		#define IO_PORTB_OR (0x80)
		#define IO_PORTB_AND (0xFE)
		#define IO_PORTD_OR (0x00)
		#define IO_PORTD_AND (0xFE)

		#define CAN_TX_10_ID	(0x401+(MCM_AD_IS_REAR*100+MCM_AD_IS_RIGHT*2))
		#define CAN_TX_10_LEN	(6)
		static union MCM_AD_TX_10_un{
			U8 dataBuf[CAN_TX_10_LEN];
			struct MCM_AD_TX_10_st {
				U16 Speed;
				U8 SpeedSign;
				U16 Position;
				U8 errorCode;
			} dataStruct;
		} mcm_ad_10_data;
		static st_cmd_t mcm_ad_10_tx;

		#if HAS_CAN_RX
		#define CAN_RX_ID	(0x501)
		#define CAN_RX_LEN	(8)
		static union MCM_AD_RX_un{
			U8 dataBuf[CAN_RX_LEN];
			struct MCM_AD_RX_st{
				U8 BoundD1;
				U8 BoundGap;
				U8 BoundD2;
				U8 BoundOff2;
				U8 ReBoundD1;
				U8 ReBoundGap;
				U8 ReBoundD2;
				U8 ReBoundOff2;
			} dataStruct;
		} mcm_ad_rx_data;
		static st_cmd_t mcm_ad_rx;
		#endif

		// nADWerte*15*2^x/200kHz
		#define MCM_ADC_PRESCALER 0
		static U8 mcm_ad_current_ADC;
#endif
	
	


		#define HAS_CAN_RX	(1)
		#define HAS_200HZ	(1)
		#define HAS_100HZ	(0)
		#define HAS_50HZ	(1)
		#define HAS_10HZ	(0)
		#define HAS_ADC		(0)
	
	
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


