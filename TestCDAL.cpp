#include "Catch.hpp"
#include "CDAL.h"
#include <stdexcept>

//***********************CDAL TESTING***********************************
//by Timothy Botelho

TEST_CASE("CDAL_Test insert", "[CDAL_insert]"){
	COP3530::CDAL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}

  SECTION("Testing length "){
    REQUIRE(l.length() == 60);
  }

	SECTION("Inserting out of bounds"){bool caught = false;
			bool error;
			try {
	 			l.insert('A',61);
			} catch (std::runtime_error &le) {
 				error = true;
	 		}
	 		REQUIRE(error == true);
	}

	SECTION("Inserting at pos 0"){
		l.insert('B',0);
	REQUIRE(l.peek_front() == 'B');
  REQUIRE(l.item_at(0) == 'B');
	}

	SECTION("Inserting at pos 2"){
		l.insert('A',2);
	REQUIRE(l.item_at(2) == 'A');
	}
}

//************************PUSH FRONT TESTING*********************************
TEST_CASE("CDAL_Test push_front", "[CDAL_push_front]"){
	COP3530::CDAL<int> list;

	SECTION("Push Front When Empty"){
			list.push_front(77);
	 		REQUIRE(list.peek_front() == 77);
	}

	SECTION("Push Front 5 Items"){
		for(int i = 0 ; i < 5; i++)
		{
			list.push_front(i);
		}
	REQUIRE(list.peek_front() == 4);
	}
}

//***********************TEST LENGTH******************************************
TEST_CASE("CDAL_Test length", "[CDAL_length]"){
	COP3530::CDAL<int> list;
	list.clear();

	SECTION("Length when empty"){

	 		REQUIRE(list.length() == 0);
	}

	SECTION("Test length for 5 items"){
		for(int i = 0 ; i < 5; i++)
		{
			list.push_front(i);
		}
	REQUIRE(list.length() == 5);
	}
}

//***********************TEST CLEAR******************************************
TEST_CASE("CDAL_Test Clear", "[CDAL_length]"){
	COP3530::CDAL<int> list;
	for(int i = 0 ; i < 5; i++)
	{
		list.push_front(i);
	}

	SECTION("Clear from 5 elements"){
			list.clear();
	 		REQUIRE(list.length() == 0);
	}

}

// //***********************TEST PUSH BACK******************************************
TEST_CASE("CDAL_Test PUSH BACK", "[CDAL_push_back]"){
	COP3530::CDAL<int> list;

	SECTION("When Empty"){
			list.push_back(7);
	 		REQUIRE(list.length() == 1);
			REQUIRE(list.peek_back() == 7);
	}

	SECTION("Push 5 elements"){
		for(int i = 0 ; i < 5; i++)
		{
			list.push_back(i);
		}
	 		REQUIRE(list.length() == 5);
			REQUIRE(list.peek_back() == 4);
	}

	SECTION("Push 5 elements"){
		for(int i = 0 ; i <60; i++)
		{
			list.push_back(i);
		}
		//list.print_cur_node(list.find_cur_node(1));
		//list.print_cur_node(list.find_cur_node(55));
	 	REQUIRE(list.length() == 60);
		REQUIRE(list.peek_back() == 59);
	}

}

//***********************TEST REPLACE******************************************
TEST_CASE("CDAL_Test REPLACE", "[CDAL_replace]"){
	COP3530::CDAL<int> list;

	SECTION("Replacing item when list is empty"){
		bool caught = false;
				bool error;
				try {
					list.replace(9,0);
				} catch (std::runtime_error &le) {
					error = true;
				}
				REQUIRE(error == true);
		}

	SECTION("Replace an item out of bounds"){
		for(int i = 0 ; i < 5; i++)
		{
			list.push_back(i);
		}
		bool error2 = false;
		try{
			list.replace(99,6);
		}catch(std::runtime_error &le){
			error2 = true;
		}
	 		REQUIRE(error2 == true);
	}

	SECTION("Replace at pos 0"){
		list.clear();
		for(int i = 0 ; i < 80; i++)
		{
			list.push_back(i);
		}
		list.replace(99,0);
		REQUIRE(list.peek_front() ==99);
	}
}

