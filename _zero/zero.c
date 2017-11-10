#include <stdio.h>

#define AIN_0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

int main( int argn, char ** args )
{
    FILE * in;
    char value[ 5 ];
    
    in = fopen( AIN_0, "rb" );
    if( in == NULL )
    {
        printf( "Cannot open file: %s\n", AIN_0 );
        return 1;
    }
    fclose( in );
    
    while( 1 )
    {
        in = fopen( AIN_0, "rb" );
        fread( value, sizeof( char ), 4, in );
        fclose( in );
        printf( "%s\n", value );
    }
    
    return 0;
}
