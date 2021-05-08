#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SetBit(k)     ( primes[(k/32)] |= (1 << (k%32)) )
#define TestBit(k)    ( primes[(k/32)] & (1 << (k%32)) )

int main(int argc, char *argv[]) {
    int* primes;
    unsigned long int rootlim;
    unsigned long int factor;
    unsigned long int i;
    unsigned long int lim;

    if(argc<=1) {
        printf("Please provide a number\n");
        return 1;
    }
    lim = strtoul(argv[1], NULL, 0);

    primes = malloc(lim + (2*sizeof(int)) - (lim % sizeof(int)));
    if (primes == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    for (i = 0; i < (lim / sizeof(int)) + 1; i++) {
        primes[i] = 0;
    }

    rootlim = sqrt(lim);
    rootlim++;
    factor = 0;
    SetBit(0);
    SetBit(1);

    while (factor < rootlim) {
        while (factor < lim) {
            if (!TestBit(factor)) {
                break;
            }
            factor++;
        }
        for (i = factor * factor; i < lim; i += factor) {
            SetBit(i);
        }
        factor++;
    }
    return 0;
}