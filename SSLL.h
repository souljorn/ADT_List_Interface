//
//  SSLL.h
//  ADT_List
//
//  Created by Timothy Botelho on 9/12/17.
//  Copyright © 2017 Timothy Botelho. All rights reserved.
//

#ifndef SSLL_h
#define SSLL_h
#include "ADT_List.h"

namespace COP3530{


template <typename T>
class Linked_List_Iterator{
    Node<T> * iter;
public:
    Linked_List_Iterator(Node<T>* it):iter(it){}
    Linked_List_Iterator(const Linked_List_Iterator& c_iter):iter(c_iter.iter){}
    Linked_List_Iterator& operator=(Linked_List_Iterator it){ std::swap(iter, it.p); return *this;}
    Linked_List_Iterator&  operator++() {  iter = iter->next; return *this;}
    Linked_List_Iterator& operator++(int) { Linked_List_Iterator it(*this); iter = iter->next; return it;}
    bool operator==(const Linked_List_Iterator& it) { return iter == it.iter; }
    bool operator!=(const Linked_List_Iterator& it) { return iter != it.iter; }
    const T& operator*() const {Linked_List_Iterator it(*this); return it.iter->data; }
};


template<typename T>
class SSLL:ADT_List<T>{

public:

    SSLL();
    ~SSLL() override;
    friend class Linked_List_Iterator<T>;
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

    //----iterator---------------
    typedef Linked_List_Iterator<T> iterator;
    typedef Linked_List_Iterator<T> const_iterator;

    iterator begin()
    {
        return iterator(head);
    }

    const_iterator begin() const
    {
        return const_iterator(head);
    }

    iterator end()
    {
        return iterator(NULL);
    }

    const_iterator end() const
    {
        return const_iterator(NULL);
    }

