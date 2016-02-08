/*
 * init.c
 *
 * Created: 2/6/2016 3:18:47 PM
 *  Author: Reza_pc
 */ 


#include <init.h>



void init_Usart (void)
{
	ioport_set_pin_dir(PIO_PA21_IDX,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(PIO_PB4_IDX,IOPORT_DIR_OUTPUT);
	
	cpu_irq_enable();
	
	const sam_usart_opt_t usart_console_settings = {
		USART_SERIAL_BAUDRATE,
		USART_SERIAL_CHAR_LENGTH,
		USART_SERIAL_PARITY,
		USART_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL
	};
	
	#if SAM4L
	sysclk_enable_peripheral_clock(USART_SERIAL);
	#else
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	#endif
	
	usart_init_rs232(USART_SERIAL, &usart_console_settings,
	sysclk_get_main_hz()/2);
	usart_enable_tx(USART_SERIAL);
	usart_enable_rx(USART_SERIAL);
}


void USART_send(char* in, char number)
{
	for (char c=0;c<number;c++)
	{
		usart_putchar(USART_SERIAL,*(in+c));
	}
}


int make_two_byte(char msB,char lsb)
{
	int a=msB*256+lsb;
	return a;
}