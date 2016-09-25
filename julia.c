/*
 * julia.c: Generate points to plot a Julia Set with a given parameter
 * 
 * Copyright (c) 2016 Trey Boehm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more detail.
 * <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <complex.h>
#include <math.h>

#define MAXITERATIONS 256 // Highest iteration count in testMembership()
//#define PARAMETER -0.805 + 0.175 * I // The `c' value (changes plot)
#define PARAMETER -.835 - .2321 * I // The `c' value (changes plot)
#define REMIN -1.6 // Minimum value on the real (horizontal) axis
#define REMAX 1.6 // Maximum value on the real (horizontal) axis
#define IMMIN -1.6 // Minimum value on the imaginary (vertical) axis
#define IMMAX 1.6 // Maximum value on the imaginary (vertical) axis
#define RESOLUTION 1000 // Width of the square plot generated (pixels)

// Find the magnitude of a complex number using Pythagorean theorem
float magnitude(float complex z);
// Count how many iterations it takes to diverge on z = z*z + c
int testMembership(float complex z);

float magnitude(float complex z) {
    float rePart = creal(z);
    float imPart = cimag(z);
    float sumSquares = rePart*rePart + imPart*imPart;
    return sqrt(sumSquares);
}

int testMembership(float complex z) {
    float complex param = PARAMETER;
    int count;
    for (count = 0; count < MAXITERATIONS; count++) {
        z = z*z + param;
        if (magnitude(z) > 2) {
            return count;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    float complex z;
    float delta = (REMAX-REMIN)/((float)RESOLUTION);
    float re;
    float im;
    int iterCount;

    for (re = REMIN; re < REMAX; re = re + delta) {
        for (im = IMMIN; im < IMMAX; im = im + delta) {
            z = re + im * I;
            iterCount = testMembership(z);
            printf("%.3f\t%.3f\t%d\n", re, im, iterCount);
        }
    }
    return 0;
}

