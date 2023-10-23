# Introduction to parallel computing - Homework 1 - Exercise 1

## Compiling and running the code
After download this repository on the UniTN cluster, we must request for an interactive session with the following command:
```bash
qsub -I -q short_cpuQ
```
so, after the request is accepted, we can load the module for the Intel compiler with the following command:
```bash
module load gcc91
```

Then, we can compile the code with the following command:
```bash
gcc [-DN=<Arrays_dimension>] main.c -O3 -ftree-vectorize [-ftree-vectorizer-verbose=2]

```
where N is the dimension of the arrays. If N is not specified, the program will ask it later, and the flag `-ftree-vectorizer-verbose=2` is optional and it is used to print the vectorization report.
```bash
./a.out
```

