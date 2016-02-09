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

	while (1)
	{
	}
}