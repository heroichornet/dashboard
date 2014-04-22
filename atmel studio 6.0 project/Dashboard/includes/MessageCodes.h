/*
 * MessageCodes.h
 *
 * Created: 22.04.2014 09:25:26
 *  Author: michael
 */ 


#ifndef MESSAGECODES_H_
#define MESSAGECODES_H_

#define MESSAGE_STARTING_TS (101)
#define MESSAGE_CHECK_MS (102)
#define MESSAGE_PRECHARGING (103)
#define MESSAGE_PRECHARGED (104)
#define MESSAGE_STARTING_MOTOR_CONTROLLER (105)
#define MESSAGE_READY_2_DRIVE (106)
#define MESSAGE_ENRE_FAIL (201)
#define MESSAGE_MS_OPEN (202)
#define MESSAGE_PRECHARGE_FAIL (203)
#define MESSAGE_MOTORCONTROLLER_FAIL (204)


/* Message Strings */
display_line_t display_line_message_starting_ts={'#','X','X','X',' ',' ',' ','S','T','A','R','T','I','N','G',' ','T','S',' ',' '};
display_line_t display_line_message_check_ms={'#','X','X','X',' ',' ',' ','C','H','E','C','K',' ','M','S',' ',' ',' ',' ',' '};
display_line_t display_line_message_precharging={'#','X','X','X',' ',' ',' ','P','R','E','C','H','A','R','G','I','N','G',' ',' '};
display_line_t display_line_message_precharged={'#','X','X','X',' ',' ',' ','P','R','E','C','H','A','R','G','E','D',' ',' ',' '};
display_line_t display_line_message_starting_motor_controller={'#','X','X','X',' ',' ',' ','P','R','E','C','H','A','R','G','E','D',' ',' ',' '};
display_line_t display_line_message_ready_2_drive={'#','X','X','X',' ',' ',' ','R','E','A','D','Y',' ','2',' ','D','R','I','V','E'};
display_line_t display_line_message_enre_fail={'#','X','X','X',' ',' ',' ','E','N','R','E',' ','F','A','I','L',' ',' ',' ',' '};
display_line_t display_line_message_ms_open={'#','X','X','X',' ',' ',' ','M','S',' ','O','P','E','N',' ',' ',' ',' ',' ',' '};
display_line_t display_line_message_precharge_fail={'#','X','X','X',' ',' ',' ','P','R','E',' ','C','H','R','G',' ','F','A','I','L'};	
display_line_t display_line_message_mc_fail={'#','X','X','X',' ',' ',' ','M','C',' ','F','A','I','L',' ',' ',' ',' ',' ',' '};	



	




#endif /* MESSAGECODES_H_ */