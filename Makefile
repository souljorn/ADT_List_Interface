#project 1 make file
#Tim Botelho

list.o: Main_Test.o TestPSLL.o TestSSLL.o TestSDAL.o TestCDAL.o
	g++ -std=c++14 Main_Test.o TestSSLL.o TestPSLL.o TestSDAL.o TestCDAL.o -o tests && ./tests -r console

Main_Test.o: Main_Test.cpp ADT_List.h CDAL.h PSLL.h SDAL.h SSLL.h test.h
	g++ -c -std=c++14 Main_Test.cpp

TestSSLL.o: TestSSLL.cpp SSLL.h
	g++ -c -std=c++14 TestSSLL.cpp

TestPSLL.o: TestPSLL.cpp PSLL.h
	g++ -c -std=c++14 TestPSLL.cpp

TestSDAL.o: TestSDAL.cpp SDAL.h
	g++ -c -std=c++14 TestSDAL.cpp

TestCDAL.o: TestCDAL.cpp CDAL.h
	g++ -c -std=c++14 TestCDAL.cpp

clean:
	find . -name "*.o" -type f
	rm *.o tests *.h.gch
