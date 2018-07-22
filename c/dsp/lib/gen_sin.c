//  Function    : gen_sin
//  Parameters  :
//      float freq  - frequency of the sin wave to be generated 
//      float phase - phase (float)
//      int sf      - Sampling frequency (int)
//      void* buff  - Pointer to the buffer where the samples should be
//                    stored.
//      char type   - type of the sample,
//                      1 - unsigned 
//                      2 - signed
//
//  Description : 
//      Generates the sin wave and populated the buffer.
//

void    gen_sin(float freq, int phase, int sf,  short *buff, char type)
{
    // Digital representation of the sin wave.
    //      f = analog frequency    (cycles / second)
    //      N = Sampling frequency  (Samples / second)
    //      T = 1 / N               (Sample period)
    //      w = 2 * pi * f          (radians / second)
    // x(t) = sin(wt)   
    //  
    // Digital Frequency
    //      Fd = w/N                (Radians / sample)
    //
    // x(n) = sin(Fd * n) = sin((w*n)/N)

    float   x;
    int     sample;
    int     n;

    printf("Generating the sin wave for %f ..... \n", freq);

    x = (2 * 3.14 * freq) / sf;
    for (n=0; n < sf; n++) {
        sample = (int)(sin(x*n) * 32767);
        if (type == 1) {
            sample += 32767;
            buff[n] = (unsigned short)sample;
        }
        buff[n] = (short)sample;
    }
    return;
}


