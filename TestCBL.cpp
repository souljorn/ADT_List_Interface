#include "Catch.hpp"
#include "CBL.h"
#include <stdexcept>

// //***********************CBL TESTING***********************************
// //by Timothy Botelho
//
// //***********************Constructor**********************************
// TEST_CASE( "CBL_Testing constructor", "[CBL_constructor]" ) {
// 	cop3530::CBL<char> l;
// 	l.push_front('X');
// 	cop3530::CBL<char>::iterator iter = l.begin();
// 	cop3530::CBL<char>::iterator iter2(iter);
// 	REQUIRE(*iter2 == 'X');
// }
//************************INSERT****************************************
TEST_CASE("CBL_Test insert", "[CBL_insert]"){
  cop3530::CBL<char> l;
  for (int i = 0; i < 10; i++) {
    l.push_front('X');
  }

  SECTION("Testing length "){
    REQUIRE(l.length() == 10);
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

//************************INSERT with larger numbers****************************************
TEST_CASE("CBL_Test insert2", "[CBL_insert2]"){
  cop3530::CBL<int> l;
  for (int i = 0; i < 60; i++) {
    l.push_front(i);
  }

  SECTION("Testing head and tail"){
    REQUIRE(l.peek_front() == 59);
    REQUIRE(l.peek_back() == 0);
    REQUIRE(l.length() == 60);
  }

  SECTION("testing inserting at front and back"){

    l.insert(77, 0);
    l.insert(66, l.length()-1);

    REQUIRE(l.length() == 62);
    REQUIRE(l.peek_front() == 77);
    REQUIRE(l.peek_back() == 66);
  }

  SECTION("Inserting in middle using shift"){
    l.insert(99,4);
    //l.print(cout);
    REQUIRE(l.length() == 61);
    REQUIRE(l.item_at(4) == 99);
  }
}

//************************PUSH FRONT TESTING*********************************
TEST_CASE("CBL_Test push_front", "[CBL_push_front]"){
	cop3530::CBL<int> list;

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
TEST_CASE("CBL_Test length", "[CBL_length]"){
	cop3530::CBL<int> list;
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
TEST_CASE("CBL_Test Clear", "[CBL_length]"){
	cop3530::CBL<int> list;
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
TEST_CASE("CBL_Test PUSH BACK", "[CBL_push_back]"){
	cop3530::CBL<int> list;

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

}

//***********************TEST REPLACE******************************************
TEST_CASE("CBL_Test REPLACE", "[CBL_replace]"){
	cop3530::CBL<int> list;

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
TEST_CASE("CBL_TEST REMOVE", "[CBL_REMOVE]"){
		cop3530::CBL<int> list;

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
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}
			int before = list.item_at(50);
			int after = list.item_at(51);
			int item = list.remove(50);
      //list.print(cout);
      REQUIRE(item == 50);
      REQUIRE(before == 50);
      REQUIRE(after == 51);
			REQUIRE(list.item_at(50) == after);
			REQUIRE(list.length() == 79);
		}

    SECTION("Remove an item from 76th position"){
			list.clear();
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}
			int before = list.item_at(75);
			int after = list.item_at(77);
			int item = list.remove(76);
      //list.print(cout);
      REQUIRE(item == 76);
      REQUIRE(before == 75);
      REQUIRE(after == 77);
			REQUIRE(list.item_at(76) == after);
			REQUIRE(list.length() == 79);
		}
}

//*********************POP_BACK********************
TEST_CASE("CBL_TEST POP_BACK", "[CBL_pop_back]"){
		cop3530::CBL<int> list;

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
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
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

//***************CBL CONTAINS************************
TEST_CASE("CBL_TEST CONTAINS", "[CBL_CONTAINS]"){
cop3530::CBL<char> list;

	SECTION("Testing Contains A"){
		list.push_front('A');
    //cout << list.peek_front() << endl;
		REQUIRE(list.contains('A',equals_function) == true);
	}
}

//***************************Test Contents********************
TEST_CASE("CBL_TEST CONTENTS", "[CBL_CONTENTS]"){
cop3530::CBL<char> list;

  SECTION("Testing Contents to Array"){
    list.push_front('D');
    list.push_front('A');
    list.push_front('T');
    list.push_front('A');
    list.push_front('S');
    list.push_front('T');
    list.push_front('R');
    list.push_front('U');
    list.push_front('C');
    list.push_front('T');
    list.push_front('U');
    list.push_front('R');
    list.push_front('E');
    list.push_front('S');

    REQUIRE(list.item_at(13) == 'D');
    REQUIRE(list.item_at(12) == 'A');
    REQUIRE(list.item_at(11) == 'T');
    REQUIRE(list.item_at(10) == 'A');
    REQUIRE(list.item_at(9) == 'S');
    REQUIRE(list.item_at(8) == 'T');
    REQUIRE(list.item_at(7) == 'R');
    REQUIRE(list.item_at(6) == 'U');
    REQUIRE(list.item_at(5) == 'C');
    REQUIRE(list.item_at(4) == 'T');
    REQUIRE(list.item_at(3) == 'U');
    REQUIRE(list.item_at(2) == 'R');
    REQUIRE(list.item_at(1) == 'E');
    REQUIRE(list.item_at(0) == 'S');
  }
}



// //*************************ITERATOR TESTING*****************************
// TEST_CASE( "CBL_Iterator TESTING", "[iteration]" ) {
// 	cop3530::CBL<char> l;
// 	for (int i = 0; i < 60; i++) {
// 		l.push_front('X');
// 	}
// 	SECTION("Iterating through list, testing *, end, begin, = and preincrement operator"){
// 		l.push_front('A');
// 		cop3530::CBL<char>::iterator iter = l.begin();
// 		REQUIRE(*iter == 'A');
// 		int count = 0;
// 		while (iter != l.end()) {
// 			++count;
// 			++iter;
// 		}
// 		REQUIRE(count == 61);
// 	}
//
// 	SECTION("Non equal and equality operators work, testing postincrement operator"){
// 			l.push_front('A');
// 			l.push_front('A');
// 			cop3530::CBL<char>::iterator iter = l.begin();
// 			iter++;
// 			cop3530::CBL<char>::iterator iter2 = l.begin();
// 			REQUIRE(iter != iter2);
// 			iter2++;
// 			REQUIRE(iter == iter2);
// 	}
// 	SECTION("Range based for loop"){
// 		int size = 0;
// 		for(auto it = l.begin(); it != l.end(); ++it)
// 		{
// 			size++;
// 		}
// 		REQUIRE(size == 60);
// 	}
// }
