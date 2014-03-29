/*
 * Button.h
 *
 * Created: 06.03.2014 09:56:42
 * Author: michael
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


uint16_t button_pressed_previous;
uint16_t button_pressed_current;



/* Buttons on Steering Wheel */

#define BUTTON_ID_FLAPPY_DRS (0)
#define BUTTON_ID_FLAPPY_RADIO (1)
#define BUTTON_ID_PLUS (4)
#define BUTTON_ID_MINUS (5)
#define BUTTON_ID_UP (8)
#define BUTTON_ID_DOWN (9)

/* Buttons on Dashboard */
#define BUTTON_ID_TMS (2)
#define BUTTON_ID_RECUP (3)
#define BUTTON_ID_TC (6)
#define BUTTON_ID_KOBI (7)
#define BUTTON_ID_TV (10)
#define BUTTON_ID_AD (11)

/*
	  col1¦col2 ¦col3 ¦
row1---0--¦--1--¦--2--¦
row2---3--¦--4--¦--5--¦
row3---6--¦--7--¦--8--¦
row4---9--¦-10--¦-11--¦

*/


#define BUTTON_PIN_NUMBER (7)
#define BUTTON_ROW_NUMBER (4)


	
#define ROW_1_PIN (4);
#define ROW_2_PIN (5);
#define ROW_3_PIN (6);
#define ROW_4_PIN (3);
#define COLOUMN_1_PIN (6);
#define COLOUMN_2_PIN (7);
#define COLOUMN_3_PIN (4);







void button_init(void);
void button_multiplex_cycle(void);
void button_row_col(void);




#endif /* BUTTON_H_ */