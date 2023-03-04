#include "Laplacian.h"
#include "Parameters.h"
#include "PointwiseOps.h"
#include "Reductions.h"
#include "Utilities.h"
#include "Timer.h"

#include <iostream>

extern Timer timerLaplacian1;
extern Timer timerLaplacian2;

extern Timer timerCopy1;
extern Timer timerCopy2;

extern Timer timerIP1;
extern Timer timerIP2;
extern Timer timerIP3;

extern Timer timerNorm1;
extern Timer timerNorm2;

extern Timer timerSaxpy1;
extern Timer timerSaxpy2;
extern Timer timerSaxpy3;
extern Timer timerSaxpy4;
extern Timer timerSaxpy5;

void ConjugateGradients(
    float (&x)[XDIM][YDIM][ZDIM],
    const float (&f)[XDIM][YDIM][ZDIM],
    float (&p)[XDIM][YDIM][ZDIM],
    float (&r)[XDIM][YDIM][ZDIM],
    float (&z)[XDIM][YDIM][ZDIM],
    const bool writeIterations)
{
    // Algorithm : Line 2
    timerLaplacian1.Restart(); ComputeLaplacian(x, z); timerLaplacian1.Pause();
    timerSaxpy1.Restart(); Saxpy(z, f, r, -1); timerSaxpy1.Pause();
    timerNorm1.Restart(); float nu = Norm(r); timerNorm1.Pause();

    // Algorithm : Line 3
    if (nu < nuMax) return;
        
    // Algorithm : Line 4
    timerCopy1.Restart(); Copy(r, p); timerCopy1.Pause(); 
    timerIP1.Restart(); float rho=InnerProduct(p, r); timerIP1.Pause(); 
        
    // Beginning of loop from Line 5
    for(int k=0;;k++)
    {
        std::cout << "Residual norm (nu) after " << k << " iterations = " << nu << std::endl;

        // Algorithm : Line 6
        timerLaplacian2.Restart(); ComputeLaplacian(p, z); timerLaplacian2.Pause();
        timerIP2.Restart(); float sigma=InnerProduct(p, z); timerIP2.Pause(); 

        // Algorithm : Line 7
        float alpha=rho/sigma;

        // Algorithm : Line 8
        timerSaxpy2.Restart(); Saxpy(z, r, r, -alpha); timerSaxpy2.Pause();
        timerNorm2.Restart(); nu=Norm(r); timerNorm2.Pause();

        // Algorithm : Lines 9-12
        if (nu < nuMax || k == kMax) {
            timerSaxpy3.Restart(); Saxpy(p, x, x, alpha); timerSaxpy3.Pause();
            std::cout << "Conjugate Gradients terminated after " << k << " iterations; residual norm (nu) = " << nu << std::endl;
            if (writeIterations) WriteAsImage("x", x, k, 0, 127);
            return;
        }
            
        // Algorithm : Line 13
        timerCopy2.Restart(); Copy(r, z); timerCopy2.Pause();
        timerIP3.Restart(); float rho_new = InnerProduct(z, r); timerIP3.Pause();

        // Algorithm : Line 14
        float beta = rho_new/rho;

        // Algorithm : Line 15
        rho=rho_new;

        // Algorithm : Line 16
        timerSaxpy4.Restart(); Saxpy(p, x, x, alpha); timerSaxpy4.Pause();
        timerSaxpy5.Restart(); Saxpy(p, r, p, beta); timerSaxpy5.Pause();

        if (writeIterations) WriteAsImage("x", x, k, 0, 127);
    }

}
