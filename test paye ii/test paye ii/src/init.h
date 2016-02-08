/*
 * init.h
 *
 * Created: 2/6/2016 3:19:24 PM
 *  Author: Reza_pc
 */ 


#ifndef INIT_H_
#define INIT_H_

#include <asf.h>
#include "pio.h"
#include <string.h>
#include <stdio.h>



#define MY_LED    IOPORT_CREATE_PIN(PIOA, 23)
#define button    PIO_PA9_IDX



#define USART_SERIAL                 USART1
#define USART_SERIAL_ID              ID_USART1
#define USART_SERIAL_ISR_HANDLER     USART1_Handler
#define USART_SERIAL_BAUDRATE        9600
#define USART_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY          US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT

#define USART_SERIAL_IRQ		USART1_IRQn



void init_Usart (void);
void USART_send(char* in, char number);
int make_two_byte(char msB,char lsb);





#endif /* INIT_H_ */


