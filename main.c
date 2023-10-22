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
#include <limits.h>

// Random float generator
float randomF(int min, int max, int prec){ 
  prec = 10 * prec; 
  return (rand()%(max * prec - min * prec + 1) + min * prec) / (float)prec; 
} 

// Routine 1
clock_t routine1(float *A, float *B, float *C, int n){
    clock_t t_start, t_stop;
    unsigned long long int i;

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
    printf("Routine 1\n\nInput size n:\n");
    do{
        scanf("%d", &n);
        if (n < 0){
            printf("\nInvalid input, please insert a positive integer!\n");
        }
    } while (n < 0);
#else
    n = N;
#endif
    // Allocate memory for arrays
    float a[n], b[n], c[n];
    FILE *fp;
    fp = fopen("T1-results.csv", "w");
    if (fp != NULL){
        fprintf(fp, "job,n,wall_time\n");
        int n_times;
        for (n_times = 0; n_times < 10; ++n_times){
            printf("\n\nJob %d\nInitializing arrays...", n_times);
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
            printf("\n\nLoop time: %.6f ms\n", time);
            fprintf(fp, "%d,%d,%.6f\n", n_times, n, time);
        }
    }else{
        printf("Error opening file!\n");
    }
    fclose(fp);
    return 0;
}
