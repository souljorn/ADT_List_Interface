//
//  CBL.h
//  List
//
//  Created by Timothy Botelho on 9/20/17.
//  Copyright © 2017 Timothy Botelho. All rights reserved.
//

#ifndef CBL_h
#define CBL_h
#include "List.h"

using namespace std;

namespace cop3530{

//-----------------------CBL_Iterator Class---------------------
template <typename T>
class CBL_Iterator{
public:
  T * iter;

  // type aliases required for C++ iterator compatibility
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using iterator_category = std::forward_iterator_tag;

public:
  CBL_Iterator(T * it):iter(it){}
  CBL_Iterator(const CBL_Iterator& c_iter):iter(c_iter.iter){}
  CBL_Iterator& operator=(CBL_Iterator it){ std::swap(iter, it.p); return *this;}
  CBL_Iterator&  operator++() {  iter = iter + 1; return *this;}
  CBL_Iterator operator++(int) { CBL_Iterator it(*this); iter = iter + 1; return it;}
  bool operator==(const CBL_Iterator& it) { return iter == it.iter; }
  bool operator!=(const CBL_Iterator& it) { return iter != it.iter; }
  const T& operator*() const {CBL_Iterator it(*this); return *(it.iter); }
  //PSLL_Iterator& operator-(const difference_type& movement){PSLL_Iterator oldPtr = iter; iter-=movement;PSLL_Iterator temp(*this);iter = oldPtr;return temp;}
  //difference_type operator-(const PSLL_Iterator& rawIterator){return std::distance(rawIterator.iter,iter);}

};

template<typename T>
class CBL: public List<T>{

    //---------Single Dynamic Array-Based List-------------
public:
    //function declerations
    CBL();
    CBL(size_t size);
    ~CBL() override;
    friend class CBL_Iterator<T>;
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
    bool contains(T elem,  bool equals_function(const T &a,const T &b))override;
    void print (std::ostream &stream)override;
    T * contents()override;
    size_t size();

    void shift_left(size_t pos_shift);
    void shift_right(size_t pos_shift);
    void resize_larger();
    void resize_smaller();
    void print_entire_array(std::ostream &stream);

    //----iterator---------------
    typedef CBL_Iterator<T> iterator;
    typedef CBL_Iterator<T> const_iterator;

    //---------------iterator functions----------------------
    iterator begin()
    {
        return iterator(list);
    }

    const_iterator begin() const
    {
        return const_iterator(list);
    }

    iterator end()
    {
        return iterator(list + capacity_used);
    }

