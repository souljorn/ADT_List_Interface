
/*
Created by Timothy Botelho on 9/14/17.
Copyright © 2017 Timothy Botelho. All rights reserved.
Project 1 cop3530
Instructor Dave Small
*/

#ifndef PSLL_h
#define PSLL_h
#include "List.h"
using namespace std;

namespace cop3530{
//-----------------------PSLL_Iterator Class---------------------
  template <typename T>
  class PSLL_Iterator{
  public:
    Node<T> * iter;

    // type aliases required for C++ iterator compatibility
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::forward_iterator_tag;

  public:
    PSLL_Iterator(Node<T>* it):iter(it){}
    PSLL_Iterator(const PSLL_Iterator& c_iter):iter(c_iter.iter){}
    PSLL_Iterator& operator=(PSLL_Iterator it){ std::swap(iter, it.p); return *this;}
    PSLL_Iterator&  operator++() {  iter = iter->next; return *this;}
    PSLL_Iterator operator++(int) { PSLL_Iterator it(*this); iter = iter->next; return it;}
    bool operator==(const PSLL_Iterator& it) { return iter == it.iter; }
    bool operator!=(const PSLL_Iterator& it) { return iter != it.iter; }
    const T& operator*() const {PSLL_Iterator it(*this); return it.iter->data; }
    PSLL_Iterator& operator-(const difference_type& movement){PSLL_Iterator oldPtr = iter; iter-=movement;PSLL_Iterator temp(*this);iter = oldPtr;return temp;}
    difference_type operator-(const PSLL_Iterator& rawIterator){return std::distance(rawIterator.iter,iter);}

  };

template<typename T>
class PSLL : public List<T>{

//---------Pool Singly Linked List-------------
public:
    //function declerations
    PSLL();
    ~PSLL() override;
    friend class PSLL_Iterator<T>;
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
    bool contains(T elem,  bool equals_function( const T &a, const T &b))override;
    void print (std::ostream &stream)override;
    T * contents()override;
    void create_pool(int num);
    size_t length_pool();
    bool pool_is_empty();
    Node<T> * pool_pop_back();
    void find_tail();
    size_t trim_pool();
    void push_pool(Node<T> * node);
    void clear_pool();
    /*----in-class iterator functions---------------
    functions to allow PSSL_Iterator to function as
    an iterator with in PSLL
    */

    //typedefs to allow iterators to works with c++ std functions
    typedef PSLL_Iterator<T> iterator;
    typedef PSLL_Iterator<T> const_iterator;
    using difference_type = std::ptrdiff_t;

    iterator begin()
    {
        return iterator(head->next);
    }

    const_iterator begin() const
    {
        return const_iterator(head->next);
    }

    iterator end()
    {
        return iterator(NULL);
    }

    const_iterator end() const
    {
        return const_iterator(NULL);
    }

    difference_type distance(iterator first, iterator last){
        return  (last - first)/4;
    }


