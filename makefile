comp_test:
	g++ Source/*.cpp tester.cpp -o test.exe -larmadillo -I Include/

run_test:
	./test.exe

test: comp_test run_test
	
run_main:
	./main.exe

comp_Problem_5:
	g++ Source/*.cpp problem5.cpp -o main.exe -larmadillo -I Include/

python_Problem_5:
	python problem5.py

Problem5: comp_Problem_5 run_main python_Problem_5

comp_Problem_6:
	g++ Source/*.cpp problem6.cpp -o main.exe -larmadillo -I Include/

python_Problem_6:
	python problem6.py

Problem6: comp_Problem_6 run_main python_Problem_6

comp_Problem_7_seq:
	g++ Source/*.cpp problem7.cpp -o main.exe -larmadillo -I Include/

comp_Problem_7_parallel:
	g++ Source/*.cpp problem7.cpp -o main.exe -fopenmp -larmadillo -I Include/

time:
	./main.exe

time_seq:
	./main.exe 2
	./main.exe 3
	./main.exe 4
	./main.exe 5
	./main.exe 6
	./main.exe 7
	./main.exe 8
	./main.exe 9
	./main.exe 10

Problem7: comp_Problem_7_seq time comp_Problem_7_parallel time_seq

Problem8:
	g++ Source/*.cpp problem8.cpp -o main.exe -fopenmp -larmadillo -I Include/

Problem8_zoom1_:
	./main.exe 2.25 2.4 10 300000 20
	./main.exe 2.25 2.35 10 300000 40
	./main.exe 2.225 2.325 10 300000 60
	./main.exe 2.15 2.3 15 500000 80
	./main.exe 2.1 2.2 10 1000000 100

Problem8_zoom1: Problem8 Problem8_zoom1_

Problem8_zoom2_:
	./main.exe 2.2 2.4 40 500000 20
	./main.exe 2.28 2.34 10 500000 40
	./main.exe 2.28 2.34 10 500000 60
	./main.exe 2.25 2.31 10 700000 80
	./main.exe 2.25 2.3 10 1500000 100

Problem8_zoom2: Problem8 Problem8_zoom2_

Problem8_zoom3_:
	./main.exe 2.4 2.5 20 500000 20
	./main.exe 2.28 2.4 15 1000000 40
	./main.exe 2.31 2.35 7 700000 80
	./main.exe 2.2 2.25 10 1500000 100
	./main.exe 2.3 2.35 10 1500000 100

Problem8_zoom3: Problem8 Problem8_zoom3_