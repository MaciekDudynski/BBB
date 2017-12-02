#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define RESOLUTION	12
#define DELAY_CYCLES	50 	// 200MHz / 2MHz / 2 = 50

#define CLK		6	// P8_39 pruout blue
#define ADC_MISO	4	// P8_41 pruin green
#define ADC_MOSI	2	// P8_43 pruout yellow
#define ADC_CS		0	// P8_45 pruout purple
#define DAC_MOSI	3	// p8_44 pruout yellow
#define DAC_CS		1	// P8_46 pruout purple

register uint32_t volatile __R30;
register uint32_t volatile __R31;

void main()
{
	uint8_t bit = 0x00;
	uint16_t buf = 0x0000;

	// Set the CFG Register to direct output instead of serial output
	CT_CFG.GPCFG0 = 0;

	// Clear the registers
	__R30 = 0x0000;
	__R31 = 0x0000;

	__R30 ^= (1 << ADC_CS);
	__R30 ^= (1 << DAC_CS);

	while( 1 )
	{
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 &= ~(1 << ADC_CS);

		__R30 |= (1 << ADC_MOSI);	// 1 - ADC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 |= (1 << ADC_MOSI);	// 1 - ADC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 &= ~(1 << ADC_MOSI);	// 0 - ADC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 &= ~(1 << DAC_CS);

		__R30 &= ~(1 << ADC_MOSI);	// 0 - ADC
		__R30 &= ~(1 << DAC_MOSI);	// 0 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 &= ~(1 << ADC_MOSI);	// 0 - ADC
		__R30 &= ~(1 << DAC_MOSI);	// 0 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		// wait - ADC
		__R30 |= (1 << DAC_MOSI);	// 1 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		// null bit - ADC
		__R30 |= (1 << DAC_MOSI);	// 1 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		for( bit = 0; bit < RESOLUTION; ++bit )
		{
			/* write DAC */

			if( buf & (1 << (RESOLUTION - 1)) )
				__R30 |= (1 << DAC_MOSI);
			else
				__R30 &= ~(1 << DAC_MOSI);

			buf = buf << 1;

			__R30 &= ~(1 << CLK);
			__delay_cycles( DELAY_CYCLES );

			/* read ADC */

			if( __R31 & (1 << ADC_MISO) )
				buf |= 0x01;
			else
				buf &= ~(0x01);

			__R30 |= (1 << CLK);
			__delay_cycles( DELAY_CYCLES );
		}

		__R30 |= (1 << ADC_CS);
		__R30 |= (1 << DAC_CS);
	}
}
