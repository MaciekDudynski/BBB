/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static void pabort(const char *s)
{
	perror(s);
	abort();
}

static uint32_t mode;
static uint8_t bits = 8;
static uint32_t speed = 2000000;
static int verbose;

uint8_t adc_tx[3]= {
	0x06, 0x00, 0x00
};

uint8_t adc_rx[3] = {
	0x00, 0x00, 0x00
};

uint8_t dac_tx[2]= {
	0x30, 0x00
};

static void adc_hex_dump( const void *src, char *prefix )
{
	int i = 0;
	const unsigned char *address = src;

	printf( "%s | ", prefix );
	for( ; i < 3; ++i )
	{
		printf( "%02X ", *(address + i) );
	}
	uint16_t val = ( (*(address + 1) & 0x0F ) << 8 ) | *(address + 2);
	printf( "| %4d\n", val );
}

static void dac_hex_dump( const void *src, char *prefix )
{
	int i = 0;
	const unsigned char *address = src;

	printf( "%s | ", prefix );
	for( ; i < 2; ++i )
	{
		printf( "%02X ", *(address + i) );
	}
	uint16_t val = ( (*(address) & 0x0F ) << 8 ) | *(address + 1);
	printf( "   | %4d\n", val );
}

static void transfer_adc( int fd )
{
	int ret;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)adc_tx,
		.rx_buf = (unsigned long)adc_rx,
		.len = 3,
		.delay_usecs = 0,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	ret = ioctl( fd, SPI_IOC_MESSAGE(1), &tr );
	if( ret < 1 )
		pabort( "Can't send spi message: ADC" );

	if( verbose )
	{
		adc_hex_dump( adc_tx, "ADC TX" );
		adc_hex_dump( adc_rx, "ADC RX" );
	}		
}

static void transfer_dac( int fd )
{
	dac_tx[0] = adc_rx[1] & 0x0F;
	dac_tx[0] |= 0x30;
	dac_tx[1] = adc_rx[2];
	
	int ret;	
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)dac_tx,
		.len = 2,
		.delay_usecs = 0,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	ret = ioctl( fd, SPI_IOC_MESSAGE(1), &tr );
	if( ret < 1 )
		pabort( "Can't send spi message: DAC" );

	if( verbose )
	{
		dac_hex_dump( dac_tx, "DAC TX" );
	}		
}

static void print_usage( const char *prog )
{
	printf( "Usage: %s [-v]\n", prog );
	puts( "  -v --verbose  Verbose (show tx buffer)\n" );
	exit( 1 );
}

static void parse_opts( int argc, char *argv[] )
{
	while( 1 ) {
		static const struct option lopts[] = {
			{ "verbose", 0, 0, 'v' },
			{ NULL, 0, 0, 0 },
		};
		int c;

		c = getopt_long( argc, argv, "v", lopts, NULL );

		if( c == -1 )
			break;

		switch( c )
		{
			case 'v':
				verbose = 1;
				break;
			default:
				print_usage(argv[0]);
				break;
		}
	}
}

int main( int argc, char *argv[] )
{
	int ret = 0;
	int adc_fd, dac_fd;

	parse_opts( argc, argv );

	adc_fd = open( "/dev/spidev1.0", O_RDWR );
	if( adc_fd < 0 )
		pabort( "Can't open device: /dev/spidev1.0" );
	dac_fd = open( "/dev/spidev2.0", O_RDWR );
	if( dac_fd < 0 )
		pabort( "Can't open device: /dev/spidev2.0" );

	/*
	 * spi mode
	 */
	ret = ioctl( adc_fd, SPI_IOC_WR_MODE32, &mode );
	if( ret == -1 )
		pabort( "Can't set SPI mode: ADC" );
	ret = ioctl( dac_fd, SPI_IOC_WR_MODE32, &mode );
	if( ret == -1 )
		pabort( "Can't set SPI mode: DAC" );

	ret = ioctl( adc_fd, SPI_IOC_RD_MODE32, &mode );
	if( ret == -1 )
		pabort( "Can't get SPI mode: ADC" );
	ret = ioctl( dac_fd, SPI_IOC_RD_MODE32, &mode );
	if( ret == -1 )
		pabort( "Can't get SPI mode: DAC" );

	/*
	 * bits per word
	 */
	ret = ioctl( adc_fd, SPI_IOC_WR_BITS_PER_WORD, &bits );
	if( ret == -1 )
		pabort( "Can't set bits per word: ADC" );
	ret = ioctl( dac_fd, SPI_IOC_WR_BITS_PER_WORD, &bits );
	if( ret == -1 )
		pabort( "Can't set bits per word: DAC" );

	ret = ioctl( adc_fd, SPI_IOC_RD_BITS_PER_WORD, &bits );
	if( ret == -1 )
		pabort( "Can't get bits per word: ADC" );
	ret = ioctl( dac_fd, SPI_IOC_RD_BITS_PER_WORD, &bits );
	if( ret == -1 )
		pabort( "Can't get bits per word: DAC" );

	/*
	 * max speed hz
	 */
	ret = ioctl( adc_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed );
	if( ret == -1 )
		pabort( "Can't set max speed Hz: ADC" );
	ret = ioctl( dac_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed );
	if( ret == -1 )
		pabort( "Can't set max speed Hz: DAC" );

	ret = ioctl( adc_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed );
	if( ret == -1 )
		pabort( "Can't get max speed Hz: ADC" );
	ret = ioctl( dac_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed );
	if( ret == -1 )
		pabort( "Can't get max speed Hz: DAC" );

	printf( "SPI mode: 0x%x\n", mode );
	printf( "Bits per word: %d\n", bits );
	printf( "Max speed: %d Hz (%d KHz)\n", speed, speed/1000 );
	
	uint16_t i = 0;
	while( 1 )
	{
		transfer_adc( adc_fd );
		transfer_dac( dac_fd );
	}

	close( adc_fd );
	close( dac_fd );

	return ret;
}
