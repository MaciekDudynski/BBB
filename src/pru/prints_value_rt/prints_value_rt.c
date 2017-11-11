#define _GNU_SOURCE 1
#include "stdio.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include "../../libpruio-0.2/src/c_wrapper/pruio.h"

int isleep( unsigned int mseconds )
{
    fd_set set;
    struct timeval timeout;

    /* Initialize the file descriptor set. */
    FD_ZERO( &set );
    FD_SET( STDIN_FILENO, &set );

    /* Initialize the timeout data structure. */
    timeout.tv_sec = 0;
    timeout.tv_usec = mseconds * 1000;

    return TEMP_FAILURE_RETRY( select( FD_SETSIZE,
                                       &set, NULL, NULL,
                                       &timeout ) );
}

int main( int argc, char **argv )
{
    int count = 0;
    pruIo *io = pruio_new( PRUIO_ACT_ADC, 0x98, 0, 1 );   /* create new driver structure */
    do
    {
        if( io->Errr )
        {
            printf( "initialisation failed (%s)\n", io->Errr );
            break;
        }
        if( pruio_config( io, 1, 0x002, 22675, 0 ) )
        {
            printf( "config failed (%s)\n", io->Errr );
            break;
        }

        struct termios oldt, newt;
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        newt.c_cc[ VMIN ] = 0;
        newt.c_cc[ VTIME ] = 0;
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );

        while( !isleep( 1 ) )
        {
            printf( "\r    %6d    %10d",
                    io->Adc->Value[1], count );
            fflush( STDIN_FILENO );
            ++count;
        }
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        printf( "\n" );
    }
    while( 0 );

    pruio_destroy( io );   /* destroy driver structure */
    return 0;
}
