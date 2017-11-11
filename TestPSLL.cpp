#include "Catch.hpp"
#include "PSLL.h"
#include <stdexcept>

//***********************SSLL TESTING***********************************
//by Timothy Botelho


//*************************ITERATOR TESTING*****************************
TEST_CASE( "PSLL_ITERATOR_TESTING", "[PSLL_ITERATOR]" ) {
	COP3530::PSLL<char> l;
	l.clear();
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}
	SECTION("Iterating through list, testing *, end, begin, = and preincrement operator"){
		l.push_front('A');
		COP3530::PSLL<char>::iterator iter = l.begin();
		REQUIRE(*iter == 'A');
		int count = 0;
		while (iter != l.end()) {
			++count;
			++iter;
		}
		REQUIRE(count == 61);
	}

	SECTION("Equality operators and testing postincrement"){
			l.push_front('A');
			l.push_front('A');
			COP3530::PSLL<char>::iterator iter = l.begin();
			iter++;
			COP3530::PSLL<char>::iterator iter2 = l.begin();
			REQUIRE(iter != iter2);
			iter2++;
			REQUIRE(iter == iter2);
	}

	SECTION("Test iterator distance"){
			l.clear();

			for (int i = 0; i < 60; i++) {
				l.push_front('X');
			}
			int dist;


			for(auto iter = l.begin(); iter != l.end(); ++iter){
				dist = distance(l.begin(),iter);
			}
			//since distance between 1 element is 0 and distance between 2 is 1
			// so distance = n - 1
			REQUIRE(dist == l.length() - 1);

	}
}

//------------------Test constructor------------------------------
TEST_CASE( "PSLL_Testing constructor", "[PSLL_constructor]" ) {
	COP3530::PSLL<char> l;
	l.push_front('X');
	COP3530::PSLL<char>::iterator iter = l.begin();
	COP3530::PSLL<char>::iterator iter2(iter);
	REQUIRE(*iter2 == 'X');
}

TEST_CASE("PSLL_Test insert", "[PSLL_insert]"){
	COP3530::PSLL<char> l;
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
  REQUIRE(l.item_at(0) == 'B');
	}

	SECTION("Inserting at pos 2"){
		l.insert('A',2);
	REQUIRE(l.item_at(2) == 'A');
	}
}
//
//************************PUSH FRONT TESTING*********************************
TEST_CASE("PSLL_Test push_front", "[PSLL_push_front]"){
	COP3530::PSLL<int> list;

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
TEST_CASE("PSLL_Test length", "[PSLL_length]"){
	COP3530::PSLL<int> list;
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
TEST_CASE("PSLL_Test Clear", "[PSLL_length]"){
	COP3530::PSLL<int> list;
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
TEST_CASE("PSLL_Test PUSH BACK", "[PSLL_push_back]"){
	COP3530::PSLL<int> list;

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
TEST_CASE("PSLL_Test REPLACE", "[PSLL_replace]"){
	COP3530::PSLL<int> list;

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
TEST_CASE("PSLL_TEST REMOVE", "[PSLL_REMOVE]"){
		COP3530::PSLL<int> list;

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
      REQUIRE(item == 50);
      REQUIRE(before == 50);
      REQUIRE(after == 51);
			REQUIRE(list.item_at(50) == after);
			REQUIRE(list.length() == 79);
		}
}

//*********************POP_BACK********************
TEST_CASE("PSLL_TEST POP_BACK", "[PSLL_pop_back]"){
		COP3530::PSLL<int> list;

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

//*********************POP_FRONT********************
TEST_CASE("PSLL_TEST POP_FRONT", "[PSLL_pop_front]"){
		COP3530::PSLL<int> list;

		SECTION("POP_FRONT when list is empty"){
			bool error = false;

			try{
			list.pop_front();
			}catch(std::runtime_error &e){
				error = true;
			}
			REQUIRE(error == true);
		}

		SECTION("POP_Front when their are 15 items"){
			bool error = false;
			for(int i = 0 ; i < 80; i++)
			{
				list.push_back(i);
			}

			REQUIRE(list.pop_front() == 0);
		}

		SECTION("POP_Front when there is 1 item"){
			list.clear();
			list.push_back(1);
			REQUIRE(list.pop_front() == 1);
			REQUIRE(list.length() == 0);
			REQUIRE(list.is_empty());
		}
}

//*********************ITEM_AT********************
TEST_CASE("PSLL_TEST ITEM_AT", "[PSLL_item_at]"){
		COP3530::PSLL<int> list;

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
TEST_CASE("PSLL_TEST CONTAINS", "[PSLL_CONTAINS]"){
COP3530::PSLL<char> list;


	SECTION("Testing Contains finds A"){
		list.push_front('A');
		REQUIRE(list.contains('A',equals_function) == true);
	}
}

//***************PSLL CONTENTS************************
TEST_CASE("PSLL_TEST CONTENTS", "[PSLL_CONTENTS]"){
COP3530::PSLL<char> list;

	SECTION("Test contents of 1 item"){
		list.push_front('A');
		auto r = list.contents();
		REQUIRE(r[0] == 'A');
	}
}
