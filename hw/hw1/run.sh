#!/bin/bash
export OMP_NUM_THREADS=16

touch results_thread_sweep
for i in {1..48}
do
    export OMP_NUM_THREADS=$i
    ./laplacian3D >> results_thread_sweep
done
