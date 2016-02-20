#include <asf.h>
#include "compiler.h"
#include "pio.h"
#include <string.h>
#include <init.h>
#include <Transmitter.h>

void USART_SERIAL_ISR_HANDLER(void);

char a;


/////    help for start an interrupt in init.c

int main (void)
{
	sysclk_init();
	
	ioport_init();
	
	board_init();
	
	init_Usart();
	
	ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,0);
	
	
	PCK_Num[0]=0;
	PCK_Num[1]=0;
	
	USART_send("salam\r",6);	
	
	while (1)
	{
		
			delay_ms(10);

	}
}





void USART_SERIAL_ISR_HANDLER(void)
{
	

	usart_getchar(USART_SERIAL,&a);
	ioport_toggle_pin_level(MY_LED);
	usart_putchar(USART_SERIAL,a);


}
