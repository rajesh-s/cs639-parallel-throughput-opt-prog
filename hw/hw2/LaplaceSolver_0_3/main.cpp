#include "ConjugateGradients.h"
#include "Timer.h"
#include "Utilities.h"

Timer timerLaplacian1;
Timer timerLaplacian2;
Timer timerCopy1;
Timer timerCopy2;
Timer timerIP1;
Timer timerIP2;
Timer timerIP3;
Timer timerNorm1;
Timer timerNorm2;
Timer timerSaxpy1;
Timer timerSaxpy2;
Timer timerSaxpy3;
Timer timerSaxpy4;
Timer timerSaxpy5;

int main(int argc, char *argv[])
{
    using array_t = float (&) [XDIM][YDIM][ZDIM];

    float *xRaw = new float [XDIM*YDIM*ZDIM];
    float *fRaw = new float [XDIM*YDIM*ZDIM];
    float *pRaw = new float [XDIM*YDIM*ZDIM];
    float *rRaw = new float [XDIM*YDIM*ZDIM];
    float *zRaw = new float [XDIM*YDIM*ZDIM];
    
    array_t x = reinterpret_cast<array_t>(*xRaw);
    array_t f = reinterpret_cast<array_t>(*fRaw);
    array_t p = reinterpret_cast<array_t>(*pRaw);
    array_t r = reinterpret_cast<array_t>(*rRaw);
    array_t z = reinterpret_cast<array_t>(*zRaw);
    
    // Initialization
    {
        Timer timer;
        timer.Start();
        InitializeProblem(x, f);
        timer.Stop("Initialization : ");
    }

    // Call Conjugate Gradients algorithm
    timerLaplacian1.Reset();
    timerLaplacian2.Reset();
    timerCopy1.Reset();
    timerCopy2.Reset();
    timerIP1.Reset();
    timerIP2.Reset();
    timerIP3.Reset();
    timerNorm1.Reset();
    timerNorm2.Reset();
    timerSaxpy1.Reset();
    timerSaxpy2.Reset();
    timerSaxpy3.Reset();
    timerSaxpy4.Reset();
    timerSaxpy5.Reset();
    ConjugateGradients(x, f, p, r, z);
    timerLaplacian1.Print("Total Laplacian 1 Time : ");
    timerLaplacian2.Print("Total Laplacian 2 Time : ");
    timerCopy1.Print("Total Copy 1 Time : ");
    timerCopy2.Print("Total Copy 2 Time : ");
    timerIP1.Print("Total InnerProduct 1 Time : ");
    timerIP2.Print("Total InnerProduct 2 Time : ");
    timerIP3.Print("Total InnerProduct 3 Time : ");
    timerNorm1.Print("Total Norm 1 Time : ");
    timerNorm2.Print("Total Norm 2 Time : ");
    timerSaxpy1.Print("Total Saxpy 1 Time : ");
    timerSaxpy2.Print("Total Saxpy 2 Time : ");
    timerSaxpy3.Print("Total Saxpy 3 Time : ");
    timerSaxpy4.Print("Total Saxpy 4 Time : ");
    timerSaxpy5.Print("Total Saxpy 5 Time : ");
    return 0;
}