    const_iterator end() const
    {
        return const_iterator( list + capacity_used);
    }


//private:
    //member variables
    T * list;
    size_t m_size = 0;
    size_t capacity_used = 0;
    int head;
    int tail;
};


//---------constructor-----------------

template<typename T>
CBL<T>::CBL(){
    list = new T[50];
    m_size = 50;
    head = 0;
    tail = 0;

}

template<typename T>
CBL<T>::CBL(size_t size)

{
    list = new T[size];
    m_size = size;
}

//---------destructor-----------------
template<typename T>
CBL<T>::~CBL(){
    delete list;


}

//-----------insert-------------------**
template<typename T>
void CBL<T>::insert(T elem, size_t pos){
    //check if array is full and then resize

    if(pos > length())
    throw std::runtime_error("out of bounds");

    if(is_full())
    resize_larger();

    if(is_empty() && pos == 0){
        list[head] = elem;
        tail = (tail + 1 ) % m_size;
                                 }
    else if (!is_empty() && pos == 0)
    {

      if(head == 0)
      {
      list[m_size-1] = elem;
      head = m_size - 1;
      }
      else{
      list[head - 1] = elem;
      head = head - 1;
      }
    }
    //if pushing on back
    else if((pos + head)% m_size == tail-1){
      list[tail] = elem;
      tail = (tail + 1) % m_size;
    }
    else{
        shift_right(pos);
        list[head + pos] = elem;
    }
    capacity_used++;
}

//------------push_back---------------**
template<typename T>
void CBL<T>::push_back(T elem){

    if(length() == 0)
    {
      push_front(elem);
    }
    else{
        insert(elem, length()-1);
    }
}

//------------push_front--------------**
template<typename T>
void CBL<T>::push_front(T elem){
    //check if array is full

    if(is_full()){
        resize_larger();
        insert(elem,0);
    }
    else{
        insert(elem, 0);

    }
}
//-------------replace----------------**

template<typename T>
T CBL<T>::replace(T elem, size_t pos)
    {

      //
      if(is_empty())
        throw std::runtime_error("list is empty");

      if(pos > length())
        throw std::runtime_error("out of bounds");

        pos = (head + pos) % m_size;

        T curr = head;
        T  end = tail;
        T temp;
        while (curr != end) {
            if(curr == pos){
                temp = list[curr];
                list[curr] = elem;
                return temp;
            }
            curr = (curr + 1) % m_size;

        }
        return temp;
    }

//----------------remove--------------**
template<typename T>
T CBL<T>::remove(size_t pos){

    if(is_empty())
      throw std::runtime_error("list is empty");

    if(pos > length())
      throw std::runtime_error("out of bounds");

    T temp = list[(pos + head) % m_size];
    shift_left(pos);
    capacity_used--;
    return temp;
}

//---------------pop_back------------**
template<typename T>
T CBL<T>::pop_back(){
    size_t  temp_size = length();

    if(is_empty())
      throw std::runtime_error("list is empty");

    T temp =list[tail-1];
    tail =(tail - 1) % m_size;
    capacity_used--;
    return temp;
}

//-----------------pop_front-----------**
template<typename T>
T CBL<T>::pop_front(){

  if(is_empty())
    throw std::runtime_error("list is empty");

  T temp = list[head];
  head = (head + 1) % m_size;
  capacity_used--;
  return temp;
}

//-----------------item_at-------------**
template<typename T>
T CBL<T>::item_at(size_t pos){

       return  list[(head + pos) % m_size];
}
//-----------------peek_back-----------**
template<typename T>
T CBL<T>::peek_back(){
    size_t size = length();
    return list[tail-1];


}
//----------------peek_front-----------**
template <typename T>
T CBL<T>::peek_front()
{

    return list[head];
}

//---------------is_empty--------------**
template <typename T>
bool CBL<T>::is_empty()
{
    if (head == tail) {
        return true;
    }
    return false;
}


//---------------is_full---------------**
template <typename T>
bool CBL<T>::is_full(){

    if(head == (tail + 1) % m_size){

    return true;
  }
    return false;
}

//---------------length----------------**
template <typename T>
size_t CBL<T>::length(){

    return (size_t)capacity_used;

}


//--------------clear-----------------**
template <typename T>
void CBL<T>::clear(){
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
size_t CBL<T>::size() {
    return m_size;
}

//-------------contains-------------
template <typename T>
bool CBL<T>::contains(T elem,  bool equals_function(const T &a,const T &b)) {
    int curr = head;

    while (curr != tail) {
        if (equals_function(elem, list[curr])) {
            return true;
        }
        curr = (curr + 1) % m_size;
    }
    return false;
}

//--------------print-----------------
template <typename T>
void CBL<T>::print(std::ostream &stream){

    if (is_empty()) {
        stream << "<empty list> \n ";
    }
    else if(length() ==1 ){
      stream << " <" << list[head]<< ">" ;
    }
    else if(!is_empty()){
        size_t current_size = capacity_used;
        int pos = head;
        while(pos != tail-1){
            stream << " <" << list[pos]<< ">" ;
            stream << ", ";
            pos = (pos + 1) % m_size;

        }
        stream << "<" << list[tail-1] << ">"  << " \n";
    }
}

//--------------contents-------------
template<typename T>
T * CBL<T>::contents(){
  T * array = new T[length()];

  int curr = head;
  int i = 0;

  while (curr != tail) {
      array[i] = list[curr];
      curr = (curr + 1) % m_size;
  }
}


//--------------shift values right--------------**
template<typename T>
void CBL<T>::shift_right(size_t pos_shift){
  //create temp array to hold while shifting
  T * temp = new T[m_size];
  memcpy(temp, list, sizeof(T) * m_size);

  //pos in memory
 int pos =(head + pos_shift) % m_size;
 //temp holder array

 //starting point
 int i = (head + pos_shift) % m_size;

 //iterates through till tail
 while(pos != tail - 1){
    temp[(i + 1) % m_size] = list[i % m_size];
     i++;
     pos = (pos + 1) % m_size;
 }
 tail = (tail + 1) % m_size;
 memcpy(list, temp, sizeof(T) * m_size);
}

//---------------shift values left-------------
template<typename T>
void CBL<T>::shift_left(size_t pos_shift){
  //create temp array to hold while shifting
  T * temp = new T[m_size];
  memcpy(temp, list, sizeof(T) * m_size);

  //pos in memory
 int pos = (head + pos_shift) % m_size;
 //temp holder array

 //starting point
 int i = (head + pos_shift) % m_size;

 //iterates through till tail
 while(pos != tail - 1){
    temp[(i) % m_size] = list[(i + 1) % m_size];
     i++;
     pos = (pos + 1) % m_size;
 }
 tail = (tail - 1) % m_size;
 memcpy(list, temp, sizeof(T) * m_size);
}


//----------------resize larger--------------
template<typename T>
void CBL<T>::resize_larger(){

  size_t new_size = 1.5 * m_size;
  T * arrTemp = new T[new_size];
  int pos = head;
  int i = 0;
  while(pos != tail)
  {
      arrTemp[i++] = list[pos];
      pos = (pos + 1) % m_size;
      //cout << i << endl;
  }


  list = arrTemp;
  // for(int i = 0; i < 60 ;i++)
  //   cout << list[i] << endl;

  head = 0;
  tail = i;

  m_size = new_size;
}

//-----------------resize smaller------------
template<typename T>
void CBL<T>::resize_smaller(){
    if(m_size < 50){
        size_t new_size = .75 * m_size;
        T * arrTemp = new T[new_size];
        copy(list, list + m_size, arrTemp);
        list = arrTemp;
        m_size = new_size;}
}

//-----------------entire array-------------
template<typename T>
void CBL<T>::print_entire_array(std::ostream &stream){
    for(int i = 0; i < m_size; i++){
        stream << "<" << list[i]<< ">" ;
        stream << ", \n";
    }
}

}//namespace
#endif /* CBL_h */
