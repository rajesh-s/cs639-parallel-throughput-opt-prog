# HW2

**Summary**: You will modify our stencil-based (as opposed to the matrix-based) implementation of the Conjugate Gradients solver, as to combine certain primitive kernels into slightly larger ones, when possible, to explore the potential benefit in performance by reducing memory bandwidth demands. 

Objective: There are several useful skills that will hopefully be practiced in this exercise. You will have to make some performance-oriented modifications to an implementation, while being careful to not really change the underlying algorithm; as a result you will have to both be careful when modifying the code, and double-check that the results produced didn't change in any nontrivial way. Finally, you will be able to probe the performance implications of such modifications on your own computer - although findings will not be uniform across all platforms, the goal is to detect such effects and attempt to justify them.

Deliverable: Place your code in a .zip archive, including a written report (e.g. in PDF, Word, or TXT format) and any auxiliary files for the sake of compilation (Makefiles, etc) and submit it through Canvas. In the written report (2-4 pages should suffice) make sure to include information on (a) What computer, including CPU model, you ran this on, (b) What operating system and compiler you used, and (c) How you compiled the code (e.g. did you compile and run via the command line? did you give any specific options? did you need to install anything particular for this to work?). You do not need to explicitly include in your report line-by-line code changes that you made, but if there are any snippets of code that you feel are worth pointing out (maybe to highlight that there was a very subtle change that you found to be particularly impactful), you are welcome to do so. Optionally: you are welcome to state in your report how long it took you to complete this work; this will not impact your grade in any way, it will just help us calibrate the difficulty of these assignments. 

Effort: The median time commitment for this assignment will likely be around 5-6hrs, provided that you have already made yourselves comfortable with the material that was required of you in the previous programming assignment (#1) Of course, if you need to catch up on the recorded lectures, before starting on the assignment, this would also take a little extra time (lectures up to, and including March 23rd would be the most relevant to this assignment). 

Grading: Will be on a 5-point scale (roughly corresponding to 0%, 20%, 40%, 60%, 80% and 100% success). 

Deadline: Friday March 3rd, at midnight.

Late policy: Canvas submission will remain open for 2 more days, till Sunday March 5th at midnight. Late submissions will be penalized with 1 point subtracted, in the 5-point grade scale. The first late assignment for each student in a semester will be "forgiven"; subsequent late submissions will carry the 1-point penalty. 

Description: Your second programming assignment will focus on the two following skills:

Ensuring that you have a certain level of comfort with timing individual functional components (i.e. kernels) of a performance-sensitive algorithm, and
Giving you some exposure to designing and optimizing kernels that fit into a larger algorithm, in our particular case by merging multiple kernels into one, for purposes of performance optimization.
The code you will use as a basis of your implementation will be taken from LaplaceSolver/LaplaceSolver_0_2, and you will likely be following the example illustrated in LaplaceSolver/LaplaceSolver_0_3 for using the "new" Timer class to benchmark kernel calls (the last point was also briefly discussed in the February 21st lecture).

Your tasks are as follows:

The code directories above provide a sample implementation for the Conjugate Gradients algorithm we described in class (use our slides from Feb 16th as reference [Link], for example looking at page 6 of those notes).
[Note: As we discussed in class, the statement of this algorithm in the notes is a bit more generic than the narrow case in the implementation. In particular, (a) the algorithmic steps in red color are not necessary for the type of problem we used in our example, and may be omitted, and (b) operations marked by the "dagger" symbol (†) in lines 4 and 13 are stand-ins for "preconditioners" that we will discuss later. You are free to consider the matrix M in those expressions as being simply the identity, which reduces them simply to assignment of r into p in line 4, and r into z in line 13].
In the supplied implementation, we have partitioned all the nontrivial computation into "kernels", such as ComputeLaplacian, InnerProduct, Norm, and Saxpy. For one of these kernels (the Laplacian stencil computation) we have previously timed the cost of individual executions, but done so in isolation; the kernel was executed repeatedly by itself, and not in the context of a larger algorithm, as Conjugate Gradients here. The example in LaplaceSolver/LaplaceSolver_0_3 shows how we can use the "new" Timer class to capture the time dedicated to the call to ComputeLaplacian within the context of the Conjugate Gradients algorithm! (again, refer to the February 21st lecture for a brief discussion of this particular part). 

Your task will be to instrument the code so that the cumulative time dedicated to each kernel call (not just ComputeLaplacian) is computed, for the entire duration of the Conjugate Gradients algorithm (as set up in the example, about 250-260 iterations are executed, at the preset resolution). That is, we want to know how much time was spent on each kernel call across all iterations of the algorithm, which will give us the proper idea of how much this kernel contributed to the execution time of the entire Conjugate Gradients algorithm. You are only required to report the cumulative time, across all iterations; it is highly optional but not required that you divide by the number of iterations to also report a "per iteration" average cost.
 
[Optional/Recommended, but not mandatory : if a kernel is invoked more than once per iteration, you should report on it separately, for example:
InnerProduct() on line 6 : Time = xxx ms.
InnerProduct() on line 13 : Time = yyy ms.
1st Saxpy() on line 16 : Time = zzz ms.
2nd Saxpy() on line 16 : Time = www ms.]

Report the timing breakdown for two runs : (a) A serial run, with no parallelism, using only a single thread, and (b) A parallel run, using all threads available on your computer. For each test, also include timing for the entire Conjugate Gradients algorithm; if you have done this exercise properly, that time should be almost equal to the sum of the individual kernels you have broken down execution into.

It is strongly recommended that you disable the "output" to an image file while doing this performance measurement; you do not (and should not) include the cost of writing out the result of each iteration to an image file.
Hint: For this part of the assignment, be aware that you will almost certainly need to create several Timer objects, one for each kernel you seek to benchmark. Make sure to include an "extern ..." declaration in ConjugateGradients.cpp for each, if you define all such timers in main.cpp!

In our February 16th class, we talked about the possibility of combining a number of kernels into a single (different) kernel, which could allow us to minimize memory usage, by streaming through certain arrays just once per kernel execution, instead of several times. Pages 6 through 11 of the aforementioned class notes [Link] illustrate groups of kernels for which such merging may be possible.
Your task will be to combine at least two groups of kernels from those illustrated in pages 6 through 11, into a new kernel. If you're ambitious, you can try to do all (5?) of these "combined" kernels, although just 2 (correctly done) will be sufficient for full credit.

You are free to specialize the kernel as much as you need, assuming that it is correct for the task that is needed! For example, general-purpose Saxpy calls may allow the destination array to be different than one of the input arrays; when designing your own "replacement/merged" kernel, you are free to specialize such instance of the kernel, for example to re-use some of the input arrays as the output arrays by design (rather than by-coincidence).

After you implement and test your new kernels (make sure you still get the correct/same behavior as before!) time the "old" group of kernels and compare with the new "merged" kernel. Report the results for single-thread, and multi-threaded (on all available cores) execution.
For your deliverable, include both code and a brief report, i.e. for task #1, show what you needed to change to instrument the code to collect timing information, and for task #2 show your replacement kernel (it will presumably be a separate pair of h/cpp files), and how you linked it in your existing project. Also include a brief report (in PDF or text format) with the timing information requested, and (optionally) other observations or comments from your implementation experience.