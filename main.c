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

// Random float generator
float randomF(int min, int max, int prec){ 
  prec = 10 * prec; 
  return (rand() % (max * prec - min * prec + 1) + min * prec) / (float)prec; 
}

// Routine 1
clock_t routine1(float *A, float *B, float *C, int n){
    clock_t t_start, t_stop;
    int i;
    t_start = clock();
    for (i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    t_stop = clock();
    return t_stop - t_start;
}

//Routine 2
clock_t routine2(float *A, float *B, float * __restrict C, int n){
    clock_t t_start, t_stop;
    int i;
    t_start = clock();
    for (i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    t_stop = clock();
    return t_stop - t_start;
}

int main(int argc, char const *argv[]){
    int n;
    int i;
    
#ifndef N
    printf("\n Input size n:\n");
    do{
        scanf("%d", &n);
        if (n < 0){
            printf("Invalid input, please insert a positive integer!\n");
        }
    } while (n < 0);
#else
    n = N;
#endif

    // Allocate arrays
    float a[n], b[n], c[n];

    // Initialize arrays with random values
    srand(time(NULL));
    for (i = 0; i < n; i++){
        a[i] = randomF(0, 100, 3);
        b[i] = randomF(0, 100, 3);
    }

    // Print some values
    printf("Printing some values of the arrays:\n");
    for (i = 0; i < 10; i++){
        int j = rand() % n;
        printf("a[%d] = %f\tb[%d] = %f\n", j, a[j], j, b[j]);
    }
    printf("call routine1\n");
    // Call routine 1
    clock_t wall_time;
    wall_time = routine1(a, b, c, n);

    // Print results
    double time = (double)wall_time/((double)CLOCKS_PER_SEC);
    printf("\n\nRoutine 1 loop time: %.6f ms\n", time);

    // Call routine 2
    wall_time = routine2(a, b, c, n);
    time = (double)wall_time/((double)CLOCKS_PER_SEC);
    printf("\n\nRoutine 2 loop time: %.6f ms\n", time);
    
    return 0;
}
