#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../../libpruio-0.2/src/c_wrapper/pruio.h"

int main( int argc, char **argv )
{
    const uint32 tSamp = 200000;    // number of samples in the files (per step)
    const uint32 tmr = 5000;        // sampling rate in ns (5000 -> 200 kHz)
    const uint32 NoStep = 1;        // number of active steps (must match setStep calls and mask)
    const uint32 NoFile = 1;        // number of files to write
    const char * NamFil = "out.%u"; // output file names

    struct timespec mSec;
    mSec.tv_nsec=1000000;
    
    pruIo * io = pruio_new( PRUIO_DEF_ACTIVE, 0x98, 0, 1 ); // create driver
    
    do
    {
    	if( pruio_adc_setStep( io, 9, 0, 0, 0, 0 ) )
    	{
            printf( "Step 9 configuration failed: (%s)\n", io->Errr );
            break;
        }
        
        uint32 mask = 1 << 9;                                   // active steps
        uint32 tInd = tSamp * NoStep;                           // max total index
        uint32 half = ( ( io->ESize >> 2 ) / NoStep ) * NoStep; // max index of the half ring buffer
        
        if( half > tInd )
            half = tInd;   // adapt size for small files
        
        uint32 samp = ( half << 1 ) / NoStep; // number of samples (per step)
        
        if( pruio_config( io, samp, mask, tmr, 0 ) )
        {
            printf( "Config failed: (%s)\n", io->Errr );
            break;
        }
        
        if( pruio_rb_start( io ) )
        {
            printf( "rb_start failed: (%s)\n", io->Errr );
            break;
        }
        
        uint16 * p0 = io->Adc->Value;  // A pointer to start of the ring buffer
        uint16 * p1 = p0 + half;       // A pointer to the middle of the ring buffer
        uint32 n;                      // File counter
        char fName[20];
        
        for( n = 0; n < NoFile; ++n )
        {
            sprintf( fName, NamFil, n );
            printf( "Creating file %s\n", fName );
            FILE * oFile = fopen( fName, "wb" );
            uint32 i = 0;         // Start index
            while( i < tInd )
            {
                i += half;
                if( i > tInd )    // Fetch the rest
                {
                    uint32 rest = tInd + half - i;
                    uint32 iEnd = p1 >= p0 ? rest : rest + half;
                    while( io->DRam[0] < iEnd )
                        nanosleep( &mSec, NULL );
                    printf( "  Writing samples %u-%u\n", tInd - rest, tInd - 1 );
                    fwrite( p0, sizeof( uint16 ), rest, oFile );
                    uint16 * swap = p0;
                    p0 = p1;
                    p1 = swap;
                }
                if( p1 > p0 )
                    while( io->DRam[0] < half )
                        nanosleep( &mSec, NULL );
                else
                    while( io->DRam[0] > half )
                        nanosleep( &mSec, NULL );
                printf( "  Writing samples %u-%u\n", i - half, i - 1 );
                fwrite( p0, sizeof( uint16 ), half, oFile );
                uint16 * swap = p0;
                p0 = p1;
                p1 = swap;
            }
            fclose( oFile );
            printf( "Finished file %s\n", fName );
        }
    }
    while( 0 );

    pruio_destroy( io );   /* destroy driver structure */
    return 0;
}
