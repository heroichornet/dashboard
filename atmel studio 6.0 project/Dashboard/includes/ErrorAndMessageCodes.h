/*
 * ErrorCodes.h
 *
 * Created: 22.03.2014 15:00:12
 *  Author: michael
 */ 


#ifndef ERRORANDMESSAGECODES_H_
#define ERRORANDMESSAGECODES_H_

/*errors */
#define ERRROR_NONE (0)
#define ERROR_SC_DOWN (1)
#define ERROR_PRE_ENRE (2)
#define ERROR_BOTS (3)
#define ERROR_PRE_BOTS (4)
#define ERROR_HVDI (5)
#define ERROR_IMD (6)
#define ERROR_IMDF (7)
#define ERRROR_PBD (10)

#define ERROR_BMS (20)
#define ERROR_BMS_UNDERVOLTAGE (21)
#define ERROR_BMS_OVERCURRENT (22)
#define ERROR_BMS_OVERTEMP (23)

#define ERROR_MC (30) // 30 bis 39

#define ERROR_MCM_A (40) // 40 
#define ERROR_MCM_B (50) // bis 59

#define ERROR_THROTTLE_FAIL (81)	
#define ERROR_BRAKE_FORCE_FAIL (82)

/* missing errors */
#define ERROR_MISSING_MCM_REAR (90)
#define ERROR_MISSING_MCM_FRONT (91)
#define ERROR_MISSING_MCM_LVB (92)
#define ERROR_MISSING_MCM_AB (93)
#define ERROR_MISSING_MC_LEFT (94)
#define ERROR_MISSING_MC_RIGHT (95)
#define ERROR_MISSING_SHUNT (96)

#define ERROR_AIRror (99) // Airs verschweisst


