#include "Reductions.h"

// #define DO_NOT_USE_MKL
#ifndef DO_NOT_USE_MKL
#include <mkl.h>
#endif

#include <algorithm>

float Norm(const float (&x)[XDIM][YDIM][ZDIM])
{
#ifdef DO_NOT_USE_MKL
    float result = 0.;
#pragma omp parallel for reduction(max:result)
    for (int i = 1; i < XDIM-1; i++)
    for (int j = 1; j < YDIM-1; j++)
    for (int k = 1; k < ZDIM-1; k++)
        result = std::max(result, std::abs(x[i][j][k]));
    return result;
#else
    int idx =
    cblas_isamax( // Rajesh: Replaced for MKL variant
        XDIM * YDIM * ZDIM, // Specifies the number of elements
        &x[0][0][0], // Array, size at least (1 + (n-1)*abs(incx))
        1 // Specifies the increment for the elements of x
    );
    // Retrieve element from index
    int i = idx / (XDIM * YDIM);
    int j = (idx - (i * XDIM * YDIM)) / XDIM;
    int k = idx - (i * XDIM * YDIM) - (j * XDIM);
    return std::abs(x[i][j][k]);
#endif
}

float InnerProduct(const float (&x)[XDIM][YDIM][ZDIM], const float (&y)[XDIM][YDIM][ZDIM])
{
#ifdef DO_NOT_USE_MKL 
    double result = 0.;
#pragma omp parallel for reduction(+:result)
    for (int i = 1; i < XDIM-1; i++)
    for (int j = 1; j < YDIM-1; j++)
    for (int k = 1; k < ZDIM-1; k++)
        result += (double) x[i][j][k] * (double) y[i][j][k];
    return (float) result;
#else
    return
    cblas_sdot(
        XDIM * YDIM * ZDIM, // Specifies the number of elements in vectors x and y
        &x[0][0][0], // Array, size at least (1 + (n-1)*abs(incx))
        1, // Specifies the increment for the elements of x
        &y[0][0][0], // Array, size at least (1 + (n-1)*abs(incy))
        1 // Specifies the increment for the elements of y
    );
#endif
}
