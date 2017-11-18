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


//***************SSLL CONTENTS************************
//***************SSLL CONTENTS************************
// TEST_CASE( "SSLL_Testing arrow operator", "[SSLL_arrow_operator]" ) {
// 	cop3530::SSLL<Employee> l;
// 	Employee emp;
// 	l.push_front(emp);
// 	cop3530::SSLL<Employee>::iterator iter = l.begin();
// 	REQUIRE(iter->data->salary == 0);
//
// 	SECTION("Throws exception when trying to use with a null node") {
// 		cop3530::SSLL<Employee>::iterator iter2;
// 		bool caught = false;
// 		try {
// 			iter2->data->salary;
// 		} catch (std::logic_error &le) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }

// TEST_CASE( "SSLL_Iterating through elements with const iterator", "[SSLL_const_iteration]" ) {
// 	cop3530::SSLL<char> l;
// 	for (int i = 0; i < 60; i++) {
// 		l.push_front('X');
// 	}
// 	l.push_front('A');
// 	const cop3530::SSLL<char> const_list = l;
// 	SECTION("Iterating through list, testing *, end, begin, =, and preincrement operator"){
// 		cop3530::SSLL<char>::const_iterator iter = const_list.begin();
// 		REQUIRE(*iter == 'A');
// 		int count = 0;
// 		while (iter != const_list.end()) {
// 			++count;
// 			++iter;
// 		}
// 		REQUIRE(count == 61);
// 	}
//
// 	SECTION("Non equal and equality operators work"){
// 			cop3530::SSLL<char>::const_iterator iter = const_list.begin();
// 			iter++;
// 			cop3530::SSLL<char>::const_iterator iter2 = const_list.begin();
// 			REQUIRE(iter != iter2);
// 			iter2++;
// 			REQUIRE(iter == iter2);
// 	}
// }
//
// TEST_CASE( "SSLL_Testing const explicit constructor and exception caught with dereference operator when null", "[SSLL_explicit_const]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	const cop3530::SSLL<char> const_list = l;
// 	cop3530::SSLL<char>::const_iterator iter;
// 	bool caught = false;
// 	try {
// 		*iter;
// 	} catch(std::logic_error &le) {
// 		caught = true;
// 	}
// 	REQUIRE(caught == true);
// }
//
// TEST_CASE( "SSLL_Testing constructor const", "[SSLL_const_constructor]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	const cop3530::SSLL<char> const_list = l;
// 	cop3530::SSLL<char>::const_iterator iter = const_list.begin();
// 	cop3530::SSLL<char>::const_iterator iter2(iter);
//
// 	REQUIRE(*iter2 == 'X');
// }
//
// TEST_CASE( "SSLL_Testing arrow operator with const iter", "[SSLL_arrow_operator_const_iter]" ) {
// 	cop3530::SSLL<Student> l;
// 	Student student;
// 	l.push_front(student);
// 	const cop3530::SSLL<Student> const_list = l;
// 	cop3530::SSLL<Student>::const_iterator iter = const_list.begin();
// 	REQUIRE(iter->grade == 0);
//
// 	SECTION("Throws exception when trying to use with a null node") {
// 		cop3530::SSLL<Student>::const_iterator iter2;
// 		bool caught = false;
// 		try {
// 			iter2->grade;
// 		} catch (std::logic_error &le) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE("SSLL_Const iter-Testing increment operators for exceptions", "[SSLL_cont_incrementing]") {
// 	cop3530::SSLL<char> l;
// 	l.push_front('A');
// 	l.push_front('B');
// 	const cop3530::SSLL<char> const_list = l;
// 	SECTION("Preincrement operator throws exception when the node is null") {
// 		cop3530::SSLL<char>::const_iterator iter = const_list.begin();
// 		++iter;
// 		++iter;
// 		bool caught = false;
// 		try {
// 			++iter;
// 		} catch(std::logic_error &le) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// 	SECTION("Postincrement operator throws exception when the node is null") {
// 		cop3530::SSLL<char>::const_iterator iter = const_list.begin();
// 		++iter;
// 		++iter;
// 		bool caught = false;
// 		try {
// 			iter++;
// 		} catch (std::logic_error &le) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE( "Replacing elements", "[SSLL_replace]") {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
//
// 	SECTION("Catch exception when the list is empty and replace is called") {
// 		bool caught = false;
// 		l.pop_back();
// 		try {
// 			l.replace('A', 0);
// 		} catch(std::out_of_range& oor) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
//
// 	SECTION("Catch exception when replace is called on an invalid element") {
// 		bool caught = false;
// 		try {
// 			l.replace('A', 1);
// 		} catch (std::out_of_range& oor) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
//
// 	SECTION("Returns the original element when an element is replaced") {
// 		REQUIRE(l.replace('A', 0) == 'X');
// 	}
//
// 	SECTION("Replaces the only element if the size is 1") {
// 		l.replace('A', 0);
// 		REQUIRE(l.pop_back() == 'A');
// 	}
//
// 	SECTION("Correctly replaces the head element when there is more than 1 element") {
// 		l.push_front('X');
// 		l.replace('A', 0);
// 		REQUIRE(l.pop_front() == 'A');
// 	}
//
// 	SECTION("Correctly replaces the tail element when there is more than 1 element") {
// 		l.push_front('X');
// 		l.replace('A', 1);
// 		REQUIRE(l.pop_back() == 'A');
// 	}
// }
//
// TEST_CASE( "Inserting elements", "[SSLL_insert]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
//
// 	SECTION("Allow inserting anywhere in the list") {
// 		l.push_front('X');
// 		l.push_front('X');
// 		l.insert('A', 1);
// 		REQUIRE(l.item_at(1) == 'A');
// 	}
//
// 	SECTION("Inserting at 1 past the last index occupied") {
// 		l.insert('A', 1);
// 		REQUIRE(l.item_at(1) == 'A');
// 	}
//
// 	SECTION("Inserting at the head") {
// 		l.insert('A', 0);
// 		REQUIRE(l.item_at(0) == 'A');
// 		REQUIRE(l.item_at(1) == 'X');
// 	}
//
// 	SECTION("Inserting at more than 1 past the last index occupied") {
// 		bool caught = false;
// 		try {
// 			l.insert('A', 2);
// 		} catch(std::out_of_range& oor) {
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE( "Pushing Elements to front", "[SSLL_push_front]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Pushing an element") {
// 		l.push_front('A');
// 		REQUIRE(l.item_at(0) == 'A');
// 		REQUIRE(l.item_at(1) == 'X');
// 	}
// 	SECTION("Pushing onto empty list") {
// 		l.pop_front();
// 		l.push_front('A');
// 		REQUIRE(l.item_at(0) == 'A');
// 		REQUIRE(l.size() == 1);
// 	}
// }
//
// TEST_CASE( "Pushing Elements to back", "[SSLL_push_back]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Pushing an element") {
// 		l.push_back('A');
// 		REQUIRE(l.item_at(1) == 'A');
// 		REQUIRE(l.item_at(0) == 'X');
// 	}
// 	SECTION("Pushing onto empty list") {
// 		l.pop_front();
// 		l.push_back('A');
// 		REQUIRE(l.item_at(0) == 'A');
// 		REQUIRE(l.size() == 1);
// 	}
// }
//
// TEST_CASE( "Popping elements from front", "[SSLL_pop_front]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Popping an element") {
// 		l.push_front('A');
// 		REQUIRE(l.pop_front() == 'A');
// 		REQUIRE(l.size() == 1);
// 		REQUIRE(l.item_at(0) == 'X');
// 	}
// 	SECTION("Popping head element") {
// 		REQUIRE(l.pop_front() == 'X');
// 		REQUIRE(l.size() == 0);
// 	}
//
// 	SECTION("Popping from empty list") {
// 		bool caught = false;
// 		l.pop_front();
// 		try {
// 			l.pop_front();
// 		} catch (std::out_of_range& oor){
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE( "Popping elements from back", "[SSLL_pop_back]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Popping an element") {
// 		l.push_front('A');
// 		REQUIRE(l.pop_back() == 'X');
// 		REQUIRE(l.size() == 1);
// 	}
// 	SECTION("Popping head element") {
// 		REQUIRE(l.pop_back() == 'X');
// 		REQUIRE(l.size() == 0);
// 	}
//
// 	SECTION("Popping from empty list") {
// 		bool caught = false;
// 		l.pop_back();
// 		try {
// 			l.pop_back();
// 		} catch (std::out_of_range& oor){
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE( "Removing an element at a position", "[SSLL_remove]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Removing an element") {
// 		l.push_front('A');
// 		l.push_front('A');
// 		REQUIRE(l.remove(0) == 'A');
// 		REQUIRE(l.item_at(0) == 'A');
// 		REQUIRE(l.item_at(1) == 'X');
// 		REQUIRE(l.size() == 2);
// 	}
// 	SECTION("Removing head element") {
// 		REQUIRE(l.remove(0) == 'X');
// 		REQUIRE(l.size() == 0);
// 	}
//
// 	SECTION("Removing from empty list") {
// 		bool caught = false;
// 		l.remove(0);
// 		try {
// 			l.remove(0);
// 		} catch (std::out_of_range& oor){
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
//
// 	SECTION("Removing from 1 past last index") {
// 		bool caught = false;
// 		try {
// 			l.remove(1);
// 		} catch (std::out_of_range& oor){
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE( "Retrieving items within the list", "[SSLL_item_at]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Retrieving an element") {
// 		l.push_front('A');
// 		REQUIRE(l.item_at(1) == 'X');
// 	}
//
// 	SECTION("Retrieving an element at an invalid position") {
// 		bool caught = false;
// 		try {
// 			l.item_at(1);
// 		} catch (std::out_of_range& oor){
// 			caught = true;
// 		}
// 		REQUIRE(caught == true);
// 	}
// }
//
// TEST_CASE( "Checking if the list is empty", "[SSLL_is_empty]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Returns true if empty list") {
// 		l.pop_front();
// 		REQUIRE(l.is_empty() == true);
// 	}
//
// 	SECTION("Returns false if there are elements in the list") {
// 		REQUIRE(l.is_empty() == false);
// 	}
// }
//
// TEST_CASE( "Returns the correct size of the list", "[SSLL_size]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Returns the size") {
// 		REQUIRE(l.size() == 1);
// 	}
//
// 	SECTION("Returns 0 if there are no elements") {
// 		l.pop_back();
// 		REQUIRE(l.size() == 0);
// 	}
//
// 	SECTION("Returns 3 if there are 3 elements") {
// 		l.push_front('X');
// 		l.push_front('X');
// 		REQUIRE(l.size() == 3);
// 	}
// }
//
// TEST_CASE( "Clears the entire list", "[SSLL_clear]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Clears the list") {
// 		l.push_front('X');
// 		l.push_front('X');
// 		l.clear();
// 		REQUIRE(l.size() == 0);
// 	}
//
// 	SECTION("Returns if there are no elements") {
// 		l.pop_back();
// 		l.clear();
// 		REQUIRE(l.size() == 0);
// 	}
// }
//
// TEST_CASE( "Returns the element at the specified index", "[SSLL_operator[]" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	SECTION("Returns the head element") {
// 		REQUIRE(l[0] == 'X');
// 	}
//
// 	SECTION("Returns the element at the index") {
// 		l.push_front('X');
// 		l.push_front('A');
// 		l.push_front('X');
// 		REQUIRE(l[1] == 'A');
// 	}
//
// 	SECTION("Correctly throws exception with invalid indices") {
// 		bool caught = false;
// 			l.pop_front();
// 			try {
// 				l[0];
// 			} catch(std::out_of_range& oor) {
// 				caught = true;
// 			}
// 			REQUIRE(caught == true);
// 		}
// }
//
// TEST_CASE( "Returns the const element at the specified index", "[SSLL_operator[]_const" ) {
// 	cop3530::SSLL<char> l;
// 	l.push_front('X');
// 	const cop3530::SSLL<char> const_list = l;
// 	SECTION("Returns the head element") {
// 		REQUIRE(const_list[0] == 'X');
// 	}
//
// 	SECTION("Returns the element at the index") {
// 		l.push_front('X');
// 		l.push_front('A');
// 		l.push_front('X');
// 		const cop3530::SSLL<char> const_list2 = l;
// 		REQUIRE(const_list2[1] == 'A');
// 	}
//
// 	SECTION("Correctly throws exception with invalid indices") {
// 		bool caught = false;
// 			l.pop_front();
// 			const cop3530::SSLL<char> const_list3 = l;
// 			try {
// 				const_list3[0];
// 			} catch(std::out_of_range& oor) {
// 				caught = true;
// 			}
// 			REQUIRE(caught == true);
// 		}
// }
//
//
// TEST_CASE( "SSLL_Prints the elements in the correct format", "[SSLL_print" ) {
// 	//for this method, assertions are not possible, so looking at the output is how I verified it.
// 	cop3530::SSLL<char> l;
// 	for(int i = 0; i < 60;i++){
// 		l.push_front('X');
// 	}
// 	l.push_front('A');
// 	l.print(std::cout);
// }
//
// template <typename T>
// bool equals(const T& a, const T& b) {
// 	if(a == b){
// 		return true;
// 	}
// 	return false;
// }
//
// TEST_CASE( "SSLL_Determines if the element is contained in the list", "[SSLL_contains]" ) {
// 	cop3530::SSLL<char> l;
// 	SECTION("Determines if an element is in the list") {
// 		for (int i = 0; i < 60; i++) {
// 			l.push_front('X');
// 		}
// 		l.push_back('A');
// 		REQUIRE(l.contains('A', equals));
// 		REQUIRE(!l.contains('B', equals));
// 	}
//
// 	SECTION("Returns false if the list is empty") {
// 		REQUIRE(!l.contains('A', equals));
// 	}
// }
