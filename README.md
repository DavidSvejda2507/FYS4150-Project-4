# FYS4150-Project-4

## Dependencies
Python packages used:
numpy
matplotlib.pyplot
scipy

can be installed with
```bash
conda install numpy matplotlib scipy
```
or
```bash
pip install numpy matplotlib scipy
```


## Usage
Compile and run the test using
```bash
make test
```

### Problem 5:
```bash
make Problem5
```

### Problem 6:
```bash
make Problem6
```

### Problem 7:
```bash
make Problem7
```
This will run a test run with L=100 and n = 1e5 for up to 10 parallel processes
It took me about 1300 seconds or 20 min to run.
The output to the terminal should allow you to choose a suitable number of loops to split the computations over
If the optimum is not 8 you'll have to change the source code.

### Problem 8:
```bash
make Problem8
./main.exe
```
or
```bash
make Problem8
./main.exe <T_min (double)> <T_max(double)> <n_T(int)> <n(int)> [<L(int)>]
```
By default this will run with 2.1 2.4 20 100.000. The results will be appended to the log file.

### Problem 9:
```bash
python problem8.py
```
will remake the images using all of the results in Data/Problem8/log.txt
Running simulations using problem8.cpp will add lines to the log file, which will change the output, hopefully not by much