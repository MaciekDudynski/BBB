#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define DELAY_CYCLES	2250	// 200MHz / 100kHz = 2000

#define SHARED_MEM	0x00010000

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main()
{
	volatile uint8_t * clock_flag = (volatile uint8_t *)SHARED_MEM;

	// Set the CFG Register to direct output instead of serial output
	CT_CFG.GPCFG0 = 0;

	while( 1 )
	{
		__delay_cycles( DELAY_CYCLES );

		// __R30 ^= (1 << 14); // P8.12
		// break when nothing is using clock
		if( *clock_flag > 0 )
			break;
		*clock_flag = 1;
	}
}
