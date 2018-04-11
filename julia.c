/*
 * julia.c: Generate points to plot a Julia Set with given parameters
 *
 * Copyright (c) 2018 Trey Boehm
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
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "parameters.h"

/* Number of iterations for z = zeqn(z)+c to diverge */
int testMembership(double complex z, double complex parameter);
/* The equation we iterate on */
double complex zeqn(double complex z);

int testMembership(double complex z, double complex parameter) {
    int count;
    for (count = 0; count < MAX_ITERATIONS; count++) {
        z = zeqn(z) + parameter;
        if (cabs(z) > 4) {
            return count;
        }
    }
    return count;
}

double complex zeqn(double complex z) {
    //return (1-cpow(z,4)/24)/cpow((z-cpow(z,3)/6),3);
    //return (1-cpow(z,3)/6)/cpow((z-cpow(z,2)/2),2);
    //return (1-z*z*z/6)/((z-z*z/2)*(z-z*z/2));
    return cpow(z,2);
}

int main(int argc, char *argv[]) {
    double complex z;
    double delta = (REMAX-REMIN)/((double)RESOLUTION);
    double re;
    double im;
    double theta;
    //double complex radius = PARAMETER;
    double radius = 0.707;
    double complex cVal;
    int iterCount;

    char gnuplotCMD[1000];
    char mvCMD[100];
    FILE* fp;
    char buffer[50];

    sprintf(gnuplotCMD, "gnuplot -e \"reset; set terminal pngcairo size %d, %d; set cbrange [1:%d]; load 'jet.pal'; set output 'png/julia.png'; set lmargin 0; set rmargin 0; set bmargin 0; set tmargin 0; unset border; unset colorbox; unset xtics; unset ytics; plot 'data.txt' with image notitle\" 2>/dev/null", RESOLUTION, RESOLUTION, MAX_ITERATIONS);

    system("mkdir -p png");

    for (theta = 0; theta < 2*3.14159; theta += THETA_STEP) {
        fp = fopen("data.txt", "w");
        //cVal = radius*cos(theta) + radius*sin(theta)*I;
        cVal = radius*cexp(theta*I);
        for (re = REMIN; re < REMAX; re = re + delta) {
            for (im = IMMIN; im < IMMAX; im = im + delta) {
                z = re + im * I;
                iterCount = testMembership(z, cVal);
                sprintf(buffer, "%.3f\t%.3f\t%d\n", re, im, iterCount);
                fwrite(buffer, strlen(buffer), 1, fp);

            }
        }
        printf("theta = %.2f/6.28\n", theta);
        fclose(fp);

        system(gnuplotCMD);
        system("rm data.txt");
        sprintf(mvCMD, "mv png/julia.png png/julia-%.3f.png", theta);
        system(mvCMD);
    }

    return 0;
}

