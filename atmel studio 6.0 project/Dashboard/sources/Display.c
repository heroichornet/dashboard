/*!
 * Display.c
 *
 *  Created on: Jan 22, 2014
 *      Author: michael
 *
 *	This Library can be used to 
 *
 */

#include <stdint.h>
#include <avr/io.h>
#include "../includes/Display.h"
#include "../includes/spi_lib.h"
#include <string.h>

/* Display Data Ram (DDRAM)
 * 0x00 till 0x27
 * 0x40 till 0x67
 */

uint8_t display_ddram_top_row[28];
uint8_t display_ddram_bottom_row[28];

/* Display Strings*/

display_line_t display_line_home={' ',' ',' ',' ',' ',' ','A','M','Z',' ','g','r','i','m','s','e','l',' ',' ',' '};
display_line_t display_line_error={' ',' ',' ',' ',' ',' ','E','R','R','R','O','R',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_soc={' ',' ','S','T','A','T','E',' ','O','F',' ','C','H','A','R','G','E',' ',' ',' '};
display_line_t display_line_min_cv_max={' ',' ','M','I','N',' ','C','E','L','L','V','O','L','T','A','G','E','M','A','X'};
display_line_t display_line_cel_temp={' ',' ','M','I','N',' ','C','E','L','L','t','E','M','P',' ',' ','M','A','X',' '};
display_line_t display_line_motor_power_front={' ',' ','M','O','T','O','R',' ','P','O','W','E','R',' ','F','R','O','N','T',' '};
display_line_t display_line_motor_power_rear={ ' ',' ','M','O','T','O','R',' ','P','O','W','E','R',' ','R','E','A','R',' ',' '};
display_line_t display_line_torque_vectoring={' ',' ','T','O','R','Q','U','E',' ',' ','V','E','C','T','O','R','I','N','G',' '};
display_line_t display_line_accleration_mode={ ' ',' ','A','C','C','E','L','E','R','A','T','I','O','N',' ','M','O','D','E',' '};
display_line_t display_line_blank={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	

/* Character Generator Ram (CGRAM)
 * stores pixel info, 1=pixel on, 0=pixel off
 * 5*8 pixel / char
 * Valid addresses 0x00 till 0x3F
 * User defined characters are from 0x00 till 0x07 or 0x08 till 0x0F
 */
#define	CGRAM_A 0x41;
#define CGRAM_B 0x42;
#define CGRAM_C 0x43;
#define CGRAM_D 0x44;

/* Instructions */

#define INSTRUCTION_CLEAR_DISPLAY 0x01
#define INSTRUCTION_CURSOR_HOME 0x02
#define INSTRUCTION_ENTRY_MODE_SET 0x06 /* S=0, I/D=1 */
#define INSTRUCTION_DISPLAY_AC_UP 0x14
#define INSTRUCTION_DISPLAY_AC_DOWN 0x10
#define INSTRUCTION_DISPLAY_LEFT_SHIFT 0x18
#define INSTRUCTION_DISPLAY_RIGHT_SHIFT 0x1C
#define INSTRUCTION_DDRAM_ADDRESS_SET(x) ((0x80)|(x))

/* Start Bit */
#define START_BITS_READ_INSTRUCTION (0xF8|0x04|0x00)
#define	START_BITS_READ_DATA (0xF8|0x04|0x02)
#define	START_BITS_WRITE_INSTRUCTION (0xF8|0x00|0x00)
#define START_BITS_WRITE_DATA (0xF8|0x00|0x02)


/* Address Counter (AC) 
*	 with DDRAM: 
*	 overflows from 0x40 to 0x27 and 0x00 to 0x67 
* 	 with CGRAM:
* 	 overflows from 0x3F to 0x00
*/

uint8_t address_counter; 


display_string_t test={'0','1','2','3','4','5','6','7','8','9',
					 'A','B','C','D','E','F','G','H','I','J'};

void display_write_data(uint8_t data){
	spi_write_buffer(START_BITS_WRITE_DATA,data);	
}

void display_write_instruction(uint8_t inst){
	spi_write_buffer(START_BITS_WRITE_INSTRUCTION,inst);
}

void display_write_display_line(display_line_t s){
	int i;
	display_write_instruction(INSTRUCTION_CURSOR_HOME);	// cursor to pos 1
	for(i=0;i<20;i++){
		display_write_data(s[i]);
	}	
}


void display_init(void){
	/* SPI */
		/* width 8 Bit */
		/* is MSB  */
		/* Clock ploarity is high */
		/* Clock phase is change on leading edge */
		/* parity is none */
		/* chip select toggle is no */
		/* clock rate index is 0 */
		/* clock rate is CPU clock, so 12MHz and 16Mhz withe new quarz */
	spi_init(SPI_MASTER|SPI_MSB_FIRST|SPI_DATA_MODE_2|SPI_CLKIO_BY_32);
	
	
	/* Display selected Menu init */
	selected_menu=DISPLAY_MENU_HOME;
	
}

void display_update(void){
	switch(selected_menu){
		case DISPLAY_MENU_HOME:
				display_write_display_line(display_line_home);
			break;
		case DISPLAY_MENU_ERROR:
				display_write_display_line(display_line_error);
			break;
		case DISPLAY_MENU_SOC:
			break;
		case DISPLAY_MENU_MIN_AV_MAX_VOLT:
			break;
		case DISPLAY_MENU_MIN_AV_MAX_TEMP:
			break;
		case DISPLAY_MENU_TORQUE_VECTORING:
			break;
		default:
			break;		
	}/* end switch */
}/* end display update */

void display_set_display_string(display_string_t s){
	memcpy(s,display_string,20);
}/* end display_set_display_string*/

void display_make_display_line_percent(display_line_t dpl,char a, char b){
	display_line_t display_line_percent={' ',' ',' ',' ',' ',' ',a,b,'%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	dpl=display_line_percent;
}/* end display_make_display_line_percent */

void display_make_display_line_min_av_max_volt(display_line_t dpl,char a, char b,char c,char d, char e,char f){
	display_line_t display_line_percent={' ',' ',a,b,'V',' ',c,d,'V',' ',' ',' ',' ',' ',' ',' ',e,f,'V',' '};
	dpl=display_line_percent;
}/*display_make_display_line_min_av_max_volt */

void display_make_display_line_percent_bar(display_line_t dpl,uint8_t percent){
	display_line_t display_line_percent={' ',' ',' ',' ','A','B','C','D','E','F','G','H','I','J',' ',' ',' ',' ',' ',' '};

	int i;
	for(i=0;i<percent;i++){
		display_line_percent[i+4]=(char)0b10000110;
	}
	
	for(i;i<10;i++){
		display_line_percent[i+4]='o';
	}
	dpl=display_line_percent;
	
}/* end display_make_display_line_percent_bar */	

void display_make_display_line_min_av_max_temp(display_line_t dpl,char a, char b,char c,char d, char e,char f){
	display_line_t display_line_percent={' ',' ',a,b,'C',' ',c,d,'C',' ',' ',' ',' ',' ',' ',' ',e,f,'C',' '};
	dpl=display_line_percent;
}/* end display_make_display_line_min_av_max_temp*/

void display_make_display_line_min_max_temp(display_line_t dpl, char a, char b,char c,char d, char e,char f){
	display_line_t display_line_percent={' ',' ',a,b,c,'C',' ',' ',' ',' ',' ',' ',' ',' ',' ',d,e,f,'C',' '};
	dpl=display_line_percent;
}/* end display_make_display_line_min_av_max_temp*/