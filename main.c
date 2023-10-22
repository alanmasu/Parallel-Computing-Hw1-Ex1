/*                      INTRODUCTION TO PARALLEL COMPUTING - Prof. VELLA 

    Student: Alan Masutti - 226901
    Assignment 1 - Exercise 1:
      - T1: Write a C/C++ sequential program and the related routine, namely routine1, that computes the
            element-wise addition of floats and stores the result in an array C. Use a wall-clock time, at
            the program level, that measures the time of the for loop only. The size n should be taken by
            the program as an input parameter.
      - T2: Write a function, routine2, that utilizes implicit parallelism techniques like vectorization or 
            software prefetching to improve performance.
      - T3: Benchmark and compare the performance of the three routines, assuming that n can vary from
            2^4 to 2^22 . Summarize the results in a plot showing on the x-axis the size of the arrays and on
            the y-axis the time of each routine.
      - T4: Write a short document describing the solution implemented, the performance, and comment on
            the results you have obtained.

    Notes:
*/



#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

// Routine 1
void routine1(float *A, float *B, float *C, int n, clock_t *t_loop){
    clock_t t_start, t_stop;
    t_start = clock();
    for (int i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    t_stop = clock();
    *t_loop = t_stop - t_start;
}

int main(int argc, char const *argv[]){
    int n;
    printf("Routine 1\n\n Input size n:\n");
    do{
        scanf("%d", &n);
        if (n < 0){
            printf("Invalid input, please insert a positive integer!\n");
        }
    } while (n < 0);
    
    

    return 0;
}
