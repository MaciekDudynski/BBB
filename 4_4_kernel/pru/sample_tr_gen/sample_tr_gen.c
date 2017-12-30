#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define DELAY_CYCLES	2495	// 200MHz / 100kHz = 2000

#define SHARED_MEM	0x00010000

register uint32_t volatile __R30;
register uint32_t volatile __R31;

void main()
{
	uint8_t volatile * sample_flag = (uint8_t volatile *)SHARED_MEM;

	// Set the CFG Register to direct output instead of serial output
	CT_CFG.GPCFG0 = 0;

	while( 1 )
	{
		__delay_cycles( DELAY_CYCLES );

		// __R30 ^= (1 << 14); // P8.12
		// break when nothing is using clock
		// if( *sample_flag > 0 )
		//	break;
		*sample_flag = 1;
	}
}
