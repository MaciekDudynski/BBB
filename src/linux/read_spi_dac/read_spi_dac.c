#include <stdio.h>
#include "../spi_bus/SPIDevice.h"

using namespace std;
using namespace exploringBB;

short combineValues( unsigned char upper, unsigned char lower )
{
   return ( (short)upper << 8 ) | (short)lower;
}

int main()
{
    SPIDevice * busDevice = new SPIDevice( 1, 0 ); // Using second SPI bus (both loaded)
    busDevice->setSpeed( 4000000 );                // Have access to SPI Device object
    busDevice->setMode( SPIDevice::MODE0 );

    unsigned char send[ 3 ], receive[ 3 ];

    send[ 0 ] = 0b00000110; // Start, SGL/Diff, D2 bits - set to single
    send[ 1 ] = 0b00000000; // D1, D0 bits - set to CH0
    send[ 2 ] = 0b00000000; // This bytes doesn't need to be set, just for a clear display
    busDevice->transfer( send, receive, 3 );

    printf( "Response bytes are %d %d %d\n",
        receive[ 0 ], receive[ 1 ], receive[ 2 ] );
    // printf( "Value bytes are %d %d %d\n",
    //     ( receive[ 0 ] & 0b00000000 ),
    //     ( receive[ 1 ] & 0b00001111 ),
    //     ( receive[ 2 ] & 0b11111111 ) );

    int value = combineValues( receive[ 1 ] & 0b00001111, receive[ 2 ] );

    printf( "This is the value %d out of 4095.\n", value );
}
