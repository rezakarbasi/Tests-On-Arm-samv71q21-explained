/*
 * init.c
 *
 * Created: 2/6/2016 3:18:47 PM
 *  Author: Reza_pc
 */ 


#include <init.h>



void init_Usart_receive_packet (void)
{
	ioport_set_pin_dir(PIO_PA21_IDX,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(PIO_PB4_IDX,IOPORT_DIR_OUTPUT);
	
	
	const sam_usart_opt_t usart_console_settings = {
		USART1_SERIAL_BAUDRATE,
		USART1_SERIAL_CHAR_LENGTH,
		USART1_SERIAL_PARITY,
		USART1_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL
	};
	#if SAM4L
	sysclk_enable_peripheral_clock(USART1_SERIAL);
	#else
	sysclk_enable_peripheral_clock(USART1_SERIAL_ID);
	#endif
	usart_init_rs232(USART1_SERIAL, &usart_console_settings,
	sysclk_get_main_hz()/2);
	usart_enable_tx(USART1_SERIAL);
	usart_enable_rx(USART1_SERIAL);
	// how to enable an interrupt( use three steps ):use these functions: -usart_enable_interrupt-    Then  -NVIC_EnableIRQ(USART_SERIAL_IRQ);-    & Then add this function  void USART_SERIAL_ISR_HANDLER(void)
 	usart_enable_interrupt(USART1_SERIAL, US_IER_RXRDY);
	NVIC_EnableIRQ(USART1_SERIAL_IRQ);
}


void init_Usart_transmit_data (void)
{
	ioport_set_pin_dir(PIO_PD15_IDX,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(PIO_PD16_IDX,IOPORT_DIR_OUTPUT);
	
	
	const sam_usart_opt_t usart_console_settings = {
		USART2_SERIAL_BAUDRATE,
		USART2_SERIAL_CHAR_LENGTH,
		USART2_SERIAL_PARITY,
		USART2_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL
	};
	#if SAM4L
	sysclk_enable_peripheral_clock(USART1_SERIAL);
	#else
	sysclk_enable_peripheral_clock(USART1_SERIAL_ID);
	#endif
	usart_init_rs232(USART2_SERIAL, &usart_console_settings,
	sysclk_get_main_hz()/2);
	usart_enable_tx(USART2_SERIAL);
	usart_enable_rx(USART2_SERIAL);
	// how to enable an interrupt( use three steps ):use these functions: -usart_enable_interrupt-    Then  -NVIC_EnableIRQ(USART_SERIAL_IRQ);-    & Then add this function  void USART_SERIAL_ISR_HANDLER(void)
	usart_enable_interrupt(USART2_SERIAL, US_IER_RXRDY);
	NVIC_EnableIRQ(USART2_SERIAL_IRQ);
}


void USART_send(char* in, char number)
{
	for (char c=0;c<number;c++)
	{
		usart_putchar(USART2_SERIAL,*(in+c));
	}
}


int make_two_byte(char msB,char lsb)
{
	int a=msB*256+lsb;
	return a;
}