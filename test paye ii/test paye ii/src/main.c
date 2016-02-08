#include <asf.h>
#include "compiler.h"
#include "pio.h"
#include <string.h>
#include <init.h>
#include <Transmitter.h>


int main (void)
{
	sysclk_init();
	
	ioport_init();
	
	board_init();
	
	irq_initialize_vectors();
	
	ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,0);
	
	
	
	//init_Usart();
	
	PCK_Num[0]=0;
	PCK_Num[1]=0;
	
	USART_send("salam\r",6);	
	
	uint8_t ch=0;
	
	irq_register_handler(USART1_IRQn,3);
	
	while (1)
	{
		
			char a;
			usart_getchar(USART_SERIAL,&a);
			usart_putchar(USART_SERIAL,'a');
	}
}








// ISR (USART_ISR)
// {
// 	char a;
// 	usart_getchar(USART_SERIAL,&a);
// 	usart_putchar(USART_SERIAL,"a");
// }
