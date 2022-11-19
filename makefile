comp_test:
	g++ Source/*.cpp tester.cpp -o test.exe -larmadillo -I Include/

run_test:
	./test.exe

test: comp_test run_test
	
run_main:
	./main.exe

comp_Problem_5:
	g++ Source/*.cpp problem5.cpp -o main.exe -larmadillo -I Include/

Problem5: comp_Problem_5 run_main

comp_Problem_6:
	g++ Source/*.cpp problem6.cpp -o main.exe -larmadillo -I Include/

Problem6: comp_Problem_6 run_main
