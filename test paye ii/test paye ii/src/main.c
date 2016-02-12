#include <asf.h>
#include "compiler.h"
#include "pio.h"
#include <string.h>
#include <init.h>
#include <Transmitter.h>

void USART_SERIAL_ISR_HANDLER(void);

void usb_init(void);

static bool my_flag_autorize_cdc_transfert = false;
bool my_callback_cdc_enable(void)
{
	my_flag_autorize_cdc_transfert = true;
	return true;
}
void my_callback_cdc_disable(void)
{
	my_flag_autorize_cdc_transfert = false;
}
void task(void)
{
	if (my_flag_autorize_cdc_transfert) {
		udi_cdc_putc('A');
	//	udi_cdc_getc();
	}
}

 UDI_CDC_RX_NOTIFY(port)
{
	int ch=udi_cdc_getc();

	udi_cdc_putc(ch);

	ioport_toggle_pin_level(MY_LED);
}


char a;



/////    help for start an interrupt in init.c

int main (void)
{
	sysclk_init();
	
	ioport_init();
	
	board_init();
	
	ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,0);
	
	PCK_Num[0]=0;
	PCK_Num[1]=0;
	
	Enable_global_interrupt();
	
	init_Usart();
	
	USART_send("salam\r",6);	
	
	irq_initialize_vectors();
	
	delay_ms(1000);
	
	usb_init();
	
	
	while (1)
	{
//		if (my_flag_autorize_cdc_transfert) 
//		{
// 			int i=udi_cdc_putc('A');
// 			//	udi_cdc_getc();
// 			if (i==1)
// 			{
// 				ioport_toggle_pin_level(MY_LED);
// 			}
//		}
			delay_ms(2000);
			udi_cdc_putc('R');
		
// 		int ch=udi_cdc_getc();
// 		
// 		usart_putchar(USART_SERIAL,ch);
// 		
// 		ioport_toggle_pin_level(MY_LED);
		
		

	}
}


void usb_init(void)
{
	udc_start();
}


void USART_SERIAL_ISR_HANDLER(void)
{
	

	usart_getchar(USART_SERIAL,&a);
	ioport_toggle_pin_level(MY_LED);
	usart_putchar(USART_SERIAL,a);


}
