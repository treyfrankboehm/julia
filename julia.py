#!/usr/bin/env python3

# To make the cover image:
#   - maxIterations = 256
#   - uncomment the ``if count == maxIterations...'' line and comment
#   the one after it in julia.py
#   - set resolution in julia.gplot to 500x500
#   - uncomment last line of julia.gplot, comment the one before it


#   julia.py: generate points to plot a Julia set with a given parameter
#
#   Copyright (c) 2016 Trey Boehm
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more detail.
#   <http://www.gnu.org/licenses/>

from euler import frange

# Define important magic numbers
parameter = complex(-.805, .175)    # Complex parameter for the function
maxIterations = 256                 # Limit on iterations to test points
realDomain = [-1.6, 1.6]            # Horizontal (real) limits
imagRange  = [-1.6, 1.6]            # Vertical (imaginary) limits
delta = (realDomain[1]-realDomain[0])/1600  # Step for 1600x1600 image

# Return how many iterations it takes z**2 + c to diverge
def testMembership(z, c):
    count = 0
    for i in range(maxIterations):
        z = z**2 + c
        if abs(z) > 2:
            break
        count += 1
    return count

# Iterate over all points in the complex plane bounded by realDomain and
# imagRange, using delta as the step size. Run points (z = x+iy) through
# testMembership(z, c) and print a tab-separated line formatted as such:
# xValue    <tab>   yValue  <tab>   result of testMembership(z,c)
def juliaPoints(c):
    x = realDomain[0]
    while x <= realDomain[1]:
        y = imagRange[0]
        while y <= imagRange[1]:
            z = complex(x, y)
            count = testMembership(z, c)
            #if count == maxIterations: print("%f\t%f" % (x, y))
            print("%f\t%f\t%d" % (x, y, count))
            y += delta
        x += delta

# Run the above function if this program is executed.
if __name__ == "__main__":
    juliaPoints(parameter)

