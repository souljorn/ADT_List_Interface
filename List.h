//
//  ADT_List.h
//  ADT_List
//
//  Created by Timothy Botelho on 9/12/17.
//  Copyright © 2017 Timothy Botelho. All rights reserved.
//
/*
----------To Do -------------
CBL(circular buffer list) data stucture

****For all lists********
copy constructor,
copy-assignment operator,
move constructor,
move-assignment operator, &
destructor

PSLL
copy constructor is the same with empty pool
-deallocacte the list cleanly
copy assignment keeps the same free pool

CDAL at most will contain one empty array

SDAL
Because we don't want the list to waste too much
memory, whenever the array's size is ≥ 100 slots
twice the starting capacity and fewer than half
the slots are used, allocate a new array 75%
the size of the original current array,
copy the items over to the new array,
and deallocate the original one.
current array, and use the new array
as the backing store.
*/

#ifndef List_h
#define List_h
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace cop3530{
template<class T>
class Node{
public:
    Node * next = NULL;
    Node * prev = NULL;
    T  data;
    T* ptr;
    int cur_arr_size = 0;
    bool is_full =false;
    bool is_empty = true;

};

template<typename T>
class List{

public:
    virtual void insert(T elem,size_t pos) = 0;
    virtual void push_back(T elem) = 0;
    virtual void push_front(T elem) = 0;
    virtual T replace(T elem, size_t pos) = 0;
    virtual T remove(size_t pos)= 0;
    virtual T pop_back(void) = 0;
    virtual T pop_front(void) = 0;
    virtual T item_at(size_t pos) = 0;
    virtual T peek_back(void) = 0;
    virtual T peek_front(void) = 0;
    virtual bool is_empty(void) = 0;
    virtual bool is_full(void) = 0;
    virtual size_t length(void) = 0;
    virtual void clear(void) = 0;
    virtual bool contains(T elem,  bool equals_function(const T &a,const T &b)) = 0;
    virtual void print(std::ostream &stream) = 0;
    virtual T * contents(void) = 0;
    virtual ~List(){};




};
}
#endif /* ADT_List_h */
