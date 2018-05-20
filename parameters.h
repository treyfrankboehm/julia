#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#define MAX_ITERATIONS 256 // Highest iteration count in testMembership)
//#define PARAMETER (-0.550 - 0.510*I)
#define PARAMETER (-0.805 + 0.175*I)
//#define PARAMETER (-.835 - .2321*I)
//#define PARAMETER (-0.7269 + 0.1889*I)
#define REMIN -1.7 // Minimum value on the real (horizontal) axis
#define REMAX 1.7 // Maximum value on the real (horizontal) axis
#define IMMIN -1.5 // Minimum value on the imaginary (vertical) axis
#define IMMAX 1.5 // Maximum value on the imaginary (vertical) axis
#define RESOLUTION 800 // Width of the square plot generated (pixels)
#define THETA_STEP 0.01 // How much to change angle for gif generation
#define CREATE_GIF

#endif

