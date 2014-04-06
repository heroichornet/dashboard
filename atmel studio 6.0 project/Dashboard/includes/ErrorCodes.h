/*
 * ErrorCodes.h
 *
 * Created: 22.03.2014 15:00:12
 *  Author: michael
 */ 


#ifndef ERRORCODES_H_
#define ERRORCODES_H_

#define ERRROR_NONE 0
#define ERROR_SC_DOWN 1
#define ERROR_PRE_MASTER 2
#define ERROR_PRE_BOTS 3
#define ERROR_HVDI 4
#define ERROR_IMD 5
#define ERROR_IMDF 6
#define ERROR_IMDF 7
#define ERRROR_PBD 11

/* error Strings */

display_line_t display_line_error_none={'#','X','X','X',' ',' ',' ','N','O','N','E',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_sc_down={'#','X','X','X',' ','S','C',' ','D','O','W','N',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_unknown_code={'#','X','X','X',' ','U','N','K','N','O','W','N',' ','E','R','R','O','R',' '};
display_line_t display_line_error_pre_master={'#','X','X','X',' ','P','R','E',' ','M','A','S','T','E','R',' ',' ',' ',' '};
display_line_t display_line_error_pre_bots={'#','X','X','X',' ','P','R','E',' ','B','O','T','S',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_hvdi={'#','X','X','X',' ','H','V','D','I',' ','I','N','T','E','R','U','P','T',' '};
display_line_t display_line_error_imd={'#','X','X','X',' ','I','M','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_imdf={'#','X','X','X',' ','I','M','D','F',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_error_bpd={'#','X','X','X',' ','B','R','A','K','E',' ','P','.','D','.',' ',' ',' ',' '};





#endif /* ERRORCODES_H_ */