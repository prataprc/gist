unsigned int max = 0;
unsigned int min = 0;
unsigned int itercount = 0;

int newtonsguess( unsigned int x, unsigned int guess )
{
    unsigned int nextguess;

    itercount++;
    nextguess  = (( x / guess ) + guess ) / 2;
    min = guess < nextguess ? guess : nextguess;
    max = guess > nextguess ? guess : nextguess;
    
    printf( "%u %u \n", guess, nextguess );
    if (( max - min ) < 2 ) {
        return;
    } else {
        newtonsguess( x, nextguess );
    }
}

int issquare( unsigned int x )
{
    min = max = 0;
    itercount = 0;
    newtonsguess( x, 1 );
    printf( "%u %u \n", min, max );
}

int main(void)
{
    unsigned int x;
    unsigned int d;
    unsigned int i;

    /* Modified diaphontine equation
     *
     *  y^2     =  ( x^2 - 1 ) / D
     *
     */
    d = 2;
    for ( i = 0 ; i < ((1 << 31) - 1) ; i++ ) {
        if ( issquare( (i * i - 1 ) / d ) ) {
            x   = i;
        }
    }
    printf("%u\n", x);
}
