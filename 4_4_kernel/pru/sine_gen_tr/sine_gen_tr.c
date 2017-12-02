#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define RESOLUTION	12
#define DELAY_CYCLES	5 	// 200MHz / 20MHz / 2 = 5

#define CLK		6	// P8_39 pruout blue
#define ADC_MISO	4	// P8_41 pruin green
#define ADC_MOSI	2	// P8_43 pruout yellow
#define ADC_CS		0	// P8_45 pruout purple
#define DAC_MOSI	3	// p8_44 pruout yellow
#define DAC_CS		1	// P8_46 pruout purple

#define SHARED_MEM	0x00010000

#define SAMPLES_COUNT	1024

const uint16_t WAVE_SAMPLES[ SAMPLES_COUNT ] 
= { 0x800, 0x80C, 0x819, 0x825, 0x832, 0x83E, 0x84B, 0x857, 0x864, 0x871, 0x87D, 0x88A, 0x896, 0x8A3, 0x8AF, 0x8BC, 0x8C8, 0x8D5, 0x8E1, 0x8EE, 0x8FA, 0x907, 0x913, 0x91F, 0x92C, 0x938, 0x945, 0x951, 0x95E, 0x96A, 0x976, 0x983, 0x98F, 0x99B, 0x9A8, 0x9B4, 0x9C0, 0x9CC, 0x9D9, 0x9E5, 0x9F1, 0x9FD, 0xA09, 0xA15, 0xA22, 0xA2E, 0xA3A, 0xA46, 0xA52, 0xA5E, 0xA6A, 0xA76, 0xA82, 0xA8E, 0xA9A, 0xAA5, 0xAB1, 0xABD, 0xAC9, 0xAD5, 0xAE0, 0xAEC, 0xAF8, 0xB03, 0xB0F, 0xB1B, 0xB26, 0xB32, 0xB3D, 0xB49, 0xB54, 0xB60, 0xB6B, 0xB76, 0xB82, 0xB8D, 0xB98, 0xBA3, 0xBAE, 0xBBA, 0xBC5, 0xBD0, 0xBDB, 0xBE6, 0xBF1, 0xBFC, 0xC06, 0xC11, 0xC1C, 0xC27, 0xC32, 0xC3C, 0xC47, 0xC52, 0xC5C, 0xC67, 0xC71, 0xC7B, 0xC86, 0xC90, 0xC9A, 0xCA5, 0xCAF, 0xCB9, 0xCC3, 0xCCD, 0xCD7, 0xCE1, 0xCEB, 0xCF5, 0xCFF, 0xD09, 0xD12, 0xD1C, 0xD26, 0xD2F, 0xD39, 0xD42, 0xD4C, 0xD55, 0xD5F, 0xD68, 0xD71, 0xD7A, 0xD83, 0xD8C, 0xD95, 0xD9E, 0xDA7, 0xDB0, 0xDB9, 0xDC2, 0xDCA, 0xDD3, 0xDDC, 0xDE4, 0xDED, 0xDF5, 0xDFD, 0xE06, 0xE0E, 0xE16, 0xE1E, 0xE26, 0xE2E, 0xE36, 0xE3E, 0xE46, 0xE4E, 0xE55, 0xE5D, 0xE65, 0xE6C, 0xE74, 0xE7B, 0xE82, 0xE8A, 0xE91, 0xE98, 0xE9F, 0xEA6, 0xEAD, 0xEB4, 0xEBB, 0xEC1, 0xEC8, 0xECF, 0xED5, 0xEDC, 0xEE2, 0xEE8, 0xEEF, 0xEF5, 0xEFB, 0xF01, 0xF07, 0xF0D, 0xF13, 0xF19, 0xF1F, 0xF24, 0xF2A, 0xF30, 0xF35, 0xF3A, 0xF40, 0xF45, 0xF4A, 0xF4F, 0xF54, 0xF59, 0xF5E, 0xF63, 0xF68, 0xF6D, 0xF71, 0xF76, 0xF7A, 0xF7F, 0xF83, 0xF87, 0xF8C, 0xF90, 0xF94, 0xF98, 0xF9C, 0xF9F, 0xFA3, 0xFA7, 0xFAA, 0xFAE, 0xFB1, 0xFB5, 0xFB8, 0xFBB, 0xFBF, 0xFC2, 0xFC5, 0xFC8, 0xFCA, 0xFCD, 0xFD0, 0xFD3, 0xFD5, 0xFD8, 0xFDA, 0xFDC, 0xFDF, 0xFE1, 0xFE3, 0xFE5, 0xFE7, 0xFE9, 0xFEB, 0xFEC, 0xFEE, 0xFF0, 0xFF1, 0xFF3, 0xFF4, 0xFF5, 0xFF6, 0xFF7, 0xFF8, 0xFF9, 0xFFA, 0xFFB, 0xFFC, 0xFFD, 0xFFD, 0xFFE, 0xFFE, 0xFFE, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFE, 0xFFE, 0xFFE, 0xFFD, 0xFFD, 0xFFC, 0xFFB, 0xFFA, 0xFF9, 0xFF8, 0xFF7, 0xFF6, 0xFF5, 0xFF4, 0xFF3, 0xFF1, 0xFF0, 0xFEE, 0xFEC, 0xFEB, 0xFE9, 0xFE7, 0xFE5, 0xFE3, 0xFE1, 0xFDF, 0xFDC, 0xFDA, 0xFD8, 0xFD5, 0xFD3, 0xFD0, 0xFCD, 0xFCA, 0xFC8, 0xFC5, 0xFC2, 0xFBF, 0xFBB, 0xFB8, 0xFB5, 0xFB1, 0xFAE, 0xFAA, 0xFA7, 0xFA3, 0xF9F, 0xF9C, 0xF98, 0xF94, 0xF90, 0xF8C, 0xF87, 0xF83, 0xF7F, 0xF7A, 0xF76, 0xF71, 0xF6D, 0xF68, 0xF63, 0xF5E, 0xF59, 0xF54, 0xF4F, 0xF4A, 0xF45, 0xF40, 0xF3A, 0xF35, 0xF30, 0xF2A, 0xF24, 0xF1F, 0xF19, 0xF13, 0xF0D, 0xF07, 0xF01, 0xEFB, 0xEF5, 0xEEF, 0xEE8, 0xEE2, 0xEDC, 0xED5, 0xECF, 0xEC8, 0xEC1, 0xEBB, 0xEB4, 0xEAD, 0xEA6, 0xE9F, 0xE98, 0xE91, 0xE8A, 0xE82, 0xE7B, 0xE74, 0xE6C, 0xE65, 0xE5D, 0xE55, 0xE4E, 0xE46, 0xE3E, 0xE36, 0xE2E, 0xE26, 0xE1E, 0xE16, 0xE0E, 0xE06, 0xDFD, 0xDF5, 0xDED, 0xDE4, 0xDDC, 0xDD3, 0xDCA, 0xDC2, 0xDB9, 0xDB0, 0xDA7, 0xD9E, 0xD95, 0xD8C, 0xD83, 0xD7A, 0xD71, 0xD68, 0xD5F, 0xD55, 0xD4C, 0xD42, 0xD39, 0xD2F, 0xD26, 0xD1C, 0xD12, 0xD09, 0xCFF, 0xCF5, 0xCEB, 0xCE1, 0xCD7, 0xCCD, 0xCC3, 0xCB9, 0xCAF, 0xCA5, 0xC9A, 0xC90, 0xC86, 0xC7B, 0xC71, 0xC67, 0xC5C, 0xC52, 0xC47, 0xC3C, 0xC32, 0xC27, 0xC1C, 0xC11, 0xC06, 0xBFC, 0xBF1, 0xBE6, 0xBDB, 0xBD0, 0xBC5, 0xBBA, 0xBAE, 0xBA3, 0xB98, 0xB8D, 0xB82, 0xB76, 0xB6B, 0xB60, 0xB54, 0xB49, 0xB3D, 0xB32, 0xB26, 0xB1B, 0xB0F, 0xB03, 0xAF8, 0xAEC, 0xAE0, 0xAD5, 0xAC9, 0xABD, 0xAB1, 0xAA5, 0xA9A, 0xA8E, 0xA82, 0xA76, 0xA6A, 0xA5E, 0xA52, 0xA46, 0xA3A, 0xA2E, 0xA22, 0xA15, 0xA09, 0x9FD, 0x9F1, 0x9E5, 0x9D9, 0x9CC, 0x9C0, 0x9B4, 0x9A8, 0x99B, 0x98F, 0x983, 0x976, 0x96A, 0x95E, 0x951, 0x945, 0x938, 0x92C, 0x91F, 0x913, 0x907, 0x8FA, 0x8EE, 0x8E1, 0x8D5, 0x8C8, 0x8BC, 0x8AF, 0x8A3, 0x896, 0x88A, 0x87D, 0x871, 0x864, 0x857, 0x84B, 0x83E, 0x832, 0x825, 0x819, 0x80C, 0x800, 0x7F3, 0x7E6, 0x7DA, 0x7CD, 0x7C1, 0x7B4, 0x7A8, 0x79B, 0x78E, 0x782, 0x775, 0x769, 0x75C, 0x750, 0x743, 0x737, 0x72A, 0x71E, 0x711, 0x705, 0x6F8, 0x6EC, 0x6E0, 0x6D3, 0x6C7, 0x6BA, 0x6AE, 0x6A1, 0x695, 0x689, 0x67C, 0x670, 0x664, 0x657, 0x64B, 0x63F, 0x633, 0x626, 0x61A, 0x60E, 0x602, 0x5F6, 0x5EA, 0x5DD, 0x5D1, 0x5C5, 0x5B9, 0x5AD, 0x5A1, 0x595, 0x589, 0x57D, 0x571, 0x565, 0x55A, 0x54E, 0x542, 0x536, 0x52A, 0x51F, 0x513, 0x507, 0x4FC, 0x4F0, 0x4E4, 0x4D9, 0x4CD, 0x4C2, 0x4B6, 0x4AB, 0x49F, 0x494, 0x489, 0x47D, 0x472, 0x467, 0x45C, 0x451, 0x445, 0x43A, 0x42F, 0x424, 0x419, 0x40E, 0x403, 0x3F9, 0x3EE, 0x3E3, 0x3D8, 0x3CD, 0x3C3, 0x3B8, 0x3AD, 0x3A3, 0x398, 0x38E, 0x384, 0x379, 0x36F, 0x365, 0x35A, 0x350, 0x346, 0x33C, 0x332, 0x328, 0x31E, 0x314, 0x30A, 0x300, 0x2F6, 0x2ED, 0x2E3, 0x2D9, 0x2D0, 0x2C6, 0x2BD, 0x2B3, 0x2AA, 0x2A0, 0x297, 0x28E, 0x285, 0x27C, 0x273, 0x26A, 0x261, 0x258, 0x24F, 0x246, 0x23D, 0x235, 0x22C, 0x223, 0x21B, 0x212, 0x20A, 0x202, 0x1F9, 0x1F1, 0x1E9, 0x1E1, 0x1D9, 0x1D1, 0x1C9, 0x1C1, 0x1B9, 0x1B1, 0x1AA, 0x1A2, 0x19A, 0x193, 0x18B, 0x184, 0x17D, 0x175, 0x16E, 0x167, 0x160, 0x159, 0x152, 0x14B, 0x144, 0x13E, 0x137, 0x130, 0x12A, 0x123, 0x11D, 0x117, 0x110, 0x10A, 0x104, 0xFE, 0xF8, 0xF2, 0xEC, 0xE6, 0xE0, 0xDB, 0xD5, 0xCF, 0xCA, 0xC5, 0xBF, 0xBA, 0xB5, 0xB0, 0xAB, 0xA6, 0xA1, 0x9C, 0x97, 0x92, 0x8E, 0x89, 0x85, 0x80, 0x7C, 0x78, 0x73, 0x6F, 0x6B, 0x67, 0x63, 0x60, 0x5C, 0x58, 0x55, 0x51, 0x4E, 0x4A, 0x47, 0x44, 0x40, 0x3D, 0x3A, 0x37, 0x35, 0x32, 0x2F, 0x2C, 0x2A, 0x27, 0x25, 0x23, 0x20, 0x1E, 0x1C, 0x1A, 0x18, 0x16, 0x14, 0x13, 0x11, 0xF, 0xE, 0xC, 0xB, 0xA, 0x9, 0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x2, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xE, 0xF, 0x11, 0x13, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x23, 0x25, 0x27, 0x2A, 0x2C, 0x2F, 0x32, 0x35, 0x37, 0x3A, 0x3D, 0x40, 0x44, 0x47, 0x4A, 0x4E, 0x51, 0x55, 0x58, 0x5C, 0x60, 0x63, 0x67, 0x6B, 0x6F, 0x73, 0x78, 0x7C, 0x80, 0x85, 0x89, 0x8E, 0x92, 0x97, 0x9C, 0xA1, 0xA6, 0xAB, 0xB0, 0xB5, 0xBA, 0xBF, 0xC5, 0xCA, 0xCF, 0xD5, 0xDB, 0xE0, 0xE6, 0xEC, 0xF2, 0xF8, 0xFE, 0x104, 0x10A, 0x110, 0x117, 0x11D, 0x123, 0x12A, 0x130, 0x137, 0x13E, 0x144, 0x14B, 0x152, 0x159, 0x160, 0x167, 0x16E, 0x175, 0x17D, 0x184, 0x18B, 0x193, 0x19A, 0x1A2, 0x1AA, 0x1B1, 0x1B9, 0x1C1, 0x1C9, 0x1D1, 0x1D9, 0x1E1, 0x1E9, 0x1F1, 0x1F9, 0x202, 0x20A, 0x212, 0x21B, 0x223, 0x22C, 0x235, 0x23D, 0x246, 0x24F, 0x258, 0x261, 0x26A, 0x273, 0x27C, 0x285, 0x28E, 0x297, 0x2A0, 0x2AA, 0x2B3, 0x2BD, 0x2C6, 0x2D0, 0x2D9, 0x2E3, 0x2ED, 0x2F6, 0x300, 0x30A, 0x314, 0x31E, 0x328, 0x332, 0x33C, 0x346, 0x350, 0x35A, 0x365, 0x36F, 0x379, 0x384, 0x38E, 0x398, 0x3A3, 0x3AD, 0x3B8, 0x3C3, 0x3CD, 0x3D8, 0x3E3, 0x3EE, 0x3F9, 0x403, 0x40E, 0x419, 0x424, 0x42F, 0x43A, 0x445, 0x451, 0x45C, 0x467, 0x472, 0x47D, 0x489, 0x494, 0x49F, 0x4AB, 0x4B6, 0x4C2, 0x4CD, 0x4D9, 0x4E4, 0x4F0, 0x4FC, 0x507, 0x513, 0x51F, 0x52A, 0x536, 0x542, 0x54E, 0x55A, 0x565, 0x571, 0x57D, 0x589, 0x595, 0x5A1, 0x5AD, 0x5B9, 0x5C5, 0x5D1, 0x5DD, 0x5EA, 0x5F6, 0x602, 0x60E, 0x61A, 0x626, 0x633, 0x63F, 0x64B, 0x657, 0x664, 0x670, 0x67C, 0x689, 0x695, 0x6A1, 0x6AE, 0x6BA, 0x6C7, 0x6D3, 0x6E0, 0x6EC, 0x6F8, 0x705, 0x711, 0x71E, 0x72A, 0x737, 0x743, 0x750, 0x75C, 0x769, 0x775, 0x782, 0x78E, 0x79B, 0x7A8, 0x7B4, 0x7C1, 0x7CD, 0x7DA, 0x7E6, 0x7F3 };

