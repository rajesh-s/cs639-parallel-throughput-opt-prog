# HW3

## Setup

CSL Machines:

```bash
source /s/intelcompilers-2019/bin/iccvars.sh intel64
icc *.cpp -qopenmp -mkl
```

## Description

Summary: You will replace some of our hand-coded kernel components in our Conjugate Gradients solver benchmark with equivalent code from the Intel Math Kernel Library (MKL).

Objective: Even it appears secondary to our goal of learning about parallel optimizations, a very significant objective of this assignment is to create a certain degree of comfort for you in using third-party libraries. This would require you to take a careful look at the documentation (of MKL, in this instance), make sure that you understand the semantics of the kernels that you replace, and those that are implemented within the MKL library, and sometimes make certain simple changes to bring those semantics in alignment before you replace your own code with the corresponding library call (see, e.g. the special versions of Saxpy, as we discuss below). Finally, it's an opportunity for you to collect timings for both the MKL implementation, and the reference version we previously crafted; in some cases you might see an acceleration, in other instances you might confirm that our own version was actually very competitive!

Description:  Your third programming assignment will require you to replace some of the hand-coded kernels involved in the Conjugate Gradients algorithm with library calls from the Intel Math Kernel Library & BLAS.

The code you will use as a basis of your implementation will be taken from LaplaceSolver/LaplaceSolver_1_5, and it will be useful to compare this implementation with the one found in LaplaceSolver/LaplaceSolver_1_0. If you compare these two versions, you will notice that the following changes have been made (we briefly discussed these in-class on March 4th, but we'll repeat the key points here):

The function MatVecMultiply() (in MatVecMultiply.cpp) has been changed to optionally replace (based on whether the macro DO_NOT_USE_MKL is defined) the hand-coded implementation of the CSR Matrix-Vector multiply with its counterpart within MKL (you can find the documentation for that MKL routine hereLinks to an external site.).
In file PointwiseOps.cpp you can see we now have two versions of the Saxpy() routine. The one we had seen previously takes the arguments Saxpy(x, y, z, scale) takes three vector arguments and one scalar, and performs the operation 
 . The newly implemented one, Saxpy(x, y, scale), takes one less argument, and uses the vector y to store the result instead, performing the operation 
 . This is actually the operation of the MKL Saxpy routine (see documentation hereLinks to an external site.), and in PointwiseOps.cpp you can see a similar construct that the hand-coded version is optionally replaced by the MKL equivalent. In PointwiseOps.cpp, in the part that corresponds to "Line 16" of the pseudocode-version algorithm (look for the comment "// Line 16" in the code file), we actually observe that one of the two Saxpy's involved is exactly of the latter form Saxpy(x, y, scale); the MKL-implemented version will thus be used here. 
Some minor changes have occured in ConjugateGradients.cpp, just to add a couple timers that capture the runtime of these newly added MKL-based implementations.
These two changes have been given to you as examples of using MKL implementations of some of the kernels we have used in the Conjugate Gradients benchmark. Your task will be to try and replace even more of the kernels that appear within this algorithm, with their MKL counterparts. In particular, it should be possible to provide alternative, MKL-based implementations for the following:

Other calls to Saxpy() within the Conjugate Gradients algorithm. Be cautious here; not all instances of this kernel have exactly the same semantics as the newly introduced Saxpy(x, y, scale) ... some of them, for example, use the full 3-vector version of this operation, with a separate destination vector than one of the inputs. Another (sneaky) variant that appears somewhere deposits the result of the operation 
 onto vector x instead (be mindful of such subtleties). But all of them can ultimately be implemented by (a combination, at most) of MKL kernels - you just need to be careful that you get the semantics right!
The InnerProduct() call.
The Copy() call.
The Norm() call.
In crafting replacements for such kernels, turn your attention to the "BLAS Level 1" kernels within MKL (Level 1 refers to the fact that these are vector-specific operations; Level 2 would be matrix-vector operations, and Level 3 would be matrix-matrix operations). Check out the documentation hereLinks to an external site., those should give you most of the tools you'll need! Hint: focus on the routines cblas_scopy, cblas_ssdot, cblas_saxpy, cblas_isamax

You are, of course, welcome to replace as many kernels as possible in this algorithm with MKL equivalents. But, to make matters easier, you will get a full grade if you successfully replace at least three kernel calls within the Conjugate Gradients routine with an implementation that uses MKL instead; different "versions" of Saxpy in this file count as different kernels, as long as it's not the version we have already given you (there's 2 more!). 

Make sure that your code works correctly, by checking that the "residual norm" values that a reported during execution are consistent across implementations. You should also time your alternative implementation in one of the following ways: Either (a) place a timer around individual kernels, and report the difference of the MKL-based vs. non-MKL implementations, or (b) time an entire loop of the Conjugate Gradients algorithm, and report an aggregate result. You are welcome to report times for the full-program execution of these kernels, or divide by the number of iterations to get an average "per-call/per-iteration" cost, do as you find most convenient. But, either way, include the timing numbers in your report. 