# Introduction to parallel computing - Homework 1 - Exercise 1

## Compiling and running the code
After download this repository on the UniTN cluster, we must request for an interactive session with the following command:
```bash
qsub -I -q short_cpuQ
```
so, after the request is accepted, we can load the module for the Intel compiler with the following command (if it is not already loaded):
```bash
module load gcc91
```

Then, we can compile the code with the following command:
```bash
gcc [-DN=<Arrays_dimension>] main.c -DNOTES=\"<what_kind_of_notes_you_want>\"

```
where N is the dimension of the arrays. If N is not specified, the program will ask it later.

If we want to compile the code with vectorization, we can use the following command:
```bash
gcc [-DN=<Arrays_dimension>] main.c -DNOTES=\"<what_kind_of_notes_you_want>\" -O3 -mavx [-ftree-vectorizer-verbose=2]
```
The flag `-ftree-vectorizer-verbose=2` is optional and it is used to print the vectorization report.

Finally, we can run the code with the following command,

```bash
./a.out
```
## Gettig the results and plotting them
After the execution of the program it's possible to see the results on a file called `Benchmark-resoults.csv` and this file can be also used to plot the results with the python script `chart.py`.

>Note, when the program is executed, another file called `B-resoults.csv` will be generated, but this file contains only the data of the last run! 

In order to plot the results, we can use the following command:
```bash
module add python-3.8.13

#If there isn't the libraries, we can install them with the following command:
pip3 install matplotlib numpy pandas

#or just run the script
python3 chart.py
```