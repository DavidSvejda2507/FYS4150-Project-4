# FYS4150-Project-4

Compile and run the test using
```bash
make test
```

## Problem 5:
```bash
make Problem5
```

## Problem 6:
```bash
make Problem6
```

## Problem 7:
```bash
make Problem7
```
This will run a test run with L=100 and n = 1e5 for up to 10 parallel processes
It took me about 1300 seconds or 20 min to run

## Problem 7:
```bash
make Problem8
./main.exe
```
or
```bash
make Problem8
./main.exe <T_min (double)> <T_max(double)> <n_T(int)> <n(int)> [<L(int)>]
```
By default this will run with 2.1 2.4 20 100.000. The results will be appended to the output file.