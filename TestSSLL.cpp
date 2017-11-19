#include "Catch.hpp"
#include "SSLL.h"
#include <stdexcept>

using namespace std;
//***********************SSLL TESTING***********************************
//by Timothy Botelho

//***********************SSLL COPY CONSTRUCTOR TESTING*****************

TEST_CASE( "SSLL_COPY CONSTRUCTOR", "[SSLL_copy_constructor]" ) {
	cop3530::SSLL<char> l;
	l.push_front('A');
	l.push_front('B');
	l.push_front('C');

	SECTION("Testing copy constructor with 3 elements"){
	cop3530::SSLL<char> l_copy(l);
	// cout <<"head add"<< l_copy.head << endl;
	// cout <<"tail add"<< l_copy.tail << endl;
	// cout <<"B add"<< l_copy.head->next << endl;
	// cout <<"C add"<< l_copy.head->next->next << endl;
	REQUIRE(l_copy.length() == 3);
	REQUIRE(l_copy.peek_front() == 'C');
	REQUIRE(l_copy.peek_back() == 'A');
	REQUIRE(l_copy.pop_back() == 'A');
	REQUIRE(l_copy.pop_back() == 'B');
	REQUIRE(l_copy.pop_back() == 'C');
	}
}

//*************************Copy assignment operator*********************
TEST_CASE( "SSLL_COPY_ASSIGNMENT", "[SSLL_copy_assignment]" ) {
	cop3530::SSLL<char> l;
	l.push_front('A');
	l.push_front('B');
	l.push_front('C');

	SECTION("Testing copy constructor with 3 elements"){
	cop3530::SSLL<char> l_copy;
	l_copy = l;

	REQUIRE(l_copy.length() == 3);
	REQUIRE(l_copy.peek_front() == 'C');
	REQUIRE(l_copy.peek_back() == 'A');
	REQUIRE(l_copy.pop_back() == 'A');
	REQUIRE(l_copy.pop_back() == 'B');
	REQUIRE(l_copy.pop_back() == 'C');
	}
}


//*************************ITERATOR TESTING*****************************
TEST_CASE( "Iterating through elements", "[iteration]" ) {
	cop3530::SSLL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}
	SECTION("Iterating through list, testing *, end, begin, = and preincrement operator"){
		l.push_front('A');
		cop3530::SSLL<char>::iterator iter = l.begin();
		REQUIRE(*iter == 'A');
		int count = 0;
		while (iter != l.end()) {
			++count;
			++iter;
		}
		REQUIRE(count == 61);
	}

	SECTION("Non equal and equality operators work, testing postincrement operator"){
			l.push_front('A');
			l.push_front('A');
			cop3530::SSLL<char>::iterator iter = l.begin();
			iter++;
			cop3530::SSLL<char>::iterator iter2 = l.begin();
			REQUIRE(iter != iter2);
			iter2++;
			REQUIRE(iter == iter2);
	}
}


TEST_CASE( "SSLL_Testing constructor", "[SSLL_constructor]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	cop3530::SSLL<char>::iterator iter = l.begin();
	cop3530::SSLL<char>::iterator iter2(iter);
	REQUIRE(*iter2 == 'X');
}

TEST_CASE("SSLL_Test insert", "[SSLL_insert]"){
	cop3530::SSLL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
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
	}

	SECTION("Inserting at pos 2"){
		l.insert('A',2);
	REQUIRE(l.item_at(2) == 'A');
	}
}

//*********************Test Insert********************************
TEST_CASE("SSLL_Test INSERT", "[SSLL_insert]"){
	cop3530::SSLL<char> list;

	SECTION("SSLL_Test inset at 0, [SSLL_insert]"){
		list.insert('A',0);
		REQUIRE(list.peek_front() == 'A');
		REQUIRE(list.length() == 1);
	}
	SECTION("SSLL_Test inset at 1 with length 1, [SSLL_insert]"){
		list.insert('A',0);
		list.insert('B',1);
		REQUIRE(list.peek_back() == 'B');

	}



}

//************************PUSH FRONT TESTING*********************************
TEST_CASE("SSLL_Test push_front", "[SSLL_push_front]"){
	cop3530::SSLL<int> list;

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
TEST_CASE("SSLL_Test length", "[SSLL_length]"){
	cop3530::SSLL<int> list;
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
TEST_CASE("SSLL_Test Clear", "[SSLL_length]"){
	cop3530::SSLL<int> list;
	for(int i = 0 ; i < 5; i++)
	{
		list.push_front(i);
	}

	SECTION("Clear from 5 elements"){
			list.clear();
	 		REQUIRE(list.length() == 0);
	}

}

//***********************TEST PUSH BACK******************************************
TEST_CASE("SSLL_Test PUSH BACK", "[SSLL_push_back]"){
	cop3530::SSLL<int> list;

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
TEST_CASE("SSLL_Test REPLACE", "[SSLL_replace]"){
	cop3530::SSLL<int> list;

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

//********************SSLL REMOVE*****************************
TEST_CASE("SSLL_TEST REMOVE", "[SSLL_REMOVE]"){
		cop3530::SSLL<int> list;

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
		SECTION("Remove an item from 50th position"){
			list.clear();
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}
			int before = list.item_at(49);
			int after = list.item_at(51);
			int item = list.remove(50);
			REQUIRE(list.item_at(50) == after);
			REQUIRE(list.length() == 79);
		}
}

//*********************SSLL POP_BACK********************
TEST_CASE("SSLL_TEST POP_BACK", "[SSLL_pop_back]"){
		cop3530::SSLL<int> list;

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

//*********************SSLL POP_FRONT********************
TEST_CASE("SSLL_TEST POP_FRONT", "[SSLL_pop_front]"){
		cop3530::SSLL<int> list;

		SECTION("POP_FRONT when list is empty"){
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

			REQUIRE(list.pop_front() == 0);
		}

		SECTION("POP_BACK when their is 1 item"){
			list.clear();
			list.push_back(1);
			REQUIRE(list.pop_front() == 1);
			REQUIRE(list.length() == 0);
			REQUIRE(list.head == NULL);
			REQUIRE(list.tail == NULL);
		}
}

//*********************SSLL ITEM_AT********************
TEST_CASE("SSLL_TEST ITEM_AT", "[SSLL_item_at]"){
		cop3530::SSLL<int> list;

		SECTION("item_at when list is empty"){
			bool error = false;

			try{
			list.item_at(5);
			}catch(std::runtime_error &e){
				error = true;
			}
			REQUIRE(error == true);
		}

		SECTION("item_at is out of bounds"){
			bool error = false;
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}
			try{
			list.item_at(90);
			}catch(std::runtime_error &e){
				error = true;
			}
			REQUIRE(error == true);
		}

		SECTION("item_at position 0"){
			list.clear();
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}
			REQUIRE(list.item_at(0) == 0);
		}

		SECTION("item_at position 40"){
			list.clear();
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}
			REQUIRE(list.item_at(40) == 40);
		}
}

template<typename T>
bool equals_function(T &a, T &b){
	 if(a == b)
	 return true;

	return false;
}
//***************SSLL CONTAINS************************
TEST_CASE("SSLL_TEST CONTAINS", "[SSLL_CONTAINS]"){
cop3530::SSLL<char> list;


	SECTION("Testing Contains finds A"){
		list.push_front('A');
		REQUIRE(list.contains('A',equals_function) == true);
	}

}

//***************************Test Contents********************
TEST_CASE("SSLL_TEST CONTENTS", "[SSLL_CONTENTS]"){
cop3530::SSLL<char> list;

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
