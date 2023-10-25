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
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>
#include <stdint.h>

#ifndef NOTES
    #define NOTES ""
#endif

// Random float generator
float randomF(int min, int max, int prec){ 
  prec = 10 * prec; 
  return (rand() % (max * prec - min * prec + 1) + min * prec) / (float)prec; 
}

// Routine 1
uint64_t routine1(float *A, float *B, float *C, int n){
    struct timespec start, end;
    //do stuff

    int i;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    //return t_stop - t_start;
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}

//Routine 2
uint64_t routine2(float *A, float *B, float * __restrict C, int n){
    struct timespec start, end;
    int i;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}

int main(int argc, char const *argv[]){
    uint64_t n;
    uint64_t i;
    
    //Retriving some info about the machine
    char hostbuffer[256];
    int hostname;
 
    // retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1) {
        printf("Error when getting hostname\n");
    }

    FILE *f_resoults;
    FILE *fp;
    fp = fopen("B-resoults.csv", "w");
    
    f_resoults = fopen("Benchmark-resoults.csv", "a");

    if (fp != NULL){
        fprintf(fp, "job,hostname,n,wall_time_serial,wall_time_vectorized\n");
    }
    if (f_resoults == NULL){
        printf("Error opening resoults.csv file!\n");
    }
    
    for (n = 16; n <= 4194304; n *= 2){
        // Allocate memory for arrays
        float a[n], b[n], c[n];

        printf("\n\nJob %d\nInitializing arrays...\n", n);
        // Initialize arrays with random values
        srand(time(NULL));
        for (i = 0; i < n; i++){
            a[i] = randomF(0, 1000, 3);
            b[i] = randomF(0, 1000, 3);
        }

        // Print some values [ONLY FOR DEBUG]
        // printf("Printing some values of the arrays:\n");
        // for (i = 0; i < 10; i++){
        //     int j = rand() % n;
        //     printf("a[%d] = %f\tb[%d] = %f\n", j, a[j], j, b[j]);
        // }
        // printf("call routine1\n");
        // Call routine 1
        clock_t wall_time;
        printf("\ncall routine1\n");
        wall_time = routine1(a, b, c, n);

        // Print results
        double time1 = (double)wall_time/((double)CLOCKS_PER_SEC);
        printf("Loop time: %.6f s", time1);

        // Call routine 2
        printf("\ncall routine2\n");
        wall_time = routine2(a, b, c, n);

        // Print results
        double time2 = (double)wall_time/((double)CLOCKS_PER_SEC);
        printf("Loop time: %.6f s\n", time2);
        if (fp != NULL)
            fprintf(fp, "%s,%d,%.6f,%.6f\n", hostbuffer, n, time1, time2);
        if (f_resoults != NULL)
            fprintf(f_resoults, "%s,%d,%.6f,%.6f,%s\n", hostbuffer, n, time1, time2, NOTES);
    }
    fclose(fp);
    return 0;
}
