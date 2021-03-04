#include <stdio.h>

const long double WIDTH = 150;
const long double HEIGHT = 50;

const long double RE_START = -2;
const long double RE_END = 1;
const long double IM_START = -1;
const long double IM_END = 1;

const int MAX_ITER = 100;
const char ALPHA[] = "@#**+++====-----::::...... ";

int mandelbrot(long double real, long double imag) {
    long double r = 0;
    long double i = 0;
    int n = 0;
    long double rtemp;
    while (r*r + i*i <= 4 && n < MAX_ITER) {
        rtemp = r*r - i*i + real;
        i = 2*r*i + imag;
        r = rtemp;
        n++;
    }
    return n;
}

int main() {
    long double real;
    long double imag;
    int value;
    long double alphalen = sizeof(ALPHA)/sizeof(char);
    int index;
    alphalen--;
    alphalen--;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            real = RE_START + (x / WIDTH) * (RE_END - RE_START);
            imag = IM_START + (y / HEIGHT) * (IM_END - IM_START);
            value = mandelbrot(real, imag) * alphalen;
            index = value / MAX_ITER;
            printf("%c", ALPHA[index]);
        }
        printf("\n");
    }
    return 0;
}