#include <asf.h>
#include "compiler.h"
#include "pio.h"
#include <string.h>
#include <init.h>
#include <Transmitter.h>

void USART1_SERIAL_ISR_HANDLER(void);

char a;


/////    help for start an interrupt in init.c

int main (void)
{
	sysclk_init();
	
	ioport_init();
	
	board_init();
	PCK_Num[0]=0;
	PCK_Num[1]=0;
	completed_transfer=0;
	
	ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,1);
	
	init_Usart_receive_packet();

	init_Usart_transmit_data();
	
	USART_send("salam\r",6);	
		
	char buff[10];
	
	while (1)
	{
		
// 			delay_ms(10);
// 			if (completed_transfer==1)
// 			{
// 				int m=make_two_byte(Buf_Tx[0][0][5],Buf_Tx[0][0][6]);
// 				completed_transfer=sprintf(buff,"%d\r",m);
// 				USART_send(buff,completed_transfer);
// 				completed_transfer=0;
// 			}
		
		usart_putchar(USART2_SERIAL,'a');
		delay_ms(400);
		ioport_toggle_pin_level(MY_LED);
	}
}





void USART1_SERIAL_ISR_HANDLER(void)
{
	usart_getchar(USART1_SERIAL,&a);
	GetNewData(a,0);
}
