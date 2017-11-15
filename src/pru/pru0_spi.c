#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define DELAY_TIME	200000000 	// 5 is OK

#define CLK		6	// P8_39 pruout blue
#define ADC_MISO	4	// P8_41 pruin green
#define ADC_MOSI	2	// P8_43 pruout yellow
#define ADC_CS		0	// P8_45 pruout purple
#define DAC_MOSI	3	// p8_44 pruout yellow
#define DAC_CS		1	// P8_46 pruout purple

volatile register uint32_t __R30;
volatile register uint32_t __R31;

uint8_t i = 0;

void main()
{
	volatile uint16_t buf = 0x0000;

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

		__R30 &= ~(1 << ADC_CS);

		/* init ADC */

		__R30 |= (1 << ADC_MOSI);	// 1
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 |= (1 << ADC_MOSI);	// 1
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << ADC_MOSI);	// 0
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << ADC_MOSI);	// 0
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << ADC_MOSI);	// 0
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 ^= (1 << CLK);		// wait
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);	
		__delay_cycles( DELAY_TIME );

		/* read ADC */

		for( i = 0; i < 12; ++i )
		{
			buf = buf << 1;

			__R30 ^= (1 << CLK);
			__delay_cycles( DELAY_TIME );

			if( __R31 & (1 << ADC_MISO) )
				buf |= 0x01;
			else
				buf &= ~(0x01);
		
			__R30 ^= (1 << CLK);
			__delay_cycles( DELAY_TIME );
		}

		__R30 |= (1 << ADC_CS);

		__R30 &= ~(1 << DAC_CS);

		/* init DAC */

		__R30 &= ~(1 << DAC_MOSI);	// 0 
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << DAC_MOSI);	// 0
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 &= ~(1 << DAC_MOSI);	// 1
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		__R30 |= (1 << DAC_MOSI);	// 1
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );
		__R30 ^= (1 << CLK);
		__delay_cycles( DELAY_TIME );

		/* write DAC */

		for( i = 0; i < 12; ++i )
		{
			if( buf & 0x0800 )
				__R30 |= (1 << DAC_MOSI);
			else
				__R30 &= ~(1 << DAC_MOSI);

			__R30 ^= (1 << CLK);
			__delay_cycles( DELAY_TIME );
			__R30 ^= (1 << CLK);

			__delay_cycles( DELAY_TIME );

			buf = buf << 1;
		}

		__R30 |= (1 << DAC_CS);
		__R30 &= ~(1 << DAC_MOSI);
	}
}
