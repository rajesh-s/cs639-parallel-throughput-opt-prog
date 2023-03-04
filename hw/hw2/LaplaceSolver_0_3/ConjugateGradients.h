#pragma once

#include "Parameters.h"

void ConjugateGradients(
    float (&x)[XDIM][YDIM][ZDIM],
    const float (&f)[XDIM][YDIM][ZDIM],
    float (&p)[XDIM][YDIM][ZDIM],
    float (&r)[XDIM][YDIM][ZDIM],
    float (&z)[XDIM][YDIM][ZDIM],
    const bool writeIterations = false); 
// Rajesh: It is strongly recommended that you disable the "output" to an image 
// file while doing this performance measurement; you do not (and should not) include 
// the cost of writing out the result of each iteration to an image file.

