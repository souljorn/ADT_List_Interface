//
//  ADT_List.h
//  ADT_List
//
//  Created by Timothy Botelho on 9/12/17.
//  Copyright © 2017 Timothy Botelho. All rights reserved.
//



#ifndef ADT_List_h
#define ADT_List_h
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace COP3530{
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
class ADT_List{

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
    virtual bool contains(T elem,  bool equals_function(T &a, T &b)) = 0;
    virtual void print(std::ostream &stream) = 0;
    virtual T * contents(void) = 0;
    virtual ~ADT_List(){};




};
}
#endif /* ADT_List_h */
