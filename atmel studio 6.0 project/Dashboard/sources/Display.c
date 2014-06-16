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
#include <string.h>

#include "../includes/spi_lib.h"
#include "../includes/Display.h"
#include "../includes/ErrorAndMessageCodes.h"



#define SPI_START_PORT (PORTA)
#define SPI_START_PIN (5)
#define SPI_START_DDR (DDRA)

/* Display Data Ram (DDRAM)
 * 0x00 till 0x27
 * 0x40 till 0x67
 */

uint8_t display_ddram_top_row[28];
uint8_t display_ddram_bottom_row[28];

/* Display Strings*/

display_line_t display_line_home={' ',' ',' ',' ',' ','A','M','Z',' ','g','r','i','m','s','e','l',' ',' ',' ',' '};
display_line_t display_line_error={' ',' ',' ',' ',' ',' ',' ','E','R','R','O','R',' ',' ',' ',' ',' ',' '};
display_line_t display_line_message={' ',' ',' ',' ',' ',' ',' ','M','E','S','S','A','G','E',' ',' ',' ',' ',' '};
display_line_t display_line_soc={' ',' ','S','T','A','T','E',' ','O','F',' ','C','H','A','R','G','E',' ',' ',' '};
display_line_t display_line_min_cv_max={'M','I','N',' ',' ','C','E','L','L','V','O','L','T','A','G','E',' ','M','A','X'};
display_line_t display_line_cel_temp={' ','M','I','N',' ',' ','C','E','L','L','T','E','M','P',' ',' ','M','A','X',' '};
display_line_t display_line_lv_voltage={' ',' ',' ',' ','L','V',' ','V','O','L','T','A','G','E',' ',' ',' ',' ',' ',' '};
display_line_t display_line_motor_power_front={' ',' ','M','O','T','O','R',' ','T','O','R','Q','U','E',' ','F','R','O','N','T'};
display_line_t display_line_motor_power_rear={ ' ',' ','M','O','T','O','R',' ','T','O','R','Q','U','E',' ','R','E','A','R',' '};
display_line_t display_line_motor_temp_front={ ' ',' ','M','O','T','O','R',' ','T','E','M','P','.',' ','F','R','O','N','T',' '};
display_line_t display_line_motor_temp_rear={ ' ',' ','M','O','T','O','R',' ','T','E','M','P','.',' ','R','E','A','R',' ',' '};
display_line_t display_line_traction_control={' ',' ','T','R','A','C','T','I','O','N',' ','C','O','N','T','R','O','L',' ',' '};
display_line_t display_line_torque_vectoring={' ',' ','T','O','R','Q','U','E',' ',' ','V','E','C','T','O','R','I','N','G',' '};
display_line_t display_line_accleration_mode={ ' ',' ','A','C','C','E','L','E','R','A','T','I','O','N',' ','M','O','D','E',' '};	
display_line_t display_line_accleration_mode_normal={ ' ',' ','N','O','R','M','A','L',' ','D','R','I','V','E',' ',' ',' ',' ',' ',' '};
display_line_t display_line_accleration_mode_ready={ ' ','A','C','C','E','L','E','R','A','T','I','O','N',' ','R','E','A','D','Y',' '};	
display_line_t display_line_accleration_mode_go_go={' ', ' ','<','<','G','O','!',' ','G','O','!',' ','G','O','!','>','>',' ',' ',' '};		
display_line_t display_line_buttons_pressed={ ' ',' ','B','U','T','T','O','N',' ','P','R','E','S','S','E','D',' ',' ',' ',' '};
display_line_t display_line_blank={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_tsal1={' ',' ',' ',' ',' ',' ','R','E','A','D','Y',' ',' ','T','O',' ',' ',' ',' ',' '};
display_line_t display_line_tsal2={' ',' ',' ',' ',' ',' ',' ',' ','D','R','I','V','E',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_starting={'<','<',' ',' ',' ','S','T','A','R','T','I','N','G',' ','U','P',' ',' ','>','>'};
display_line_t display_line_brake_balance={'L',' ','B','R','A','K','E',' ','B','A','L','A','N','C','E',' ',' ',' ',' ','R'};
display_line_t display_line_inverter_temperature={'M','A','X',' ','I','N','V','E','R','T','E','R','T','E','M','P',' ','A','V','E'};


/* Players */

display_line_t display_line_player_select={' ','S','E','L','E','C','T',' ','Y','O','U','R',' ','P','L','A','Y','E','R',' '};
display_line_t display_line_player_yoshi={' ',' ',' ',' ','>','Y','O','S','H','I',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_player_mario={' ',' ',' ',' ','>','M','A','R','I','O',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_player_luigi={' ',' ',' ',' ','>','L','U','I','G','I',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_player_bowser={' ',' ',' ',' ','>','B','O','W','S','E','R',' ',' ',' ',' ',' ',' ',' ',' ',' '};
display_line_t display_line_player_donkey_kong={' ',' ',' ',' ','>','D','O','N','K','E','Y','-','K','O','N','G',' ',' ',' ',' '};
display_line_t display_line_player_princess_peach={' ',' ',' ',' ','>','P','R','I','N','C','E','S','S',' ','P','E','A','C','H',' '};
	
	

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

/* for toggling dot in Overview */
uint8_t toggle_dot=0;


/* Address Counter (AC) 
*	 with DDRAM: 
*	 overflows from 0x40 to 0x27 and 0x00 to 0x67 
* 	 with CGRAM:
* 	 overflows from 0x3F to 0x00
*/

uint8_t address_counter; 



void display_write_data(uint8_t data){
	SPI_START_PORT&=~(1<<SPI_START_PIN);
	spi_putchar(START_BITS_WRITE_DATA);
	spi_putchar(data);
	SPI_START_PORT|=(1<<SPI_START_PIN);
}

void display_write_instruction(uint8_t inst){
	SPI_START_PORT&=~(1<<SPI_START_PIN);
	spi_putchar(START_BITS_WRITE_INSTRUCTION);
	spi_putchar(inst);
	SPI_START_PORT|=(1<<SPI_START_PIN);
}

void display_write_display_lines(display_line_t s1,display_line_t s2){
	int i;
	display_write_instruction(INSTRUCTION_CURSOR_HOME);	// cursor to pos 1
	for(i=0;i<20;i++){
		display_write_data(s1[i]);
	}
	
	for(i=0;i<20;i++){
		display_write_instruction(INSTRUCTION_CURSOR_RIGHT_SHIFT);	// cursor to second line
	};
			
	for(i=0;i<20;i++){
		display_write_data(s2[i]);
	}	
}

void display_write_top_line(display_line_t s1){
	int i;
	display_write_instruction(INSTRUCTION_CURSOR_HOME);	// cursor to pos 1
	for(i=0;i<20;i++){
		display_write_data(s1[i]);
	}
	
}

void display_write_bottom_line(display_line_t s1){
	int i;
	display_write_instruction(INSTRUCTION_CURSOR_HOME);	// cursor to pos 1
	
	for(i=0;i<40;i++){
		display_write_instruction(INSTRUCTION_CURSOR_RIGHT_SHIFT);	// cursor to second line
	};
	
	for(i=0;i<20;i++){
		display_write_data(s1[i]);
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
	SPI_START_DDR|=(1<<SPI_START_PIN);
	SPI_START_PORT|=(1<<SPI_START_PIN);
	
	/* turn display on */
	display_write_instruction(INSTRUCTION_DISPLAY_ON);
	
	/* set brigthness to max*/
	display_write_instruction(INSTRUCTION_BRIGHTNESS_100);

	/* set menu to home */
	display_update(DISPLAY_MENU_HOME,0,0,0,0,0,0);
	
	/* init last menu before error to none */
	selected_menu_pre_error=255;	
}

void display_update(uint8_t request_id, uint8_t value1,uint8_t value2,uint8_t value3, uint8_t value4, uint8_t value5,uint8_t error){
	char * dpl=display_line_blank;
	
	switch(request_id){
		case DISPLAY_MENU_HOME:
				display_make_display_line_blank(dpl);
				display_write_display_lines(display_line_home,dpl);
			break;
		case DISPLAY_MENU_ERROR:
				display_make_display_line_error_or_message(dpl,error);
				if(error>=100){// is message
					display_write_display_lines(display_line_message,dpl);
				}else{ //is error
					display_write_display_lines(display_line_error,dpl);
				}				
			break;
		case DISPLAY_MENU_ACCLERATION_MODE:
				switch(value1){
					case 1: // normal drive
							display_write_display_lines(display_line_accleration_mode,display_line_accleration_mode_normal);
						break;
					case 2: // Ready, both buttons pressed, show break percent
							display_make_display_line_percent_bar(dpl,value2);
							display_write_display_lines(display_line_accleration_mode_ready,dpl);
						break;
					case 3: // acceleration GO GO GO
							display_make_display_line_blank(dpl);
							display_write_display_lines(display_line_accleration_mode_go_go,dpl);
						break;
					default:
						break;					
				}
				
			break;
		case DISPLAY_MENU_SOC:
				if(value1==1){
						display_make_soc_line1(dpl,value2,value3,value4,toggle_dot);
						display_write_top_line(dpl);
						toggle_dot=0;
				}else if(value1==2){
						display_make_soc_line2(dpl,value2,value3,value4);
						display_write_bottom_line(dpl);
						toggle_dot=1;
				}

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
				display_make_display_line_motor_temp(dpl,value1,value2);
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
		case DISPLAY_MENU_BUTTON_TEST:
				display_make_display_line_button_test(dpl,value1);
				display_write_display_lines(display_line_buttons_pressed,dpl);
			break;
		case DISPLAY_MENU_TSAL:
				display_write_display_lines(display_line_tsal1,display_line_tsal2);
			break;
		case DISPLAY_MENU_SELECT_PLAYER:
				display_make_display_line_select_player(dpl,value1);
				display_write_display_lines(display_line_player_select,dpl);
			break;
		case DISPLAY_MENU_BRAKE_BALANCE:
				 display_make_display_line_brake_balance(dpl,value1);
				 display_write_display_lines(display_line_brake_balance,dpl);
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
	
	
	display_line_t dpl_volt={' ',GET_DEC_POS2_TEMP(min_i),GET_DEC_POS3_TEMP(min_i),'°','C',' ',' ',' ',GET_DEC_POS2_TEMP(av_i),GET_DEC_POS3_TEMP(av_i),'°','C',' ',' ',' ',' ',GET_DEC_POS2_TEMP(max_i),GET_DEC_POS3_TEMP(max_i),'°','C'};
	memcpy(dpl,dpl_volt,20);
}/* end display_make_display_line_min_av_max_temp*/



void display_make_display_line_lv_voltage(char *dpl,uint8_t value1){
	#define GET_DEC_POS1_LV_VOLT(x) (char)(0b00110000+(x/100))
	#define GET_DEC_POS2_LV_VOLT(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS3_LV_VOLT(x) (char)(0b00110000+((x)%10))
		
		
	display_line_t dpl_volt={' ',' ',' ',' ',' ',' ',' ',GET_DEC_POS1_LV_VOLT(value1),GET_DEC_POS2_LV_VOLT(value1),'.',GET_DEC_POS3_LV_VOLT(value1),'V',' ',' ',' ',' ',' ',' ',' ',' '};
	memcpy(dpl,dpl_volt,20);
	
} /*end display_make_display_line_lv_voltage */

void display_make_display_line_motor_temp(char *dpl,uint8_t value1,uint8_t value2){
	
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
		
			
	display_line_t dpl_volt={' ',pos_1a,pos_2a,GET_DEC_POS3_MOTOR_TEMP(value1),'°','C',' ',' ',' ',' ',' ',' ',' ',' ',pos_1b,pos_2b,GET_DEC_POS3_MOTOR_TEMP(value2),'°','C',' '};
	memcpy(dpl,dpl_volt,20);
	
} /*end display_make_display_line_motor_temp*/



void display_make_display_line_error_or_message(char * dpl,uint8_t code){
	
	uint8_t bpd;
	if((code>9)&&(code<20)){
		bpd=1;
		code=code-10;
	}else{
		bpd=0;
	}
	
	#define GET_DEC_POS3_ERROR(x) (char)(0b00110000+(x/100))
	#define GET_DEC_POS2_ERROR(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS1_ERROR(x) (char)(0b00110000+((x)%10))
		
	switch(code){
		case ERRROR_NONE:
			memcpy(dpl,display_line_error_none,20);
			break;
		case ERROR_SC_DOWN:
			memcpy(dpl,display_line_error_sc_down,20);
			break;
		case ERROR_PRE_ENRE:
			memcpy(dpl,display_line_error_pre_enre,20);
			break;
		case ERROR_PRE_BOTS:
			memcpy(dpl,display_line_error_pre_bots,20);
			break;
		case ERROR_BOTS:
			memcpy(dpl,display_line_error_bots,20);
			break;
		case ERROR_BMS_RELAY:
			memcpy(dpl,display_line_error_bms_relay,20);
			break;
		case ERROR_HVDI:
			memcpy(dpl,display_line_error_hvdi,20);
			break;
		case ERROR_IMD:
			memcpy(dpl,display_line_error_imd,20);
			break;
		case ERROR_IMDF:
			memcpy(dpl,display_line_error_imdf,20);
			break;
		case ERRROR_PBD:
			memcpy(dpl,display_line_error_bpd,20);
			break;		
		case ERROR_BMS_UNDERVOLTAGE:
			memcpy(dpl,display_line_error_bms_undervoltage,20);
			break;
		case ERROR_BMS_OVERCURRENT:
			memcpy(dpl,display_line_error_bms_overcurrent,20);
			break;
		case ERROR_BMS_OVERTEMP:
			memcpy(dpl,display_line_error_bms_overtemp,20);
			break;
		case ERROR_DISCHARGE_TEMP:
			memcpy(dpl,display_line_error_bms_dischargetemp,20);
			break;
		case ERROR_TOTAL_VOLTAGE_LOW:
			memcpy(dpl,display_line_error_total_voltage_low,20);
			break;
		case ERROR_SHUNT_VOLTAGE_LOW:
			memcpy(dpl,display_line_error_shunt_voltage_low,20);
			break;
		case ERROR_DC_LINK_VOLTAGE_LOW:
			memcpy(dpl,display_line_error_dc_link_voltage_low,20);
			break;
		case ERROR_THROTTLE_FAIL:
			memcpy(dpl,display_line_throttle_fail,20);
			break;
		case ERROR_BRAKE_FORCE_FAIL:
			memcpy(dpl,display_line_brake_force_fail,20);
			break;
		case ERROR_MISSING_MCM_REAR:
			memcpy(dpl,display_line_error_missing_mcm_rear,20);
			break;
		case ERROR_MISSING_MCM_FRONT:
			memcpy(dpl,display_line_error_missing_mcm_front,20);
			break;
		case ERROR_MISSING_MCM_LVB:
			memcpy(dpl,display_line_error_missing_mcm_lvb,20);
			break;
		case ERROR_MISSING_MCM_AB:
			memcpy(dpl,display_line_error_missing_mcm_ab,20);
			break;
		case ERROR_MISSING_MC_LEFT:
			memcpy(dpl,display_line_error_missing_mc_left,20);
			break;
		case ERROR_MISSING_MC_RIGHT:
			memcpy(dpl,display_line_error_missing_mc_right,20);
			break;
		case ERROR_MISSING_SHUNT:
			memcpy(dpl,display_line_error_missing_shunt,20);
			break;
		case ERROR_AIRp_meltdown:
			memcpy(dpl,display_line_error_airp_melt_down,20);
			break;
		case ERROR_AIRn_meltdown:
			memcpy(dpl,display_line_error_airn_melt_down,20);
			break;
		case ERROR_AIRror:
			memcpy(dpl,display_line_error_air_ror,20);
			break;
		case MESSAGE_STARTING_TS:
			memcpy(dpl,display_line_message_starting_ts,20);
			break;
		case MESSAGE_CHECK_MS:
			memcpy(dpl,display_line_message_check_ms,20);
			break;
		case MESSAGE_PRECHARGING:
			memcpy(dpl,display_line_message_precharging,20);
			break;
		case MESSAGE_PRECHARGED:
			memcpy(dpl,display_line_message_precharged,20);
			break;
		case MESSAGE_STARTING_MOTOR_CONTROLLER:
			memcpy(dpl,display_line_message_starting_motor_controller,20);
			break;
		case MESSAGE_READY_2_DRIVE:
			memcpy(dpl,display_line_message_ready_2_drive,20);
			break;
		case MESSAGE_MANUAL_MC:
			memcpy(dpl,display_line_message_manual_mc,20);
			break;
		case MESSAGE_PRECHARGE_ONLY:
			memcpy(dpl,display_line_message_precharge_only,20);
			break;
		case MESSAGE_ENRE_FAIL:
			memcpy(dpl,display_line_message_enre_fail,20);
			break;
		case MESSAGE_MS_OPEN:
			memcpy(dpl,display_line_message_ms_open,20);
			break;
		case MESSAGE_PRECHARGE_FAIL:
			memcpy(dpl,display_line_message_precharge_fail,20);
			break;
		case MESSAGE_MC_FAIL:
			memcpy(dpl,display_line_message_mc_fail,20);
			break;
		case MESSAGE_LV_LOW:
			memcpy(dpl,display_line_message_lv_low,20);
			break;
		case MESSAGE_LV_CRITICAL:
			memcpy(dpl,display_line_message_lv_critical,20);
			break;		
		case MESSAGE_BOOT_UP:
			memcpy(dpl,display_line_message_boot_up,20);
			break;
		default:
			memcpy(dpl,display_line_error_unknown_code,20);
		break;
	}
	
	if(bpd){
		dpl[19]='P';
		dpl[19]='+';		
	}
	
	if((code>23)&&(code<30)){ // General BMS ERROR
			memcpy(dpl,display_line_error_bms,20);
	}
	
	/* switch case for categories */
	switch((code/10)*10){
		case ERROR_MC:
			memcpy(dpl,display_line_error_mc,20);
			break;
		case ERROR_MCM_A:
			memcpy(dpl,display_line_error_mcm,20);
			break;
		case ERROR_MCM_B:
			memcpy(dpl,display_line_error_mcm,20);
			break;
		default:
			break;
	}	
	
	
	dpl[1]=GET_DEC_POS3_ERROR(code);
	if(bpd){
		dpl[2]='1';
	}else{
		dpl[2]=GET_DEC_POS2_ERROR(code);
	}	
	dpl[3]=GET_DEC_POS1_ERROR(code);
	
} /*end display_make_display_error*/

void display_make_display_line_button_test(char* dpl,uint8_t b1,uint8_t b2){
	

	dpl[b1]=(char) (char)(0b00110000+b2);

	
}	

void display_make_display_line_blank(char *dpl){
	display_line_t blank={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	memcpy(dpl,blank,20);
}

void display_up( void )
{
	if((selected_menu==DISPLAY_MENU_ERROR)&&(selected_menu_pre_error!=255)){
		selected_menu=selected_menu_pre_error;
		selected_menu_pre_error=255;
	}else{
		selected_menu++;
	}		
	selected_menu%=(DISPLAY_MENU_NUMBER);
	if(selected_menu==0) selected_menu=1;
	
	return;
}

void display_down( void )
{
	if((selected_menu==1)||(selected_menu==0)){
		selected_menu=(DISPLAY_MENU_NUMBER-1);
		return;
	}
	
	if((selected_menu==DISPLAY_MENU_ERROR)&&(selected_menu_pre_error!=255)){
		selected_menu=selected_menu_pre_error;
		selected_menu_pre_error=255;
	}else{
		selected_menu--;	
	}	
	return;

}

void display_starting(uint8_t percent){
	char * dpl=display_line_blank;
	
	display_make_display_line_percent(dpl,percent);
	display_write_display_lines(display_line_starting,dpl);
	
}

void display_make_display_line_select_player(char *dpl,uint8_t value1){
	
	#define DISPLAY_PLAYER_MARIO (0)
	#define DISPLAY_PLAYER_LUIGI (1)
	#define DISPLAY_PLAYER_YOSHI (2)
	#define DISPLAY_PLAYER_DKONG (3)
	#define DISPLAY_PLAYER_PPEACH (4)
	#define DISPLAY_PLAYER_BOWSER (5)
	
	switch(value1){
		case DISPLAY_PLAYER_MARIO:
			memcpy(dpl,display_line_player_mario,20);
			break;
		case DISPLAY_PLAYER_LUIGI:
			memcpy(dpl,display_line_player_luigi,20);
			break;
		case DISPLAY_PLAYER_YOSHI:
			memcpy(dpl,display_line_player_yoshi,20);
			break;
		case DISPLAY_PLAYER_DKONG:
			memcpy(dpl,display_line_player_donkey_kong,20);
			break;
		case DISPLAY_PLAYER_PPEACH:
			memcpy(dpl,display_line_player_princess_peach,20);
			break;
		case DISPLAY_PLAYER_BOWSER:
			memcpy(dpl,display_line_player_bowser,20);
			break;
		default:
			break;
	}
}


void display_make_display_line_brake_balance(char *dpl,uint8_t percent){
	if(percent>100) return; //illegal
	
	uint8_t compliment_percent=100-percent;	
	
	
	#define GET_DEC_POS2_BRAKE_BALANCE(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS1_BRAKE_BALANCE(x) (char)(0b00110000+(x%10))
	
	display_line_t template={' ','a','b','%',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','c','d','%',' '};
	
	
	template[1]=GET_DEC_POS2_BRAKE_BALANCE(percent);
	template[2]=GET_DEC_POS1_BRAKE_BALANCE(percent);
	template[16]=GET_DEC_POS2_BRAKE_BALANCE(compliment_percent);
	template[17]=GET_DEC_POS1_BRAKE_BALANCE(compliment_percent);
	
	memcpy(dpl,template,20);
	
}

void display_make_display_line_inverter_temp(dpl,value1,value2){
	
	#define GET_DEC_POS1_INVERTER_TEMP(x) (char)(0b00110000+(x/100))
	#define GET_DEC_POS2_INVERTER_TEMP(x) (char)(0b00110000+((x/10)%10))
	#define GET_DEC_POS3_INVERTER_TEMP(x) (char)(0b00110000+((x)%10))
	
	char pos_1a=GET_DEC_POS1_INVERTER_TEMP(value1);
	char pos_2a=GET_DEC_POS2_INVERTER_TEMP(value1);
	char pos_1b=GET_DEC_POS1_INVERTER_TEMP(value2);
	char pos_2b=GET_DEC_POS2_INVERTER_TEMP(value2);
	
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
	
	
display_line_t dpl_volt={' ',pos_1a,pos_2a,GET_DEC_POS3_INVERTER_TEMP(value1),'°','C',' ',' ',' ',' ',' ',' ',' ',' ',pos_1b,pos_1b,GET_DEC_POS3_INVERTER_TEMP(value2),'°','C',' '};
memcpy(dpl,dpl_volt,20);

} /*end display_make_display_line_inverter_temp*/

void display_make_soc_line1(char* dpl,uint8_t value2,uint8_t value3,uint8_t value4,uint8_t toggle_dot){

	
	/* make SOC */
	uint8_t soc_1=GET_DEC_POS1_PERCENT(value2);
	uint8_t soc_2=GET_DEC_POS2_PERCENT(value2);
	uint8_t soc_3=GET_DEC_POS3_PERCENT(value2);
	
	if(soc_1=='0'){
		soc_1=' ';
		if(soc_2=='0'){
			soc_2=' ';
		}
	}
	
	/* volt average */
	uint8_t volt_av_1=GET_DEC_POS1_VOLT(value3);
	uint8_t volt_av_2=GET_DEC_POS2_VOLT(value3);
	uint8_t volt_av_3=GET_DEC_POS3_VOLT(value3);

	
	/* volt min */
	
	uint8_t volt_min_1=GET_DEC_POS1_VOLT(value4);
	uint8_t volt_min_2=GET_DEC_POS2_VOLT(value4);
	uint8_t volt_min_3=GET_DEC_POS3_VOLT(value4);

	display_line_t dpl_soc1={'V',volt_av_1,'.',volt_av_2,volt_av_3,'/',volt_min_1,'.',volt_min_2,volt_min_3,' ','S','O','C',':',soc_1,soc_2,soc_3,'%'};
	
	if(toggle_dot==1){
		dpl_soc1[14]=' ';
	}
	memcpy(dpl,dpl_soc1,20);
}


void display_make_soc_line2(char* dpl,uint8_t value2,uint8_t value3,uint8_t value4){
		
		
		/* make akku temp */
		uint8_t akku_1=GET_DEC_POS1_MOTOR_TEMP(value2);
		uint8_t akku_2=GET_DEC_POS2_MOTOR_TEMP(value2);
		uint8_t akku_3=GET_DEC_POS3_MOTOR_TEMP(value2);
		
		if(akku_1=='0'){
			akku_1=' ';
			if(akku_2=='0'){
				akku_2=' ';
			}
		}
		
		/* make motor temp */		uint8_t motor_1=GET_DEC_POS1_MOTOR_TEMP(value3);
		uint8_t motor_2=GET_DEC_POS2_MOTOR_TEMP(value3);
		uint8_t motor_3=GET_DEC_POS3_MOTOR_TEMP(value3);
		
		if(motor_1=='0'){
			motor_1=' ';
			if(motor_2=='0'){
				motor_2=' ';
			}
		}
		
		/* make inverter temp */
		uint8_t inverter_1=GET_DEC_POS1_MOTOR_TEMP(value4);
		uint8_t inverter_2=GET_DEC_POS2_MOTOR_TEMP(value4);
		uint8_t inverter_3=GET_DEC_POS3_MOTOR_TEMP(value4);
			
		if(inverter_1=='0'){
			inverter_1=' ';
			if(inverter_2=='0'){
				inverter_2=' ';
			}
		}
	
		display_line_t dpl_soc2={'A',':',akku_1,akku_2,akku_3,' ',' ','M',':',motor_1,motor_2,motor_3,' ',' ','I',':',inverter_1,inverter_2,inverter_3,' '};
			
		memcpy(dpl,dpl_soc2,20);
}
