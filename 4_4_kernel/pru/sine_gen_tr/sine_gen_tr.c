#include "sine_wave_samples.h"

#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define DELAY_TIME	5	// 200MHz / 20MHz / 2 = 5

#define CLK		6	// P8_39 pruout blue
#define ADC_MISO	4	// P8_41 pruin green
#define ADC_MOSI	2	// P8_43 pruout yellow
#define ADC_CS		0	// P8_45 pruout purple
#define DAC_MOSI	3	// p8_44 pruout yellow
#define DAC_CS		1	// P8_46 pruout purple

#define SHARED_MEM      0x00010000

volatile register uint32_t __R30;
volatile register uint32_t __R31;

uint8_t bit = 0;

void main()
{
	volatile uint8_t * sample_flag = (volatile uint8_t *)SHARED_MEM;

	uint16_t counter = 0x0000;
	volatile uint16_t buf = 0x0000;

	// Set the CFG Register to direct output instead of serial output
	CT_CFG.GPCFG0 = 0;

	// Clear the registers
	__R30 = 0x0000;
	__R31 = 0x0000;

	__R30 &= ~(1 << CLK);
	__R30 ^= (1 << DAC_CS);

	while( 1 )
	{
		++counter;
		counter &= 0x03FF;
		buf = WAVE_SAMPLES[ counter ];

		while( *sample_flag == 0 );

		__R30 &= ~(1 << DAC_CS);

		__R30 &= ~(1 << DAC_MOSI);	// 0 - DAC
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << DAC_MOSI);	// 0 - DAC
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << DAC_MOSI);	// 1 - DAC
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 |= (1 << DAC_MOSI);	// 1 - DAC
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		for( bit = 0; bit < 12; ++bit )
		{
			/* write DAC */

			if( buf & 0x0800 )
				__R30 |= (1 << DAC_MOSI);
			else
				__R30 &= ~(1 << DAC_MOSI);

			buf = buf << 1;

			__R30 ^= (1 << CLK);
			__delay_cycles( DELAY_TIME );
			__R30 ^= (1 << CLK);
			__delay_cycles( DELAY_TIME );
		}

		__R30 |= (1 << DAC_CS);

		*sample_flag = 0;
	}
}
