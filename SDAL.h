//
//  SDAL.h
//  ADT_List
//
//  Created by Timothy Botelho on 9/20/17.
//  Copyright © 2017 Timothy Botelho. All rights reserved.
//

#ifndef SDAL_h
#define SDAL_h
#include "ADT_List.h"

using namespace std;

namespace COP3530{
template<typename T>
class SDAL:ADT_List<T>{

    //---------Single Dynamic Array-Based List-------------
public:
    //function declerations
    SDAL();
    SDAL(size_t size);
    ~SDAL() override;
    void insert(T elem, size_t pos) override;
    void push_back(T elem) override;
    void push_front(T elem)override;
    T replace(T elem, size_t pos)override;
    T remove(size_t pos)override;
    T pop_back()override;
    T pop_front()override;
    T item_at(size_t pos)override;
    T peek_back()override;
    T peek_front()override;
    bool is_empty()override;
    bool is_full()override;
    size_t length()override;
    void clear()override;
    bool contains(T elem,  bool equals_function(T &a, T &b))override;
    void print (std::ostream &stream)override;
    T * contents()override;
    size_t size();
    void create_data();
    void create_null_data();
    void shift_left(size_t pos_shift);
    void shift_left(size_t begin,size_t end);
    void shift_right(size_t pos_shift);
    void shift_right(size_t begin,size_t end);
    void resize_larger();
    void resize_smaller();
    void print_entire_array(std::ostream &stream);
private:
    //member variables
    T * list;
    size_t m_size = 0;
    size_t capacity_used = 0;
};

//
//int *secondArray = new int[secondSize]; // Create array
////Initialize secondArray to 0
//for(int i = 0; i < secondSize; i++) secondArray[i] = 0;
////Then use your code
//for(int j = 0; j < secondSize; ++j)
//{
//    secondArray[j] = firstArray[j]; // Set second array equal to first array
//}


//------------begin,  end,     , array to copy to
//std::copy ( myints, myints+7, myvector.begin() );

//---------------Goals
//--50 slots for original base constructor
//-If item is added to full array create an array 150% the size
//-100 slots in original array but only 50% used bring array down to 75%
//
//-Check for edge cases on pop to resize to smaller
//
//---------constructor-----------------

template<typename T>
SDAL<T>::SDAL(){
    list = new T[50];
    m_size = 50;

}

template<typename T>
SDAL<T>::SDAL(size_t size)

{
    list = new T[size];
    m_size = size;
}

//---------destructor-----------------
template<typename T>
SDAL<T>::~SDAL(){
    delete list;

}

//-----------insert-------------------**
template<typename T>
void SDAL<T>::insert(T elem, size_t pos){
    //check if array is full and then resize

    if(pos > length())
    throw std::runtime_error("out of bounds");


    if(is_empty() && pos == 0){
        list[0] = elem;
                                 }
    else if (!is_empty() && pos == 0)
    {   shift_right(0);
        list[0] = elem;
    }
    else if (is_full()) {
        resize_larger();
        //now move to postion and  shift items right
        shift_right(pos, length() -1 );
        list[pos] = elem;
    }
    //if not full
    else{
        shift_right(pos, length() -1 );
        list[pos] = elem;
    }
    capacity_used++;
}

//------------push_back---------------**
template<typename T>
void SDAL<T>::push_back(T elem){
    if (is_full()) {
        resize_larger();
        list[length()] = elem;
        capacity_used++;
    }
    else{
        list[length()] = elem;
        capacity_used++;
    }
}

//------------push_front--------------**
template<typename T>
void SDAL<T>::push_front(T elem){
    //check if array is full

    if(is_full()){
        resize_larger();
        shift_right(0);
        list[0] = elem;
        capacity_used++;
    }
    else{
        shift_right(0);
        list[0] = elem;
        capacity_used++;
    }



}
//-------------replace----------------**

template<typename T>
T SDAL<T>::replace(T elem, size_t pos)
    {

      //
      if(is_empty())
        throw std::runtime_error("list is empty");

      if(pos > length())
        throw std::runtime_error("out of bounds");

        T * curr = list;
        T * end = list + m_size;

        while (curr != end) {
            if(*curr == pos){

                T temp = *curr;
                *curr = elem;
                return temp;
            }
            curr++;
        }
        return NULL;
    }

//----------------remove--------------**
template<typename T>
T SDAL<T>::remove(size_t pos){

    if(is_empty())
      throw std::runtime_error("list is empty");

    if(pos > length())
      throw std::runtime_error("out of bounds");

    T temp = list[pos];
    shift_left(pos, length() -1);
    capacity_used--;
    return temp;
}

//---------------pop_back------------**
template<typename T>
T SDAL<T>::pop_back(){
    size_t  temp_size = length();

    if(is_empty())
      throw std::runtime_error("list is empty");

    T temp =list[temp_size-1];
    list[temp_size-1] = -1;
    capacity_used--;
    return temp;
}

//-----------------pop_front-----------**
template<typename T>
T SDAL<T>::pop_front(){

  if(is_empty())
    throw std::runtime_error("list is empty");

  T temp = list[0];
  shift_left(0);
  capacity_used--;
  return temp;
}

//-----------------item_at-------------**
template<typename T>
T SDAL<T>::item_at(size_t pos){

       return  list[pos];
}
//-----------------peek_back-----------**
template<typename T>
T SDAL<T>::peek_back(){
    size_t size = length();
    return list[size-1];


}
//----------------peek_front-----------**
template <typename T>
T SDAL<T>::peek_front()
{

    return list[0];
}

//---------------is_empty--------------**
template <typename T>
bool SDAL<T>::is_empty()
{
    if (length() == 0) {
        return true;
    }
    return false;
}


//---------------is_full---------------**
template <typename T>
bool SDAL<T>::is_full(){
    if(length() == m_size)
    return true;
    return false;
}

//---------------length----------------**
template <typename T>
size_t SDAL<T>::length(){

    return (size_t)capacity_used;

}


//--------------clear-----------------**
template <typename T>
void SDAL<T>::clear(){
    T * curr = list;
    T * end = list + m_size;
    while (curr!= end) {
        *curr++ = -1;
    }

    //set capacity_used to 0
    capacity_used = 0;


}
//--------------size----------------**

template <typename T>
size_t SDAL<T>::size() {
    return m_size;
}

//-------------contains-------------
template <typename T>
bool SDAL<T>::contains(T elem,  bool equals_function(T &a, T &b)) {
    T * curr =list;
    T * end = list + m_size;

    while (curr != end) {
        if (elem == *curr) {
            return true;
        }
        curr++;
    }
    return false;
}

//--------------print-----------------
template <typename T>
void SDAL<T>::print(std::ostream &stream){

    if (is_empty()) {
        stream << "<empty list> \n ";
    }
    else if(!is_empty()){
        size_t current_size = length();
        for(int i = 0; i < current_size; i++){
            stream << " <" << list[i]<< ">" ;
            stream << ", ";

        }
        //stream << "<" << conductor->data << ">"  << " \n";
    }
}

//--------------contents-------------
template<typename T>
T * SDAL<T>::contents(){

    return NULL;
}

//----------------create data----------
template<typename T>
void SDAL<T>::create_data()
{
    for(int i = 0; i<20; i++){
    list[i] = i;
    }
}

//--------------create null data---------
template<typename T>
void SDAL<T>::create_null_data()
{
    int * curr =list;
    int * end = list + m_size;
    while (curr != end) {
        *curr = -1;
        curr++;
    }
}

//--------------shift values right--------------**
template<typename T>
void SDAL<T>::shift_right(size_t pos_shift){
    size_t temp_len = length();
    if(pos_shift < temp_len){
        for (int i =temp_len; i > pos_shift; i--) {

        list[i] = list[i-1];
        }
    }
}

template<typename T>
void SDAL<T>::shift_right(size_t begin,size_t end){
    size_t temp_len = length();

        for (size_t i = end; i>= begin; i--) {

            list[i+1] = list[i];
    }
}

//---------------shift values left-------------
template<typename T>
void SDAL<T>::shift_left(size_t pos_shift){
    size_t temp_len = length();
    for (size_t i =pos_shift; i< temp_len-1 ; i++) {

        list[i] = list[i+1];
    }
    list[length()-1] = -1;
}
//---------------shift values left-------------
template<typename T>
void SDAL<T>::shift_left(size_t begin,size_t end){
    size_t temp_len = length();
    for (int i =begin; i< end ; i++) {

        list[i] = list[i+1];
    }
    list[length()-1] = -1;
}

//----------------resize larger--------------
template<typename T>
void SDAL<T>::resize_larger(){

    size_t new_size = 1.5 * m_size;
    T * arrTemp = new T[new_size];
    copy(list, list + m_size, arrTemp);
    list = arrTemp;
    m_size = new_size;
}

//-----------------resize smaller------------
template<typename T>
void SDAL<T>::resize_smaller(){
    if(m_size < 50){
        size_t new_size = .75 * m_size;
        T * arrTemp = new T[new_size];
        copy(list, list + m_size, arrTemp);
        list = arrTemp;
        m_size = new_size;}
}

//-----------------entire array-------------
template<typename T>
void SDAL<T>::print_entire_array(std::ostream &stream){
    for(int i = 0; i < m_size; i++){
        stream << "<" << list[i]<< ">" ;
        stream << ", \n";
    }

}
}
#endif /* SDAL_h */
