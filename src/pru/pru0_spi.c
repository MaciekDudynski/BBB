/*
 *Written by Vaibhav Choudhary under GSOC-2016 for BeagleBoard.org
 *Copyright (C) 2016 Vaibhav Choudhary -www.vaibhavchoudhary.com
 *
 *PRU-SPI FIRMWARE
 *
 *This code may be copied and/or modified freely according to GNU General Public  
 *License version 2 as published by the Free Software Foundation, provided   
 *the following conditions are also met:
 *1) Redistributions/adaptions of source code must retain this copyright
 *   notice on the top, giving credit to the original author, along with 
 *   this list of conditions.
 *
 *2) Redistributions in binary form, compiled from this source code and/or 
 *   modified/adapted versions of this source code, must include this copyright 
 *   notice giving credit to the original author, along with this list of conditions 
 *   in the documentation and other materials provided with the
 *   distribution.
 *
 *3) The original author shall not held for any loss arising from using this code.
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE
 */

#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define MOSI	15	// P8_11
#define CLK	14	// P8_12
#define MISO	5	// P9_27
#define CS	2	// P9_30
#define DEB	0	// P9_31

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

	while( 1 )
	{
		__R30 &= ~(1 << CLK);

		__R30 &= ~(1 << CS);

		/* init ADC */

		__R30 ^= (1 << DEB);
		__R30 |= (1 << MOSI);
		__R30 ^= (1 << CLK);
		__R30 ^= (1 << CLK);
		__R30 |= (1 << MOSI);
		__R30 ^= (1 << CLK);
		__R30 ^= (1 << CLK);
		__R30 &= ~(1 << MOSI);
		__R30 ^= (1 << CLK);
		__R30 ^= (1 << CLK);
		__R30 &= ~(1 << MOSI);
		__R30 ^= (1 << CLK);
		__R30 ^= (1 << CLK);
		__R30 &= ~(1 << MOSI);
		__R30 ^= (1 << CLK);
		__R30 ^= (1 << CLK);

		__R30 ^= (1 << DEB);
		__R30 ^= (1 << CLK);
		__R30 ^= (1 << CLK);

		/* read ADC */

		for( i = 0; i < 12; ++i )
		{
			buf = buf << 1;

			__R30 ^= (1 << CLK);

			if( __R31 & (1 << MISO) )
				buf |= 0x01;
			else
				buf &= ~(0x01);

			__R30 ^= (1 << CLK);
		}

		__R30 |= (1 << CS);	

		/* init DAC */



		/* write DAC */

		for( i = 0; i < 12; ++i )
		{
			if( buf & 0x0800 )
				__R30 |= (1 << MOSI);
			else
				__R30 &= ~(1 << MOSI);

			__R30 ^= (1 << CLK);
			__R30 ^= (1 << CLK);

			buf = buf << 1;
		}

	}
}