    //---members---
    Node<T> * head;
    Node<T> * tail;
    size_t max_nodes =100;
};

//---------constructor-----------------

template<typename T>
SSLL<T>::SSLL()
{head = new(Node<T>),tail = new(Node<T>);
    head = NULL;
    tail = NULL;
}

//---------destructor-----------------
template<typename T>
SSLL<T>::~SSLL(){
    clear();

}

//-----------insert-------------------
template<typename T>
void SSLL<T>::insert(T elem, size_t pos){
    Node<T> * temp = new Node<T>();
    Node<T> * conductor = new Node<T>();
    Node<T> * back = new Node<T>();
    conductor = head;
    size_t currentPos = 0;


      if(pos > length() || (pos != 0 && is_empty())){
      throw std::runtime_error("Out of range");
      }

   if (pos == 0 && is_empty()) {
        Node<T> * temp = new Node<T>();
        temp->data = elem;
        head = temp;
        temp->next = NULL;
        tail = temp;
    }
    else if(pos==0 && !is_empty())
    {
        temp->data = elem;
        temp->next = head;
        head = temp;
    }
    else
    {
        while (currentPos != pos) {
        back = conductor;
        conductor = conductor->next;
        currentPos++;
        }//while
        //insert using back and conductor
        temp->data = elem;
        back->next = temp;
        temp->next = conductor;
    }
   }

//------------push_back---------------
template<typename T>
void SSLL<T>::push_back(T elem){
    Node<T> * conductor = new Node<T>();
    conductor = head;

    //if is empty create first node
    if (head == NULL) {
        Node<T> * temp = new Node<T>();
        temp->data = elem;
        head = temp;
        head->next = NULL;
        tail = head;

    }
    else if(head->next ==NULL){
       Node<T> * temp2 = new Node<T>();
        temp2->data = elem;
        head->next = temp2;
        tail = temp2;

    }//else if
    else {
        Node<T> * temp3 = new Node<T>();
        temp3->data = elem;
        tail->next =temp3;
        tail = temp3;
    }
}

//------------push_front--------------
template<typename T>
void SSLL<T>::push_front(T elem){
    Node<T> * conductor = new Node<T>();
    conductor = head;

    //if is empty create first node
    if (head == NULL) {
        Node<T> * temp = new Node<T>();
        temp->data = elem;
        head = temp;
        head->next = NULL;
        tail = head;
    }

    else if(!is_empty()){
        insert(elem, 0);
    }
}
//-------------replace----------------

template<typename T>
T SSLL<T>::replace(T elem, size_t pos)
{   Node<T> * conductor = new Node<T>();
    conductor = head;
    size_t index =0;                       //index used to find position
    T temp;

    if(pos > length() || (pos != 0 && is_empty()) || is_empty()){
    throw std::runtime_error("Out of range");
    }

    if ( pos==0 ) {
        temp = head->data;                //set temp to hold original element;
        head->data = elem;               //set head to hold new element;
        return temp;
    }
    while (conductor->next != NULL) {     //traverse through list
        conductor = conductor->next;
        index++;                         //increment current index
        if(index == pos){
            temp = conductor->data;
            conductor->data = elem;
        }//if
    }//while

    return temp;
}

//----------------remove--------------
template<typename T>
T SSLL<T>::remove(size_t pos){
    Node<T> * conductor = new Node<T>();
    Node<T> * back = new Node<T>();
    conductor = head;

    T temp;
    size_t index =0;


    if (pos>length()) {
        throw std::runtime_error("Out of range");
    }
    else if (is_empty())
    {
        throw std::runtime_error("List is empty");
    }
    else if(length() == 1){
        temp = head->data;
        //std::cout << head->data << std::endl;
        clear();
        return temp;
    }

    else {while (conductor->next != NULL) {   //traverse through list
        back = conductor;
        conductor = conductor->next;
        index++;
        //keep position

        if(pos==0&& length()>1)
        {
            temp = head->data;
            head = head->next;
            return temp;
        }

        else if(index == pos){
            temp = conductor->data;
            back->next = conductor->next;
            delete conductor;
        }
        }//if
    }//while

    return temp;
}

//---------------pop_back------------
template<typename T>
T SSLL<T>::pop_back(){
    Node<T> * conductor =new Node<T>();
    Node<T> * back = new Node<T>();
    conductor = head;
    back = head;

     //Test if list is empty
     if(is_empty()) {
      throw std::runtime_error("List is Empty");
    }
    while (conductor->next != NULL) {
        back = conductor;
        conductor = conductor->next;
        //std::cout<< "con"<< conductor->data << std::endl;
        //std::cout <<"back"<< back->data << std::endl;

    }
    if (conductor == head) {    //if popping last element then set head to Null
        head =NULL;
        tail =NULL;
    }
    //if (head == NULL)
    //throw std::runtime_error("List is empty");

    T temp = tail->data;
    conductor = NULL;
    back->next = NULL;
    tail = back;
    return temp;
}

//-----------------pop_front-----------
template<typename T>
T SSLL<T>::pop_front(){
  Node<T> * conductor = new Node<T>();

  if(is_empty()) {
   throw std::runtime_error("List is Empty");
 }

  conductor = head;

  //Get the value of head to return
  T temp = head->data;

  //Set head to the new head node
  head = head->next;

  //delete the previous head node
  delete conductor;

  if (length()==0) {    //if popping last element then set head to Null
      tail = NULL;
  }
  return temp;
}

//-----------------item_at-------------
template<typename T>
T SSLL<T>::item_at(size_t pos){
    Node<T> * conductor = new Node<T>();
    conductor = head;

    size_t currentPos = 0;
    if(is_empty()){
        throw std::runtime_error("List is empty");
    }

    if(pos > length())
    {
        throw std::runtime_error("Out of bounds");
    }
    else if (pos == 0) {
      return head->data;
    }
    while (currentPos != pos) {
        conductor = conductor->next;
        currentPos++;
    }
    return conductor->data;
}
//-----------------peek_back-----------
template<typename T>
T SSLL<T>::peek_back(){
    if(head == NULL)
    throw std::runtime_error("List is empty");
    return tail->data;
}
//----------------peek_front-----------
template <typename T>
T SSLL<T>::peek_front()
{   if(head == NULL){
    throw std::runtime_error("List is Empty");
    return NULL;
    }
    return head->data;
}

//---------------is_empty--------------
template <typename T>
bool SSLL<T>::is_empty()
{   if(length()== 0)
        return true;
        return false;
}
//---------------is_full---------------
template <typename T>
bool SSLL<T>::is_full(){
    if (length()== max_nodes) {
        return true;
    }
    return false;
}

//---------------length----------------
template <typename T>
size_t SSLL<T>::length(){
    Node<T> * conductor;
    conductor = head;
    size_t len = 0;
    if (head==NULL) {
        return 0;
    }

    while (conductor != NULL) {
        conductor = conductor->next;
        ++len;
        }
    return len;
}

//--------------clear-----------------
template <typename T>
void SSLL<T>::clear(){
    Node<T> * conductor = new Node<T>();
    Node<T>  * back =new Node<T>();
    conductor = head;
    back=head;

    while (conductor != NULL) {
        back = conductor;
        conductor = conductor->next;
        delete back;

    }
    head = NULL;

}

//-------------contains-------------
template <typename T>
bool SSLL<T>::contains(T elem, bool equals_function(T &a, T &b)){
    Node<T> * conductor = new Node<T>();
    conductor = head;
    bool equal = false;
    while(conductor){
     if(equals_function(elem,conductor->data) == true)
     return true;
      conductor = conductor->next;
    }
    return false;
}

//--------------print-----------------
template <typename T>
void SSLL<T>::print(std::ostream &stream){
    Node<T> * conductor = new Node<T>();
    conductor = head;
    //size_t index = 0;
    if (is_empty()) {
        stream << "<empty list>";
    }
    else if(!is_empty()){
        while (conductor->next != NULL) {


            stream << "<" << conductor->data << ">";
            stream << ",";
            conductor = conductor->next;
        }
        stream <<"<" << conductor->data << ">";
    }
}

//--------------contents-------------
template<typename T>
T * SSLL<T>::contents(){
    T * arr = new T[length()];
    Node<T> * conductor = new Node<T>();
    conductor = head;
    size_t index = 0;
    while (conductor != NULL) {
        conductor = conductor->next;
        arr[index] = pop_back();
        index++;
    }
    arr[index] = pop_back();

    return arr;
}

}//namespace

#endif /* SSLL_h */
