#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;

int main( int argn, char ** argc )
{
	int ret;

	int fd = open( "/dev/spidev1.1", O_RDWR );
	if( fd < 0 )
	{
		printf( "Cannot open spidev file (device)." );
		return 1;
	}

	ret = ioctl( fd, SPI_IOC_WR_MODE, &mode );
	if( ret == -1 )
	{
		printf( "Can't set spi mode." );
		return 1;
	}
	ret = ioctl( fd, SPI_IOC_RD_MODE, &mode );
	if( ret == -1 )
	{
		printf( "Can't get spi mode." );
		return 1;
	}

	ret = ioctl( fd, SPI_IOC_WR_BITS_PER_WORD, &bits );
	if( ret == -1 )
	{
		printf( "Can't set bits per word." );
		return 1;
	}
	ret = ioctl( fd, SPI_IOC_RD_BITS_PER_WORD, &bits );
	if( ret == -1 )
	{
		printf( "Can't get bits per word." );
		return 1;
	}

	ret = ioctl( fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed );
	if( ret == -1 )
	{
		printf( "Can't set max speed hz." );
		return 1;
	}
	ret = ioctl( fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed );
	if( ret == -1 )
	{
		printf( "Can't get max speed hz." );
		return 1;
	}

	printf( "spi mode: %d\n", mode );
	printf( "bits per word: %d\n", bits );
	printf( "max speed: %d Hz (%d kHz)\n", speed, speed/1000 );

	return 0;
}