    //member variables
    Node<T> * head;
    Node<T> * tail;
    Node<T> * free_pool;
    Node<T> * free_pool_tail;

};

//---------constructor-----------------

template<typename T>
PSLL<T>::PSLL()
{head = new(Node<T>),tail = new(Node<T>), free_pool = new Node<T>,free_pool_tail = new Node<T>,head->data =0;
    head->next = NULL ;
    tail->next = NULL;
    free_pool->next = NULL;
    free_pool_tail->next = NULL;
}

//---------destructor-----------------
template<typename T>
PSLL<T>::~PSLL(){
    clear();

}

//-----------insert-------------------
template<typename T>
void PSLL<T>::insert(T elem, size_t pos){
    Node<T> * back = new Node<T>;
    Node<T> * conductor = new Node<T>();
    Node<T> * temp = new Node<T>();
    temp->data = elem;
    size_t index=0;
    conductor = free_pool;

    if (pos > length() || pos < 0 ) {
        throw std::runtime_error("Out of range");
        }
    else if( pos ==0 && is_empty()){    //creatin the first node if list is empty
        conductor = head->next;
        if(!pool_is_empty()){
          head->next = pool_pop_back();
        }
        else{
          head->next = temp;
        }
        head->next->data = elem;
        conductor = head->next;
        conductor->next = NULL;
        tail->next = head->next;
    }

    else if(pos == 0 && !is_empty()){

        if (pool_is_empty()) {          //if pool of free nodes is empty
        conductor = head->next;
        temp->data = elem;
        head->next = temp;
        temp->next = conductor;
            tail->next = conductor;
        }//if
        else{
            conductor = head->next;     //conductor holds the place of current head->next
            temp = pool_pop_back();     //pop a free node
            head->next = temp;          //set the head to the free node
            temp->data = elem;          //set temp data to elem
            temp->next = conductor;     //reconnect the new head node to the previous head
            tail->next = conductor;           //set the tail
        }//else

    }//else if
    else if( pos ==0 && is_empty()){    //creatin the first node if list is empty
        head->next = pool_pop_back();
        head->next->data = elem;
        conductor = head->next;
        conductor->next = NULL;
    }
    else if(pos> 0 && pos<=length())     //iserting at index
    {

        conductor = head->next;
        while (index != pos ) {
            back = conductor;
            conductor = conductor->next;
            index++;
        }//while
        if(!pool_is_empty()){
        temp = pool_pop_back();
        }
        back->next = temp;
        temp->data = elem;
        temp->next = conductor;
    }
}

template <typename T>
void PSLL<T>::find_tail(){
    length();
}
//------------push_back---------------
template<typename T>
void PSLL<T>::push_back(T elem){
    Node<T> * conductor = new Node<T>();
    conductor = head;

    if (length_pool() == 0) {                   //if pool is empty push back with new node
        if (head->next == NULL) {
            Node<T> * temp = new Node<T>();
            temp->data = elem;
            head-> next = temp;
            temp->next = NULL;
            tail->next = head->next;

        }

        else {
            Node<T> * temp3 = new Node<T>();
            temp3->data = elem;
            tail->next->next = temp3;
            tail->next = temp3;
        }//else
    }//if pool is empty
    //When pool has items
    else{
        if(head->next == NULL) {
            Node<T> * temp = new Node<T>();
            temp = pool_pop_back();
            temp->data = elem;
            head-> next = temp;
            temp->next = NULL;
            tail->next = head->next;
        }
        else if(!is_full()){
            Node<T> * temp = new Node<T>();
            Node<T> * conductor = new Node<T>();
            temp = pool_pop_back();
            temp->data = elem;
            length();
            conductor = tail->next;
            conductor->next =temp;
            tail->next = temp;

        }
        //for case where there is atleast one node

    }//else if

}

//------------push_front--------------
template<typename T>
void PSLL<T>::push_front(T elem){
    insert(elem, 0);
}

//-------------replace----------------
template<typename T>
T PSLL<T>::replace(T elem, size_t pos)
{
    Node<T> * conductor;
    conductor = head;
    size_t index =0;                       //index used to find position
    T temp = 0;

    if(is_empty())
    throw std::runtime_error("Replacing item when list is empty");

    if(pos > length())
    throw std::runtime_error("Replacing item is out of bounds");

    if ( pos==0 ) {
        temp = head->next->data;            //set temp to hold original element;
        head->next->data = elem;              //set head to hold new element;
        return elem;
    }
    while (conductor->next != NULL) {   //traverse through list
        conductor = conductor->next;
        index++;                        //increment current index
        if(index == pos){
            temp = conductor->data;
            conductor->data = elem;
        }//if
    }//while

    return elem;
}

//----------------remove--------------
template<typename T>
T PSLL<T>::remove(size_t pos){
  Node<T> * conductor = new Node<T>();
  Node<T> * back = new Node<T>();
  conductor = head->next;
  T temp;

  size_t index = 0;

  if (pos > length()) {
      throw std::runtime_error("Out of range");
  }
  else if (is_empty())
  {
      throw std::runtime_error("List is empty");
  }
  else if(length() == 1){
      temp = head->next->data;
      push_pool(head->next);
      clear();
      return temp;
  }

  else {while (conductor->next != NULL) {   //traverse through list
      back = conductor;
      conductor = conductor->next;
      index++;
      //keep position

      if(pos==0 && length()>1)
      {
          temp = head->next->data;
          pop_front();
          return temp;
      }
      else if(index == pos){
          temp = conductor->data;
          back->next = conductor->next;
          conductor->next = NULL;
          push_pool(conductor);
          return temp;
      }
      }//if
  }//while

  return temp;

}

//---------------pop_back------------
template<typename T>
T PSLL<T>::pop_back(){
    Node<T> * conductor =new Node<T>();
    Node<T> * back = new Node<T>();
    T temp;
    conductor = head;
    back = head;

    //Test if list is empty
    if(is_empty()) {
        throw std::runtime_error("list is empty");

    }
    while (conductor->next != NULL) {
        back = conductor;
        conductor = conductor->next;


    }

    if (conductor == head->next) {    //if popping last element then set head to Null
        push_pool(head->next);
        head->next =NULL;
        return temp;
    }

    else if (head->next == NULL)
        throw std::runtime_error("List is empty");

    else if(!is_empty()){
        length_pool();                  //make sure pool tail is correct
        push_pool(conductor);           //push node to free pool
        T temp = tail->next->data;      //Temp data
        tail->next = back;
        back->next =NULL;
        return temp;
    }
    return temp;
}

//-----------------pop_front-----------
template<typename T>
T PSLL<T>::pop_front(){
    Node<T> * conductor =new Node<T>();
    Node<T> * back = new Node<T>();
    T temp;

    if(is_empty()) {
        throw std::runtime_error("list is empty");
    }

    else{
        back = head->next;      //set back to head->next
        temp = back->data;      //set temp equal to node about to be popped
        conductor = back->next; //conductor = to new head->next
        back->next = NULL;      //set back->next to Null to cut off reference from list
        push_pool(back);        //push node to pool
        head->next = conductor; //set head = to conductor
        return temp;            //return temp
    }
}

//-----------------item_at-------------
template<typename T>
T PSLL<T>::item_at(size_t pos){
    Node<T> * conductor = new Node<T>();
    Node<T> * back = new Node<T>();
    conductor = head->next;

    size_t size = 0;
    if(is_empty())
    throw std::runtime_error("list is empty");

    if(pos > length())
    throw std::runtime_error("out of bounds");

    while (size != pos) {
        conductor = conductor->next;
        size++;
    }
    return  conductor->data;
}

//-----------------peek_back-----------
template<typename T>
T PSLL<T>::peek_back(){
    length();

    return tail->next->data;
}

//----------------peek_front-----------
template <typename T>
T PSLL<T>::peek_front()
{
    return head->next->data;
}

//---------------is_empty--------------
template <typename T>
bool PSLL<T>::is_empty()
{
    if(head->next == NULL)
    return true;
    return false;
}

//---------------pool_is_empty--------------
template <typename T>
bool PSLL<T>::pool_is_empty()
{
    if (free_pool->next == NULL) {
        return true;
    }
    return false;
}

//---------------is_full---------------
template <typename T>
bool PSLL<T>::is_full(){

    return false;
}

//---------------length----------------
template <typename T>
size_t PSLL<T>::length(){
    Node<T> * conductor = new Node<T>();
    size_t size=0;
    conductor = head;
    if (is_empty()) {
        return 0;
    }
    while (conductor->next != NULL) {
        conductor = conductor->next;
        size++;
    }
    tail->next = conductor;
    return size;
}

//---------------length_pool----------------
template <typename T>
size_t PSLL<T>::length_pool(){

Node<T> * conductor = new Node<T>;

    size_t size = 0;
    if (free_pool->next == NULL) {
        return 0;
    }
    conductor = free_pool;    //set conductor to free pool head
    while (conductor->next != NULL) {
        conductor = conductor->next;
        size++;
    }
    free_pool_tail->next = conductor;
    return size;
}

//--------------clear-----------------
template <typename T>
void PSLL<T>::clear(){
  Node<T> * conductor = new Node<T>();
  Node<T>  * back = new Node<T>();
  conductor = head->next;
  back = head->next;

  if(is_empty())
  return;

  while (conductor->next != NULL) {
      back = conductor;
      conductor = conductor->next;
      delete back;
  }
  head->next = NULL;
}

//--------------clear pool-----------------
template <typename T>
void PSLL<T>::clear_pool(){
  Node<T> * conductor = new Node<T>();
  Node<T>  * back = new Node<T>();
  //conductor = free_pool;
  //back->next = conductor;

  //if(pool_is_empty())
  return;

  //while (conductor->next != NULL) {
    //  back = conductor;
    //  conductor = conductor->next;
      //delete back;
//  }
  //free_pool->next = NULL;
}

//-------------contains-------------
template <typename T>
bool PSLL<T>::contains(T elem,  bool equals_function(const T &a, const T &b)) {
  Node<T> * conductor = new Node<T>();
  conductor = head->next;
  bool equal = false;
  while(conductor != NULL){
   if(equals_function(elem,conductor->data) == true)
   return true;
    conductor = conductor->next;
  }
  return false;
}

//--------------print-----------------
template <typename T>
void PSLL<T>::print(std::ostream &stream){
    Node<T> * conductor = new Node<T>();
    conductor = head->next;
    //size_t index = 0;
    if (is_empty()) {
        stream << "<empty list> \n ";
    }
    else if(!is_empty()){
        while (conductor->next != NULL) {
            stream << "<" << conductor->data << ">" ;
            stream << ",";
            conductor = conductor->next;
        }
        stream << "<" << conductor->data << ">"  << " \n";
    }
}

//--------------contents-------------
template<typename T>
T * PSLL<T>::contents(){
  T * arr = new T[length()];

  //PSLL<T>::iterator iter = begin();   //create a begin iterator
  PSLL<T>::iterator iter_end = end();     //create end iterator

  //iterator implementation using distance
  for (auto iter = begin(); iter != iter_end; ++iter) {
        //need to use distance to get an index
        int i = distance(begin(), iter);

        arr[i] = *iter;

}


  return arr;
}
template<typename T>
void PSLL<T>::create_pool(int num){

  Node<T> * conductor = new Node<T>();
  Node<T> * temp = new Node<T>();   //create a new temp node for every iteration
  conductor->next = free_pool;

    if (free_pool->next ==NULL){
      free_pool->next = temp;
      conductor->next =temp;
      free_pool_tail->next = temp;
    }//if

    int i = 0;
    while (i < num-1) {
     Node<T> * temp = new Node<T>();
        conductor = conductor->next;
        conductor->next = temp;
        i++;
    }
    free_pool_tail->next = temp;
}

//---------------pool_pop_back------------
template<typename T>
Node<T> * PSLL<T>::pool_pop_back(){
    Node<T> * conductor = new Node<T>();
    Node<T> * temp = new Node<T>();
    conductor = free_pool->next;
    if (free_pool->next == NULL) {
        cout << "Pool is empty";
        return NULL;
    }
    else{
        while (conductor->next != NULL) {
            temp = conductor;
            conductor = conductor->next;
        }
        temp->next= NULL;
        free_pool_tail->next=temp;
        return conductor;
    }
}

//---------------------trim_pool------------
template <typename T>
size_t PSLL<T>::trim_pool(){
    if (length() > 100 && length_pool() >50) {
    int pool_trim = length_pool()-50;
        for(int i =0; i<pool_trim ;i++){

            pool_pop_back();
        }
    }
    return 0;
}

//-------------------push_pool-----------
template <typename T>
void PSLL<T>::push_pool(Node<T> * node){
    Node<T> * conductor = new Node<T>();

    if(pool_is_empty()){         //when pool is empty
      free_pool->next = node;
      free_pool_tail->next = node;
    }
    else if(length_pool() >= 50){     //delete nodes over 50
      delete node;
    }
    else{
    conductor = free_pool_tail->next;  //temp is set to tail
    conductor->next= node;             //temp->next is set to node
    free_pool_tail->next = node;         //free_pool_tail is set to node
    node->next = NULL;
    }

}

}//namespace
#endif /* PSLL_h */