//********************REMOVE*****************************
TEST_CASE("CDAL_TEST REMOVE", "[CDAL_REMOVE]"){
		COP3530::CDAL<int> list;

	SECTION("Remove an item from an empty list"){
		list.clear();
		bool error = false;
		try{
		list.remove(55);
		}catch(std::runtime_error &e){
			error = true;
		}
		REQUIRE(error == true);
	}

	SECTION("Remove an item from out of bounds"){
		list.clear();
		for(int i = 0 ; i < 80; i++)
		{
			list.push_back(i);
		}
		bool error = false;

		try{
		list.remove(99);
		}catch(std::runtime_error &e){
			error = true;
		}
		REQUIRE(error == true);
  }

  SECTION("Remove an item from 1st position with length == 1"){
    list.clear();
    for(int i = 0 ; i < 1; i++)
    {
      list.push_back(i);
    }
    int item = list.remove(0);
    REQUIRE(item == 0);
    REQUIRE(list.length() == 0);
  }

		SECTION("Remove an item from 50th position"){
			list.clear();
			for(int i = 79 ; i >= 0; i--)
			{
				list.push_front(i);
			}

			int before = list.item_at(49);
			int after = list.item_at(51);

			int item = list.remove(50);
			//list.print_cur_node(list.find_cur_node(1));
			//list.print_cur_node(list.find_cur_node(55));
			REQUIRE(item == 50);
      REQUIRE(before == 49);
      REQUIRE(after == 51);
			REQUIRE(list.item_at(50) == after);
			REQUIRE(list.length() == 79);
		}
}

//*********************POP_BACK********************
TEST_CASE("CDAL_TEST POP_BACK", "[CDAL_pop_back]"){
		COP3530::CDAL<int> list;

		SECTION("POP_BACK when list is empty"){
			bool error = false;

			try{
			list.pop_back();
			}catch(std::runtime_error &e){
				error = true;
			}
			REQUIRE(error == true);
		}

		SECTION("POP_BACK when their are 15 items"){
			bool error = false;
			for(int i = 79 ; i >= 0; i--)
			{
				list.push_front(i);
			}

			REQUIRE(list.pop_back() == 79);
		}

}

template<typename T>
bool equals_function(T &a, T &b){
	 if(a == b)
	 return true;

	return false;
}

//***************CDAL CONTAINS************************
TEST_CASE("CDAL_TEST CONTAINS", "[CDAL_CONTAINS]"){
COP3530::CDAL<char> list;

	SECTION("Testing Contains finds A"){
		list.push_front('A');
		REQUIRE(list.contains('A',equals_function) == true);
	}
}
//***************CDAL PRINT/CONTENTS************************
TEST_CASE("CDAL_TEST PRINT", "[CDAL_PRINT]"){
COP3530::CDAL<char> list;

	SECTION("Test Print of 20 items"){
		for(int i = 37; i < 57; i++){
		list.push_front((char)i);
		}

		char * arr = list.contents();
		//list.print(std::cout);
		REQUIRE(list.length() == 20);
		REQUIRE(list.peek_front() == (char)56);
		REQUIRE(list.peek_back() == (char)37);
	}
}

// // //*************************ITERATOR TESTING*****************************
// // TEST_CASE( "Iterating through elements", "[iteration]" ) {
// // 	COP3530::CDAL<char> l;
// // 	for (int i = 0; i < 60; i++) {
// // 		l.push_front('X');
// // 	}
// // 	SECTION("Iterating through list, testing *, end, begin, = and preincrement operator"){
// // 		l.push_front('A');
// // 		COP3530::CDAL<char>::iterator iter = l.begin();
// // 		REQUIRE(*iter == 'A');
// // 		int count = 0;
// // 		while (iter != l.end()) {
// // 			++count;
// // 			++iter;
// // 		}
// // 		REQUIRE(count == 61);
// // 	}
// //
// // 	SECTION("Non equal and equality operators work, testing postincrement operator"){
// // 			l.push_front('A');
// // 			l.push_front('A');
// // 			COP3530::CDAL<char>::iterator iter = l.begin();
// // 			iter++;
// // 			COP3530::CDAL<char>::iterator iter2 = l.begin();
// // 			REQUIRE(iter != iter2);
// // 			iter2++;
// // 			REQUIRE(iter == iter2);
// // 	}
// // }
//
//
// // TEST_CASE( "CDAL_Testing constructor", "[CDAL_constructor]" ) {
// // 	COP3530::CDAL<char> l;
// // 	l.push_front('X');
// // 	//COP3530::CDAL<char>::iterator iter = l.begin();
// // 	//COP3530::CDAL<char>::iterator iter2(iter);
// // 	REQUIRE(*iter2 == 'X');
// // }
