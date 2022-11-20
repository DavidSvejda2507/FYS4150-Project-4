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
