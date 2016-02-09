#include <asf.h>
#include "compiler.h"
#include "pio.h"
#include <string.h>
#include <init.h>
#include <Transmitter.h>

/* Use TC Peripheral 0. */
#define TC             TC0
#define TC_PERIPHERAL  0

/* Configure TC0 channel 2 as capture input. */
#define TC_CHANNEL_CAPTURE 0
#define ID_TC_CAPTURE ID_TC0
//#define PIN_TC_CAPTURE PIN_TC0_TIOA2
//#define PIN_TC_CAPTURE_MUX PIN_TC0_TIOA2_MUX

/* Use TC2_Handler for TC capture interrupt. */
#define TC_Handler  TC0_Handler
#define TC_IRQn     TC0_IRQn

#define TC_CAPTURE_TIMER_SELECTION TC_CMR_TCCLKS_TIMER_CLOCK3


static void tc_capture_initialize(void);
void TC_Handler(void);


int main (void)
{
	sysclk_init();
	
	ioport_init();
	
	board_init();
	
	ioport_set_pin_dir(MY_LED,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,1);
	
	tc_capture_initialize();

	while (1)
	{
		delay_ms(100);
	}
}



static void tc_capture_initialize(void)
{
	/* Configure the PMC to enable the TC module */
	sysclk_enable_peripheral_clock(ID_TC_CAPTURE);
	#if SAMG55
	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_3);
	pmc_switch_pck_to_mck(PMC_PCK_3, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_3);
	#endif
	/* Init TC to capture mode. */
	tc_init(TC, TC_CHANNEL_CAPTURE,
	TC_CAPTURE_TIMER_SELECTION /* Clock Selection */
	| TC_CMR_LDRA_NONE /* RA Loading: rising edge of TIOA */
	| TC_CMR_LDRB_NONE /* RB Loading: falling edge of TIOA */
	| TC_CMR_CPCTRG /* External Trigger: TIOA */
	| TC_CMR_ETRGEDG_NONE /* External Trigger Edge: Falling edge */
	);
	
    
	
	NVIC_DisableIRQ(TC_IRQn);
	NVIC_ClearPendingIRQ(TC_IRQn);
	NVIC_SetPriority(TC_IRQn, 0);
	NVIC_EnableIRQ(TC_IRQn);
	
	tc_enable_interrupt(TC, TC_CHANNEL_CAPTURE, TC_IER_LDRBS);

}


void TC_Handler(void)
{
	uint32_t b;
	b = tc_read_rb(TC, TC_CHANNEL_CAPTURE);
	
	b = tc_read_ra(TC, TC_CHANNEL_CAPTURE);
	
	ioport_toggle_pin_level(MY_LED);
}