/* error Strings */
display_line_t display_line_error_none={'#','X','X','X',' ',' ',' ','N','O','N','E',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_sc_down={'#','X','X','X',' ','S','C',' ','D','O','W','N',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_unknown_code={'#','X','X','X',' ','U','N','K','N','O','W','N',' ','E','R','R','O','R',' '};
display_line_t display_line_error_pre_enre={'#','X','X','X',' ','P','R','E',' ','E','N','R','E',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_pre_bots={'#','X','X','X',' ','P','R','E',' ','B','O','T','S',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_bots={'#','X','X','X',' ','B','O','T','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_hvdi={'#','X','X','X',' ','H','V','D',' ','I','N','T','E','R','L','O','C','K',' ',};
display_line_t display_line_error_imd={'#','X','X','X',' ','I','M','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_imdf={'#','X','X','X',' ','I','M','D','F',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_bpd={'#','X','X','X',' ','B','R','A','K','E',' ','P','.','D','.',' ',' ',' ',' '};
display_line_t display_line_error_bad_request_id={'#','X','X','X',' ','B','A','D','R','E','Q','U','E','S','T',' ','I','D',' '};
display_line_t display_line_error_bms={'#','X','X','X',' ','B','M','S',' ','E','R','R','O','R',' ',' ',' ',' ',' '};
display_line_t display_line_error_mc={'#','X','X','X',' ','M','C',' ','E','R','R','O','R',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_mcm={'#','X','X','X',' ','M','C','M',' ','E','R','R','O','R',' ',' ',' ',' ',' '};
	
/* Bms error strings */
display_line_t display_line_bms_undervoltage={'#','X','X','X',' ','B','M','S',' ','U','N','D','E','R','V','O','L','T','.'};
display_line_t display_line_bms_overcurrent={'#','X','X','X',' ','B','M','S',' ','O','V','E','R','C','U','R','R','N','T'};
display_line_t display_line_bms_overtemp={'#','X','X','X',' ','B','M','S',' ','O','V','E','R','T','E','M','P',' ',' '};


/* further errors */
display_line_t display_line_throttle_fail={'#','X','X','X',' ','T','H','R','O','T','T','E','L',' ','F','A','I','L',' '};
display_line_t display_line_brake_force_fail={'#','X','X','X',' ','B','R','K','F','R','C','E',' ','F','A','I','L',' ',' '};


/* missing hardware errors */
display_line_t display_line_error_missing_mcm_rear={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','M','C','M','R',' ',' '};
display_line_t display_line_error_missing_mcm_front={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','M','C','M','F',' ',' '};
display_line_t display_line_error_missing_mcm_lvb={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','M','C','M','L','V','B'};
display_line_t display_line_error_missing_mcm_ab={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','M','C','M','A','B',' '};
display_line_t display_line_error_missing_mc_left={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','M','C','-','L',' ',' '};
display_line_t display_line_error_missing_mc_right={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','M','C','-','R',' ',' '};
display_line_t display_line_error_missing_shunt={'#','X','X','X',' ','M','I','S','S','I','N','G',' ','S','H','U','N','T',' '};


display_line_t display_line_air_ror={'#','X','X','X',' ','A','I','R','r','o','r',' ',' ',' ',' ',' ',' ',' ',' '};


#define MESSAGE_STARTING_TS (101)
#define MESSAGE_CHECK_MS (102)
#define MESSAGE_PRECHARGING (103)
#define MESSAGE_PRECHARGED (104)
#define MESSAGE_STARTING_MOTOR_CONTROLLER (105)
#define MESSAGE_READY_2_DRIVE (106)
#define MESSAGE_MANUAL_MC (107)
#define MESSAGE_PRECHARGE_ONLY (108)

#define MESSAGE_ENRE_FAIL (201)
#define MESSAGE_MS_OPEN (202)
#define MESSAGE_PRECHARGE_FAIL (203)
#define MESSAGE_MC_FAIL (204)


#define MESSAGE_BOOT_UP (255)

/* Message Strings */
display_line_t display_line_message_starting_ts={'#','X','X','X',' ',' ',' ','S','T','A','R','T','I','N','G',' ','T','S',' ',' '};
display_line_t display_line_message_check_ms={'#','X','X','X',' ',' ',' ','C','H','E','C','K',' ','M','S',' ',' ',' ',' ',' '};
display_line_t display_line_message_precharging={'#','X','X','X',' ',' ',' ','P','R','E','C','H','A','R','G','I','N','G',' ',' '};
display_line_t display_line_message_precharged={'#','X','X','X',' ',' ',' ','P','R','E','C','H','A','R','G','E','D',' ',' ',' '};
display_line_t display_line_message_starting_motor_controller={'#','X','X','X',' ',' ',' ','P','R','E','C','H','A','R','G','E','D',' ',' ',' '};
display_line_t display_line_message_ready_2_drive={'#','X','X','X',' ',' ',' ','R','E','A','D','Y',' ','2',' ','D','R','I','V','E'};
display_line_t display_line_message_manual_mc={'#','X','X','X',' ',' ',' ','M','A','N','U','A','L',' ','M','C',' ',' ',' ',' '};
display_line_t display_line_message_precharge_only={'#','X','X','X',' ',' ','P','R','E','C','H','A','R','G','E','O','N','L','Y',' '};
display_line_t display_line_message_enre_fail={'#','X','X','X',' ',' ',' ','E','N','R','E',' ','F','A','I','L',' ',' ',' ',' '};
display_line_t display_line_message_ms_open={'#','X','X','X',' ',' ',' ','M','S',' ','O','P','E','N',' ',' ',' ',' ',' ',' '};
display_line_t display_line_message_precharge_fail={'#','X','X','X',' ',' ',' ','P','R','E',' ','C','H','R','G',' ','F','A','I','L'};	
display_line_t display_line_message_mc_fail={'#','X','X','X',' ',' ',' ','M','C',' ','F','A','I','L',' ',' ',' ',' ',' ',' '};	
display_line_t display_line_message_boot_up={'#','X','X','X',' ',' ',' ','B','O','O','T',' ','U','P',' ',' ',' ',' ',' ',' '};	
	
	

#endif /* ERRORANDMESSAGECODES_H_ */