register uint32_t volatile __R30;
register uint32_t volatile __R31;

void main()
{
	uint8_t volatile * sample_flag = (uint8_t volatile *)SHARED_MEM;

	uint8_t bit = 0x00;
	uint16_t buf = 0x0000;
	uint16_t counter = 0x0000;

	// Set the CFG Register to direct output instead of serial output
	CT_CFG.GPCFG0 = 0;

	// Clear the registers
	__R30 = 0x0000;
	__R31 = 0x0000;

	__R30 ^= (1 << DAC_CS);

	while( 1 )
	{
		++counter;
		counter &= 0x03FF;
		buf = WAVE_SAMPLES[ counter ];

		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		while( *sample_flag == 0 );

		__R30 &= ~(1 << DAC_CS);

		__R30 &= ~(1 << DAC_MOSI);	// 0 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 &= ~(1 << DAC_MOSI);	// 0 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

		__R30 |= (1 << DAC_MOSI);	// 1 - DAC
		__R30 &= ~(1 << CLK);
		__delay_cycles( DELAY_CYCLES );
		__R30 |= (1 << CLK);
		__delay_cycles( DELAY_CYCLES );

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
			__R30 |= (1 << CLK);
			__delay_cycles( DELAY_CYCLES );
		}

		__R30 |= (1 << DAC_CS);

		*sample_flag = 0;
	}
}
