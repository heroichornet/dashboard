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

display_line_t display_line_home={' ',' ',' ',' ',' ','A','M','Z',' ','g','r','i','m','s','e','l',' ',' ',' ',' '};
display_line_t display_line_error={' ',' ',' ',' ',' ',' ','E','R','R','O','R',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_soc={' ',' ','S','T','A','T','E',' ','O','F',' ','C','H','A','R','G','E',' ',' ',' '};
display_line_t display_line_min_cv_max={'M','I','N',' ',' ','C','E','L','L','V','O','L','T','A','G','E',' ','M','A','X'};
display_line_t display_line_cel_temp={' ','M','I','N',' ',' ','C','E','L','L','T','E','M','P',' ',' ','M','A','X',' '};
display_line_t display_line_lv_voltage={' ',' ',' ',' ','L','V',' ','V','O','L','T','A','G','E',' ',' ',' ',' ',' ',' '};
display_line_t display_line_motor_power_front={' ',' ','M','O','T','O','R',' ','P','O','W','E','R',' ','F','R','O','N','T',' '};
display_line_t display_line_motor_power_rear={ ' ',' ','M','O','T','O','R',' ','P','O','W','E','R',' ','R','E','A','R',' ',' '};
display_line_t display_line_motor_temp_front={' ','L',' ',' ',' ','M','O','T','O','R','T','E','M','P','.',' ',' ',' ','R',' '};
display_line_t display_line_motor_temp_rear={ ' ',' ','M','O','T','O','R',' ','T','E','M','P','.',' ','R','E','A','R',' ',' '};
display_line_t display_line_traction_control={' ',' ','T','R','A','C','T','I','O','N',' ','C','O','N','T','R','O','L',' ',' '};
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


#define INSTRUCTION_CLEAR_DISPLAY (0x01)
#define INSTRUCTION_CURSOR_HOME (0x02)
#define INSTRUCTION_ENTRY_MODE_SET (0x06) /* S=0, I/D=1 */
#define INSTRUCTION_DISPLAY_AC_UP (0x14)
#define INSTRUCTION_DISPLAY_AC_DOWN (0x10)
#define INSTRUCTION_DISPLAY_LEFT_SHIFT (0x18)
#define INSTRUCTION_DISPLAY_RIGHT_SHIFT (0x1C)
#define INSTRUCTION_DDRAM_ADDRESS_SET(x) ((0x80)|(x))
#define INSTRUCTION_BRIGHTNESS_100 (0b0000111000)
#define INSTRUCTION_BRIGHTNESS_75 (0b0000111000)
#define INSTRUCTION_BRIGHTNESS_50 (0b0000111000)
#define INSTRUCTION_BRIGHTNESS_25 (0b0000111000)
#define INSTRUCTION_DISPLAY_ON (0x0C)
#define INSTRUCTION_CURSOR_LEFT_SHIFT (0b0000010000)
#define INSTRUCTION_CURSOR_RIGHT_SHIFT (0b0000010100)

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
	PORTB&=~(1<<4);
	spi_putchar(START_BITS_WRITE_DATA);
	spi_putchar(data);
	PORTB|=(1<<4);
}

void display_write_instruction(uint8_t inst){
	PORTB&=~(1<<4);
	spi_putchar(START_BITS_WRITE_INSTRUCTION);
	spi_putchar(inst);
	PORTB|=(1<<4);
}

