#include "stdio.h"
#include "../../libpruio-0.2/src/c_wrapper/pruio.h"

int main(int argc, char **argv)
{
    FILE * out;
    int n;
    pruIo *io = pruio_new( PRUIO_DEF_ACTIVE, 0x98, 0, 1 );   /* create new driver structure */
    if( pruio_config( io, 1, 0x1FE, 0, 4 ) )
    {
        printf( "config failed (%s)\n", io->Errr );
    }
    else
    {
        out = fopen( "first_reads.txt", "w" );
        for( n = 1; n <= 1000000; n++ )
        {
            fprintf( out, " %4X", io->Adc->Value[1] );
            // if( n % 10 == 0 )
                // printf( "\n" );
        }
        fclose( out );
    }

    pruio_destroy(io);   /* destroy driver structure */
    return 0;
}
