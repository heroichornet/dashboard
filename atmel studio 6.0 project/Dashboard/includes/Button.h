/*
 * Button.h
 *
 * Created: 06.03.2014 09:56:42
 * Author: michael
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

uint16_t button_pressed;
uint8_t button_current;

/* Buttons for VCU */
#define BUTTON_ID_START			(0)
#define BUTTON_ID_TV			(1)
#define BUTTON_ID_TC			(2)
#define BUTTON_ID_RECUP			(3)
#define BUTTON_ID_KOBI			(4)
#define BUTTON_ID_AD			(5)
#define BUTTON_ID_DRS			(6)

/* Buttons for Dashboard (local) */




/*
	  col1¦col2 ¦col3 ¦
row1---0--¦--1--¦--2--¦
row2---3--¦--4--¦--5--¦
row3---6--¦--7--¦--8--¦
row4---9--¦-10--¦-11--¦

*/


#define ROW_1_ID 0
#define ROW_2_ID 1
#define ROW_3_ID 2
#define ROW_4_ID 3
#define COLOUMN_1_ID 4
#define COLOUMN_2_ID 5
#define COLOUMN_3_ID 6

#define ROW_PIN(ROW_1_ID) 0x00

#define ROW_PORT(ROW_1_ID) 0x00

#define ROW_DD(port) 


void button_init(void);
void button_next_multiplex_step(void);




#endif /* BUTTON_H_ */