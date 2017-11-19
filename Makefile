
#project 1 make file
#Tim Botelho

#list.o: Main_Test.o TestPSLL.o TestSSLL.o TestSDAL.o TestCDAL.o
#       g++ -std=c++14 Main_Test.o TestPSLL.o TestSSLL.o TestSDAL.o TestCDAL.o -o tests

list.o: SSLL_TEST.o PSLL_TEST.o SDAL_TEST.o CDAL_TEST.o CBL_TEST.o

Main_Test.o: Main_Test.cpp List.h CDAL.h PSLL.h SDAL.h SSLL.h CBL.h
	g++ -c -std=c++14 Main_Test.cpp

TestSSLL.o: TestSSLL.cpp SSLL.h
	g++ -c -std=c++14 TestSSLL.cpp

TestPSLL.o: TestPSLL.cpp PSLL.h
	g++ -c -std=c++14 TestPSLL.cpp

TestSDAL.o: TestSDAL.cpp SDAL.h
	g++ -c -std=c++14 TestSDAL.cpp

TestCDAL.o: TestCDAL.cpp CDAL.h
	g++ -c -std=c++14 TestCDAL.cpp

TestCBL.o: TestCBL.cpp CBL.h
  g++ -c -std=c++14 TestCBL.cpp

SSLL_TEST.o: Main_Test.o TestSSLL.o
	g++ -std=c++14 Main_Test.o TestSSLL.o -o test1

PSLL_TEST.o: Main_Test.o TestPSLL.o
	g++ -std=c++14 Main_Test.o TestPSLL.o -o test2

SDAL_TEST.o: Main_Test.o TestSDAL.o
	g++ -std=c++14 Main_Test.o TestSDAL.o -o test3

CDAL_TEST.o: Main_Test.o TestCDAL.o
	g++ -std=c++14 Main_Test.o TestCDAL.o -o test4

CBL_TEST.o: Main_Test.o TestCBL.o
	g++ -std=c++14 Main_Test.o TestCBL.o -o test5

run_tests:
	./test1
	./test2
	./test3
	./test4
	./test5

clean:
	find . -name "*.o" -type f
	rm *.o test1 test2 test3 test4 test5