void display_write_display_lines(display_line_t s1,display_line_t s2){
	int i;
	display_write_instruction(INSTRUCTION_CURSOR_HOME);	// cursor to pos 1
	for(i=0;i<20;i++){
		display_write_data(s1[i]);
	}
	
	for(int i=0;i<20;i++){
		display_write_instruction(INSTRUCTION_CURSOR_RIGHT_SHIFT);	// cursor to second line
	};
			
	for(i=0;i<20;i++){
		display_write_data(s2[i]);
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
	spi_init(SPI_MASTER|SPI_MSB_FIRST|SPI_DATA_MODE_3|SPI_CLKIO_BY_64);
	Spi_disable_it();	
	Spi_select_master_mode();

	/* Display selected Menu init */
	selected_menu=DISPLAY_MENU_HOME;
	
	
	/*toggle button init */
	DDRB|=(1<<4);
	PORTB|=(1<<4);
	
	/* turn display on */
	display_write_instruction(INSTRUCTION_DISPLAY_ON);
	
	
	display_write_instruction(INSTRUCTION_BRIGHTNESS_100);

	
	
}

void display_update(uint8_t request_id, uint8_t value1,uint8_t value2,uint8_t value3, uint8_t value4, uint8_t value5){
	char * dpl=display_line_blank;
	
	switch(request_id){
		case DISPLAY_MENU_HOME:
				display_write_display_lines(display_line_home,display_line_blank);
			break;
		case DISPLAY_MENU_ERROR:
				display_write_display_lines(display_line_error,display_line_blank);
			break;
		case DISPLAY_MENU_SOC:
				display_make_display_line_percent(dpl,value1);
				display_write_display_lines(display_line_soc,dpl);
			break;
		case DISPLAY_MENU_MIN_AV_MAX_VOLT:
				display_make_display_line_min_av_max_volt(dpl,value1,value2,value3);
				display_write_display_lines(display_line_min_cv_max,dpl);
			break;
		case DISPLAY_MENU_MIN_AV_MAX_TEMP:
				display_make_display_line_min_av_max_temp(dpl,value1,value2,value3);
				display_write_display_lines(display_line_cel_temp,dpl);
			break;
		case DISPLAY_MENU_LV_VOLTAGE:
				display_make_display_line_lv_voltage(dpl,value1);
				display_write_display_lines(display_line_lv_voltage,dpl);
			break;
		case DISPLAY_MENU_MOTOR_TEMP_REAR:
				display_make_display_line_percent_bar(dpl,value1);
				display_write_display_lines(display_line_motor_temp_rear,dpl);
			break;
		case DISPLAY_MENU_MOTOR_TEMP_FRONT:
				display_make_display_line_motor_temp(dpl,value1,value2);
				display_write_display_lines(display_line_motor_temp_front,dpl);
			break;
		case DISPLAY_MENU_MOTOR_POWER_REAR:
				display_make_display_line_percent_bar(dpl,value1);
				display_write_display_lines(display_line_motor_power_rear,dpl);
			break;	
		case DISPLAY_MENU_MOTOR_POWER_FRONT:
				display_make_display_line_percent_bar(dpl,value1);
				display_write_display_lines(display_line_motor_power_front,dpl);
			break;
		case DISPLAY_MENU_TRACTION_CONTROL:
				display_make_display_line_percent_bar(dpl,value1);
				display_write_display_lines(display_line_traction_control,dpl);
			break;				
		case DISPLAY_MENU_TORQUE_VECTORING:
				display_make_display_line_percent_bar(dpl,value1);
				display_write_display_lines(display_line_torque_vectoring,dpl);		
			break;
		default:
			break;		
	}/* end switch */
}/* end display update */

void display_set_display_string(display_string_t s){
	memcpy(s,display_string,20);
}/* end display_set_display_string*/

void display_make_display_line_percent(char* dpl,uint8_t percent){
	#define GET_DEC_POS1_PERCENT(x) (char)(0b00110000+(x/100))
	#define GET_DEC_POS2_PERCENT(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS3_PERCENT(x) (char)(0b00110000+((x)%10))
	
	char pos_1=GET_DEC_POS1_PERCENT(percent);
	char pos_2=GET_DEC_POS2_PERCENT(percent);
	
	if(pos_1=='0'){
		pos_1=' ';
		if(pos_2=='0'){
			pos_2=' ';
		}
	}	
	
	display_line_t display_line_percent={' ',' ',' ',' ',' ',' ',' ',' ',pos_1,pos_2,GET_DEC_POS3_PERCENT(percent),'%',' ',' ',' ',' ',' ',' ',' ',' '};
	memcpy(dpl,display_line_percent,20);
}/* end display_make_display_line_percent */

void display_make_display_line_min_av_max_volt(char* dpl,uint8_t min_i,uint8_t av_i,uint8_t max_i){
	#define GET_DEC_POS1_VOLT(x) (char)(0b00110000+(x/100+2))
	#define GET_DEC_POS2_VOLT(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS3_VOLT(x) (char)(0b00110000+((x)%10))
	
	display_line_t dpl_volt={GET_DEC_POS1_VOLT(min_i),'.',GET_DEC_POS2_VOLT(min_i),GET_DEC_POS3_VOLT(min_i),'V',' ',' ',GET_DEC_POS1_VOLT(av_i),'.',GET_DEC_POS2_VOLT(av_i),GET_DEC_POS3_VOLT(av_i),'V',' ',' ',' ',GET_DEC_POS1_VOLT(max_i),'.',GET_DEC_POS2_VOLT(max_i),GET_DEC_POS3_VOLT(max_i),'V'};
	memcpy(dpl,dpl_volt,20);
}/*display_make_display_line_min_av_max_volt */

void display_make_display_line_percent_bar(char * dpl,uint8_t percent){
	#define GET_DEC_POS1_PERCENT_BAR(x) (x/100)
	#define GET_DEC_POS2_PERCENT_BAR(x) (char)(0b00110000+((x/10)%10))
		
		
	display_line_t display_line_percent={' ',' ',' ',' ','A','B','C','D','E','F','G','H','I','J',' ',' ',' ',' ',' ',' '};

	int i;
	for(i=0;i<((percent/10)%11);i++){
		display_line_percent[i+4]=(char)0b00010110;
	}
	
	for(i;i<10;i++){
		display_line_percent[i+4]=0b00101010;
	}
	i++;
	if(GET_DEC_POS1_PERCENT_BAR(percent)==1){
		display_line_percent[i+4]='1';
	}else{
		display_line_percent[i+4]=' ';
	}
	i++;	
	display_line_percent[i+4]=GET_DEC_POS2_PERCENT_BAR(percent);
	i++;
	display_line_percent[i+4]='0';
	i++;
	display_line_percent[i+4]='%';
	memcpy(dpl,display_line_percent,20);
	
}/* end display_make_display_line_percent_bar */	

void display_make_display_line_min_av_max_temp(char* dpl,uint8_t min_i,uint8_t av_i,uint8_t max_i){
	
	#define GET_DEC_POS1_TEMP(x) (char)(0b00110000+(x/100))
	#define GET_DEC_POS2_TEMP(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS3_TEMP(x) (char)(0b00110000+((x)%10))
	
	
	display_line_t dpl_volt={GET_DEC_POS1_TEMP(min_i),GET_DEC_POS2_TEMP(min_i),GET_DEC_POS3_TEMP(min_i),'°','C',' ',' ',GET_DEC_POS1_TEMP(av_i),GET_DEC_POS2_TEMP(av_i),GET_DEC_POS3_TEMP(av_i),'°','C',' ',' ',' ',GET_DEC_POS1_TEMP(max_i),GET_DEC_POS2_TEMP(max_i),GET_DEC_POS3_TEMP(max_i),'°','C'};
	memcpy(dpl,dpl_volt,20);
}/* end display_make_display_line_min_av_max_temp*/

void display_make_display_line_min_max_temp(char *dpl, char a, char b,char c,char d, char e,char f){
	display_line_t display_line_percent={' ',' ',a,b,c,'C',' ',' ',' ',' ',' ',' ',' ',' ',' ',d,e,f,'C',' '};
	memcpy(dpl,display_line_percent,20);
}/* end display_make_display_line_min_av_max_temp*/


void display_make_display_line_lv_voltage(dpl,value1){
	#define GET_DEC_POS1_LV_VOLT(x) (char)(0b00110000+(x/10))
	#define GET_DEC_POS2_LV_VOLT(x) (char)(0b00110000+((x)%10))
	#define GET_DEC_POS3_VOLT(x) (char)(0b00110000+((x)%100))
		
		
	display_line_t dpl_volt={' ',' ',' ',' ',' ',' ',' ',GET_DEC_POS1_TEMP(value1),GET_DEC_POS2_TEMP(value1),'.',GET_DEC_POS3_TEMP(value1),'V',' ',' ',' ',' ',' ',' ',' ',' '};
	memcpy(dpl,dpl_volt,20);
	
} /*end display_make_display_line_lv_voltage */

void display_make_display_line_motor_temp(dpl,value1,value2){
	
	#define GET_DEC_POS1_MOTOR_TEMP(x) (char)(0b00110000+(x/100))
	#define GET_DEC_POS2_MOTOR_TEMP(x) (char)(0b00110000+((x/10)%10))		
	#define GET_DEC_POS3_MOTOR_TEMP(x) (char)(0b00110000+((x)%10))
	
	char pos_1a=GET_DEC_POS1_MOTOR_TEMP(value1);
	char pos_2a=GET_DEC_POS2_MOTOR_TEMP(value1);
	char pos_1b=GET_DEC_POS1_MOTOR_TEMP(value2);
	char pos_2b=GET_DEC_POS2_MOTOR_TEMP(value2);	
	
	if(pos_1a=='0'){
		pos_1a=' ';
		if(pos_2a=='0'){
			pos_2a=' ';			
		}
	}	
	
	if(pos_1b=='0'){
			pos_1b=' ';
			if(pos_2b=='0'){
				pos_2b=' ';
			}
	}	
		
			
	display_line_t dpl_volt={' ',pos_1a,pos_2a,GET_DEC_POS1_MOTOR_TEMP(value1),'°','C',' ',' ',' ',' ',' ',' ',' ',' ',pos_1b,pos_1b,GET_DEC_POS3_MOTOR_TEMP(value2),'°','C',' '};
	memcpy(dpl,dpl_volt,20);
	
} /*end display_make_display_line_motor_temp*/