//
//  CDAL.h
//  ADT_List
//
//  Created by Timothy Botelho on 9/30/17.
//  Copyright © 2017 Timothy Botelho. All rights reserved.
//
//
//**************to do****************************
//pop front
//pop back
//remove
//replace
//push back
//insert
//print
//contains
//shift all left(pos)

#ifndef CDAL_h
#define CDAL_h

#include "ADT_List.h"

using namespace std;

namespace COP3530{
template<typename T>
class CDAL:ADT_List<T>{

    //---------Chainded Dynamic Array List-------------
public:
    //function declerations
    CDAL();
    ~CDAL() override;
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

    int find_node_count();
    int find_node_count_used();
    Node<T> * find_cur_node(int pos);
    Node<T> * find_last_used_node();
    void remove_node();
    void create_node();
    void shift_to_next();
    void last_to_first(Node<T> * curr);
    void first_to_last(Node<T> * curr);
    void shift_arr_right(Node<T> * curr);
    void shift_arr_right(Node<T> * curr, int pos);
    void shift_arr_left(Node<T> * curr,int pos);
    void print_cur_node(Node<T> * curr);
    void shift_all_right();
    void shift_all_right(int pos);
    void shift_all_left(int pos);
    Node<T> * find_last_full_node();
    void print_all_nodes();

    void create_test_data();
    void reverse_node_traversal();
    void test_shift();
    void print_node_status(Node<T> * node);

    //member variables
    Node<T> * head;
    Node<T> * tail;

};

//---------constructor-----------------

template<typename T>
CDAL<T>::CDAL(){head = new(Node<T>),tail = new(Node<T>);
    head->next = new Node<T>;
    tail->next = head->next;
    T* first_arr = new T[50];
    head->next->ptr = first_arr;
    head->next->cur_arr_size = 0;

}

//---------destructor-----------------
template<typename T>
CDAL<T>::~CDAL(){


}

//-----------insert-------------------
template<typename T>
void CDAL<T>::insert(T elem, size_t pos){

    if (pos > length()) {
        throw std::runtime_error("Out of Bounds");
    }

      T * ptr2 = find_cur_node(pos)->ptr;
      ptr2 = ptr2 + (pos%50);
      shift_all_right(pos);
      *ptr2 = elem;

}

//------------push_back---------------
template<typename T>
void CDAL<T>::push_back(T elem){

  T * ptr2 =head->next->ptr;

  //if list is empty
  if (head->next->is_empty) {
      *ptr2 = elem;
      head->next->is_empty=false;
      head->next->cur_arr_size++;
  }
  //edge case of when an item is on end of array
  else if(find_last_used_node()->is_full){


    //create a node if there is no node on the end
    if(find_node_count_used() == find_node_count() && find_last_used_node()->is_full){
      create_node();

    }

    //set a ptr to the first spot in the next empty array
    T * ptr3 = find_last_used_node()->next->ptr;
    Node<T> * temp = new Node<T>;
    temp = find_last_used_node()->next;
    temp->is_empty = false;
    temp->cur_arr_size++;
    *ptr3 = elem;
  }

  //for all other cases
  else{
    //find last node used
    T * ptr2 = find_last_used_node()->ptr;
    ptr2 = ptr2 + find_last_used_node()->cur_arr_size++;
    *ptr2 = elem;
    if(find_last_used_node()->cur_arr_size == 50)
      find_last_used_node()->is_full = true;
  }
}

//------------push_front--------------
template<typename T>
void CDAL<T>::push_front(T elem){

    T * ptr2 =head->next->ptr;

    if (head->next->is_empty) {
        *ptr2 =elem;
        head->next->is_empty=false;
        head->next->cur_arr_size++;
    }

    else{
        shift_all_right();
        *ptr2 =elem;
    }
}

//-------------replace----------------

template<typename T>
T CDAL<T>::replace(T elem, size_t pos)
{
    if (pos>length() || is_empty()) {
        throw std::runtime_error("out of bounds");

    }
    T * ptr2 = find_cur_node(pos)->ptr;
    ptr2 = ptr2 + pos;
    T temp = *ptr2;
    *ptr2 = elem;

    return temp;
}

//----------------remove--------------
template<typename T>
T CDAL<T>::remove(size_t pos){
    T temp;

    if(is_empty() || pos > length())
      throw std::runtime_error("out of bounds or list is empty");
      else if(length() == 1){
      //create temp holder
      temp = item_at(pos);
      //shift items left
      shift_all_left(pos);
    }
    else{
      temp = item_at(pos);
      //shift items left
      shift_all_left(pos);
    }
    return temp;
}

//---------------pop_back------------
template<typename T>
T CDAL<T>::pop_back(){
    //find node of back
    Node<T> * temp = new Node<T>;
    if (is_empty()) {
        throw std::runtime_error("list is empty");
    }
    temp = find_cur_node(length());
    T back = *(temp->ptr + temp->cur_arr_size-1);
    temp->cur_arr_size--;
    return back;
}

//-----------------pop_front-----------
template<typename T>
T CDAL<T>::pop_front(){
    T ptr2 = *(head->next->ptr);
    shift_all_left(0);
    return  ptr2;
}

//-----------------item_at-------------
template<typename T>
T CDAL<T>::item_at(size_t pos){
    Node<T> * temp = new Node<T>;
    T * ptr2 = head->next->ptr;

    if(pos<50)
    {
        ptr2 += pos;
        return *ptr2;
    }
    else
    {
        temp = find_cur_node(pos);
        ptr2 = temp->ptr;
        ptr2 += (pos%50);
        return *ptr2;
    }
}

//-----------------peek_back-----------
template<typename T>
T CDAL<T>::peek_back(){
    Node<T> * temp = new Node<T>;

    temp = find_cur_node(length());
    T * ptr = temp->ptr;
    int pos = temp->cur_arr_size -1;

    return *(ptr + pos);
}
//----------------peek_front-----------
template <typename T>
T CDAL<T>::peek_front()
{
    T * ptr2 = head->next->ptr;
    return *ptr2;
}

//---------------is_empty--------------
template <typename T>
bool CDAL<T>::is_empty()
{
    if(head->next == tail->next && head->next->cur_arr_size == 0)
    return true;

    else
    return false;
}

//---------------is_full---------------
template <typename T>
bool CDAL<T>::is_full(){

    return false;
}

//---------------length----------------
template <typename T>
size_t CDAL<T>::length(){
    int length = 0;
    if(head->next->cur_arr_size == 0)
        return length;

    if(find_node_count() == 1)
    {
        length = head->next->cur_arr_size;
    }

    else
    {
        if (find_last_full_node() == find_last_used_node()) {
            length = 50 * (find_node_count_used()-1);
        }
        else
        length = (find_node_count_used() -1) * 50;
        length += find_last_used_node()->cur_arr_size;
    }

    return length;
}

//--------------clear-----------------
template <typename T>
void CDAL<T>::clear(){

    Node<T> * front = new Node<T>;

    front = head->next;

    while (front != NULL) {
        remove_node();
        front = front->next;
    }
    tail->next=head->next;
    head->next->is_empty =true;
    head->next->is_full = false;
    head->next->cur_arr_size = 0;
    T * temp = head->next->ptr;
    for (int i= 50; i>=0 ; i--) {
        *(temp + i) = -1;
    }
}

//-------------contains-------------
template <typename T>
bool CDAL<T>::contains(T elem,  bool equals_function(T &a, T &b)) {
  //Start at the beginning of the list
  //work through list checking every item
  T temp;

for(int i = 0; i < length(); i++){
  temp = item_at(i);
  if(equals_function(temp,elem))
    return true;
}
  return false;
}

//--------------print-----------------
template <typename T>
void CDAL<T>::print(std::ostream &stream){

       if (is_empty()) {
           stream << "<empty list> \n ";
       }
       else if(!is_empty()){
         size_t it = 0;
         size_t size = length()-1;
           while (it != size) {
               stream << "<" << item_at(it++) << ">" ;
               stream << ",";
           }
           stream << "<" << item_at(it) << ">"  << " \n";
       }
}

//--------------contents-------------
template<typename T>
T * CDAL<T>::contents(){
    long len =length();
    T * temp_arr = new T[len];
    for(long i = length(); i>=0; i--) {
        temp_arr[i] = item_at(i);
    }
    return temp_arr;
}

template<typename T>
int CDAL<T>::find_node_count(){
    Node<T> * temp = new Node<T>;
    temp = head->next;
    int count = 1;
    while (temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

template<typename T>
Node<T> * CDAL<T>::find_cur_node(int pos){
    Node<T> * temp = new Node<T>;
    temp = head->next;

    if (find_node_count() == 1) {

        return head->next;
    }
    else{
        int find_curr = pos/50;
        //cout << "find curr node" << endl;
        while (find_curr != 0) {
        temp = temp->next;
        find_curr--;
            //cout << "while" << endl;
        }
        //cout << temp << endl;
        return temp;
    }
}

template<typename T>
void CDAL<T>::create_node(){
Node<T> * temp = new  Node<T>;
Node<T> * front = new  Node<T>;
Node<T> * back = new  Node<T>;

    T* first_arr = new T[50];
    temp->ptr = first_arr;
    front = head->next;
    back = front;

    while(front->next != NULL )
    {
        back = front;
        front = front->next;
        //cout << count++ << endl;
    }
    temp->prev = front;
    front->next = temp;
    temp->next = NULL;
    tail->next = temp;
}

template<typename T>
void CDAL<T>::remove_node(){
    Node<T> * front = new Node<T>;
    Node<T>  * back = new Node<T>;
    front = head->next;
    int count = 0;
    while(front->next != NULL )
    {
        back = front;
        front = front->next;
        cout << count++ << endl;
    }
    //delete front;
    back->next = NULL;
    tail->next = back;
}

template<typename T>
void CDAL<T>::last_to_first(Node<T> * curr){
    T * ptr2 = curr->ptr + 49;              //ptr2 points to last element in current node
    T temp = *ptr2;                         //set temp to value of that last element
    T* ptr3 = curr->next->ptr;              //ptr3 points to first element in next node
    *ptr3 = temp;
}

template<typename T>
void CDAL<T>::first_to_last(Node<T> * curr){
    T * ptr2 = curr->next->ptr;              //ptr2 points to first in next node
    T temp = *ptr2;
    *ptr2 = 0;
    T* ptr3 = curr->ptr +49;                  //ptr3 points to last element in current node
    *ptr3 = temp;
}

template<typename T>
void CDAL<T>::shift_arr_right(Node<T> * curr){
    int size = curr->cur_arr_size - 1;
    T * ptr2 = curr->ptr;
    T * ptr3 = curr->ptr;
    for (int i = size; i>= 0; i--) {

        ptr2 += i;
        ptr3 += i + 1;
        *ptr3 = *ptr2;
        ptr2 = ptr3 = curr->ptr;
    }
}

template<typename T>
void CDAL<T>::shift_arr_right(Node<T> * curr,int pos){
    int size = curr->cur_arr_size - 1;
    T * ptr2 = curr->ptr;
    T * ptr3 = curr->ptr;
    for (int i = size; i>= pos - 1; i--) {

        ptr2 += i;
        ptr3 += i + 1;
        *ptr3 = *ptr2;
        ptr2 = ptr3 = curr->ptr;
    }
}

template<typename T>
void CDAL<T>::shift_arr_left(Node<T> * curr,int pos){
    //int pos1 = abs(50 - pos);
    int size = curr->cur_arr_size - 1;
    T * ptr2 = curr->ptr;
    T * ptr3 = curr->ptr;
    for (int i = pos; i< size; i++) {

        ptr2 += i;
        ptr3 += i + 1;
        *ptr2 = *ptr3;
        ptr2 = ptr3 = curr->ptr;
    }
}

template<typename T>
void CDAL<T>::shift_all_left(int pos){
    Node<T> * front = new Node<T>;
    Node<T> * back = new Node<T>;
    T temp1;
    T temp2;

    if(pos > length() - 1){
        throw runtime_error("Shift All Left: out of bounds");
        return;
    }

    if(is_empty()){
        throw runtime_error("Shift All Left: out of bounds");
        return;
    }

    if(head->next->cur_arr_size == 1){
        head->next->is_empty = true;
        head->next->cur_arr_size--;
        //cout << "head cur size =1" << endl;
        return;
    }

    //front set to current node where pos is
    front = find_cur_node(pos);
    back = front->next;



    // for first node only
    if(find_node_count_used() == 1){

        if(head->next->is_full){
            head->next->is_full = false;
        }
        shift_arr_left(head->next, 0);
        head->next->cur_arr_size--;
        if(head->next->cur_arr_size == 0){
            head->next->is_empty = true;
            head->next->is_full = false;
        }
        if(back->cur_arr_size == 0)
        {
            back->is_empty = true;
        }

        if(back->cur_arr_size == 49)
        {
            back->is_full = false;
        }
        return;
    }

    //two nodes exist and it's in the first node
    if(find_node_count_used() == 2 && find_cur_node(pos) == head->next ){
        shift_arr_left(front, pos);
        first_to_last(front);
        shift_arr_left(back, 0);
        find_last_used_node()->cur_arr_size--;
        if(back->cur_arr_size == 0)
        {
            back->is_empty = true;
        }

        if(back->cur_arr_size == 49)
        {
            back->is_full = false;
        }
        return;
    }

    //item is in last node and not in first position
    else if(find_cur_node(pos) == find_last_used_node() && pos % 50 == 0){
        //first_to_last(find_cur_node(pos));
        shift_arr_left(find_cur_node(pos),0);
        find_cur_node(pos)->cur_arr_size--;
        if(find_cur_node(pos)->cur_arr_size == 0)
        {
            find_cur_node(pos)->is_empty = true;
        }

        if(find_cur_node(pos)->cur_arr_size == 49)
        {
            find_cur_node(pos)->is_full = false;
        }
        return;
    }

    //item is in last node and not in first position
    else if(find_cur_node(pos) == find_last_used_node()){
        shift_arr_left(back, pos);
        back->cur_arr_size--;
        //cout << "item in last node" << endl;
        return;
    }

    else{

        //for when there is one item left in last node
        if(find_last_used_node()->cur_arr_size == 1){
            while (front->next != find_last_used_node()) {

                //for the first node with a position designated
                if( front == find_cur_node(pos)){
                    shift_arr_left(front, pos);
                    first_to_last(front);

                    //cout << "first if" << endl;
                }
                else{
                    shift_arr_left(front,0);
                    first_to_last(front);
                    //cout << "else" << endl;
                }
                front = back;
                back = back->next;

                //cout << "while" << endl;

            }//while
            if(back == find_last_used_node()){
                shift_arr_left(front,0);
                first_to_last(front);
                //shift_arr_left(back,0);
            }

            find_last_used_node()->cur_arr_size--;
            if(back->cur_arr_size == 0)
            {
                back->is_empty = true;
            }

            if(back->cur_arr_size == 49)
            {
                back->is_full = false;
            }

            }//if


        else{
            while (front->next != find_last_used_node()) {

                //for the first node with a position designated
                if( front == find_cur_node(pos)){
                    shift_arr_left(front, pos);
                    first_to_last(front);
                }
                else{
                    shift_arr_left(front,0);
                    first_to_last(front);

                }
                front = back;
                back = back->next;

                //cout << "2nd while" << endl;

            }//while
            if(back == find_last_used_node()){
                shift_arr_left(front,0);
                first_to_last(front);
                shift_arr_left(back,0);
            }

            find_last_used_node()->cur_arr_size--;
        }

        }//else

    //if node decreases in size
    if(back->cur_arr_size == 0)
    {
        back->is_empty = true;
    }

    if(back->cur_arr_size == 49)
    {
        back->is_full = false;
    }

}

template<typename T>
void CDAL<T>::print_cur_node(Node<T> * curr)
{
    int size = curr->cur_arr_size - 1;
    T * ptr2 = curr->ptr;
    for (int i = 0; i <= size; i++) {
        cout << "arr[" << i << "] = " << *(ptr2+i) <<endl;
    }
    //cout << "print add" << curr <<endl;
}

template<typename T>
void CDAL<T>::test_shift()
{
    //create_test_data();

    for(int i =50; i>= 0; i--)
    {
      push_front(i);
    }
    //T * arr =contents();

    for(int i =50; i>= 0; i--)
    {
        cout << pop_front() << endl;
    }


    print_all_nodes();


}

//-------------Last node used------------------
template<typename T>
Node<T> * CDAL<T>::find_last_used_node(){
    Node<T> * front = new Node<T>;
    Node<T>  * back = new Node<T>;
    front = tail->next;
    back = front;

    if (tail->next->is_full == true) {
        return tail->next;
    }
    if (find_node_count_used() == 1) {
        return head->next;
    }

    while (front->prev != head) {
        back = front;
        front = front->prev;
        if (front->is_full && back->is_empty) {
            return front;
        }
        else if(front->is_full && !back->is_empty)
            return back;
    }

    return back;
}

//-------------Last full node------------------
template<typename T>
Node<T> * CDAL<T>::find_last_full_node(){

    Node<T> * front = new Node<T>;
    Node<T>  * back = new Node<T>;
    front = head->next;
    back = nullptr;

    if (tail->next->is_full == true) {
        return tail->next;
    }

    if(find_node_count_used() == 1 && !head->next->is_empty && !head->next->is_full)
    {
        return NULL;
    }

    int count = find_node_count_used();

    while (count != 0) {
        back = front;
        front = front->next;
        count--;

        if (back->is_full && !front->is_full ) {
            return back;
        }
    }

    return back;
}

//-------------shift all right(pos)------------------
template<typename T>
void CDAL<T>::shift_all_right(int pos){

    Node<T> * front = new Node<T>;
    Node<T> * back = new Node<T>;
    front = find_last_used_node()->prev;
    back = find_last_used_node();

    //out of bounds error checking
    if(is_empty() || pos > length()){
        return;
    }

    //when node is less than 50 items
    if(head->next->cur_arr_size<50){
        shift_arr_right(head->next, pos);
        head->next->cur_arr_size++;
        head->next->is_empty = false;
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
        return;
    }

    //create new node when no nodes exist
    if(find_last_used_node()->is_full && find_last_used_node() == tail->next){
        create_node();
    }

    //when crossing from 1st node to 2nd node
    if(find_node_count_used() == 1 && head->next->is_full){
        last_to_first(head->next);
        shift_arr_right(head->next, pos);
        tail->next->cur_arr_size++;
        tail->next->is_empty = false;
        front = find_last_used_node()->prev;
        back = find_last_used_node();
        return;
    }

    //if pos is in last node and last node is full
    if(find_cur_node(pos) == find_last_used_node() && find_cur_node(pos)->is_full == true){
        last_to_first(find_cur_node(pos));
        shift_arr_right(find_cur_node(pos)->next, pos);
        find_cur_node(pos)->next->cur_arr_size++;
        find_cur_node(pos)->next->is_empty = false;
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
        //cout<< "if pos is in last node and last node is full" << endl;
        print_node_status(back);
        return;
    }

    //if pos is in last node and last node is not full
    if(find_cur_node(pos) == find_last_used_node()){
        shift_arr_right(find_cur_node(pos));
        find_cur_node(pos)->cur_arr_size++;
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
       // cout<< "if pos is in last node and last node is not full" << endl;
       // print_node_status(back);
        return;
    }

    if(find_last_used_node()->is_full && find_node_count_used() < 3){
        tail->next->cur_arr_size++;
        tail->next->is_empty = false;

        front = find_last_used_node()->prev;
        back = find_last_used_node();

        last_to_first(front);
        shift_arr_right(front);

        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
        //shift_arr_right(find_last_full_node());


        back =front;
        front = front->prev;
        //cout<< "full <3" << endl;

        last_to_first(front);
        shift_arr_right(front);
        //back->cur_arr_size++;

        return;
    }

    if (find_last_used_node()->cur_arr_size == 50) {
        find_last_used_node()->is_full = true;
    }
    if(find_last_used_node()->is_full && find_node_count_used() >= 3){
        back = tail->next;
        front = back->prev;
        last_to_first(front);
        //shift_arr_right(front);
        back->cur_arr_size++;
        back->is_empty = false;
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
        //cout<< "last node full****" << endl;
        //cout<< *(front->ptr) << endl;
        //cout<< *(back->ptr) << endl;
        //print_cur_node(back);
        //print_cur_node(front);
        print_node_status(front);
        back =front;
        front = front->prev;

        while(front != find_cur_node(pos)){

            shift_arr_right(back);
            last_to_first(front);
            //shift_arr_right(front);

            if(find_last_used_node() == back)

            {
                back->cur_arr_size++;

                if (back->cur_arr_size == 50) {
                    back->is_full = true;
                }
            }

            back =front;
            front = front->prev;

        }
        shift_arr_right(back);
        last_to_first(front);
        shift_arr_right(front, pos);
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full= true;
        }
        return;
    }

    if(find_node_count_used() >=3 && find_last_used_node()->cur_arr_size !=50){
        front = find_last_used_node()->prev;
        back = find_last_used_node();
        while(front != find_cur_node(pos)){

            shift_arr_right(back);
            last_to_first(front);
            //shift_arr_right(front);

            if(find_last_used_node() == back)

            {
                back->cur_arr_size++;

                if (back->cur_arr_size == 50) {
                    back->is_full = true;
                }
            }
            if (back->cur_arr_size == 50) {
                back->is_full = true;
            }
            back =front;
            front = front->prev;

        }
        shift_arr_right(back);
        last_to_first(front);
        shift_arr_right(front,pos);
        back->cur_arr_size++;


        print_node_status(back);
        print_node_status(front);
        //    print_cur_node(front);
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full= true;
        }
    }

    else {
        while(front != find_cur_node(pos)){
            shift_arr_right(back);
            last_to_first(front);

            if(find_last_used_node() == back)

            {
                back->cur_arr_size++;

                if (back->cur_arr_size == 50) {
                    back->is_full = true;
                }
            }
            back =front;
            front = front->prev;

        }
        shift_arr_right(back);
        last_to_first(front);
        shift_arr_right(front, pos);
        back->cur_arr_size++;

    }
    if (find_last_used_node()->cur_arr_size == 50) {
        find_last_used_node()->is_full = true;
    }
}

//-------------shift all right------------------
template<typename T>
void CDAL<T>::shift_all_right(){

    Node<T> * front = new Node<T>;
    Node<T> * back = new Node<T>;
    front = find_last_used_node()->prev;
    back = find_last_used_node();

    if(head->next->cur_arr_size<50){
        shift_arr_right(head->next);
        head->next->cur_arr_size++;
        head->next->is_empty = false;
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
        return;
    }

    if(find_last_used_node()->is_full && find_last_used_node() == tail->next){
        create_node();
    }

    if(find_node_count_used() == 1 && head->next->is_full){
        last_to_first(head->next);
        shift_arr_right(head->next);
        tail->next->cur_arr_size++;
        tail->next->is_empty = false;
        front = find_last_used_node()->prev;
        back = find_last_used_node();
        return;
    }
    if(find_last_used_node()->is_full && find_node_count_used() < 3){
        tail->next->cur_arr_size++;
        tail->next->is_empty = false;

        front = find_last_used_node()->prev;
        back = find_last_used_node();

        last_to_first(front);
        shift_arr_right(front);

        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }
        //shift_arr_right(find_last_full_node());


        back =front;
        front = front->prev;


        last_to_first(front);
        shift_arr_right(front);
        //back->cur_arr_size++;

        return;
    }

    if (find_last_used_node()->cur_arr_size == 50) {
        find_last_used_node()->is_full = true;
    }
    if(find_last_used_node()->is_full && find_node_count_used() >= 3){
        back = tail->next;
        front = back->prev;
        last_to_first(front);
        //shift_arr_right(front);
        back->cur_arr_size++;
        back->is_empty = false;
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full = true;
        }

        back =front;
        front = front->prev;

        while(front != head->next ){

            shift_arr_right(back);
            last_to_first(front);
            //shift_arr_right(front);

            if(find_last_used_node() == back)

            {
                back->cur_arr_size++;

                if (back->cur_arr_size == 50) {
                    back->is_full = true;
                }
            }

            back =front;
            front = front->prev;

        }
        shift_arr_right(back);
        last_to_first(front);
        shift_arr_right(front);
        if (find_last_used_node()->cur_arr_size == 50) {
            find_last_used_node()->is_full= true;
        }
        return;
         }

    if(find_node_count_used() >=3 && find_last_used_node()->cur_arr_size !=50){
        front = find_last_used_node()->prev;
        back = find_last_used_node();
        while(front != head->next ){

            shift_arr_right(back);
            last_to_first(front);
            //shift_arr_right(front);

            if(find_last_used_node() == back)

            {
                back->cur_arr_size++;

                if (back->cur_arr_size == 50) {
                    back->is_full = true;
                }
            }
            if (back->cur_arr_size == 50) {
                back->is_full = true;
            }
            back =front;
            front = front->prev;

        }
        shift_arr_right(back);
        last_to_first(front);
        shift_arr_right(front);

    }

    else {
        while(front != head->next ){
            shift_arr_right(back);
            last_to_first(front);

            if(find_last_used_node() == back)

            {
                back->cur_arr_size++;

                if (back->cur_arr_size == 50) {
                    back->is_full = true;
                }
            }
            back =front;
            front = front->prev;

        }
        shift_arr_right(back);
        last_to_first(front);
        shift_arr_right(front);
        back->cur_arr_size++;

            }
    if (find_last_used_node()->cur_arr_size == 50) {
        find_last_used_node()->is_full = true;
    }
}

//--------------find node count used-----------
template<typename T>
int CDAL<T>::find_node_count_used(){
    Node<T> * temp = new Node<T>;
    temp = head->next;
    int count = 0;
    while (temp != NULL && temp->is_empty == false) {
        temp = temp->next;
        count++;
    }
    return count;
}

//--------------reverse_node_traversal-----------
template<typename T>
void CDAL<T>::reverse_node_traversal()
{
    Node<T> * temp = new Node<T>;

    create_node();
    create_node();
    temp = tail->next;
    while (temp != head->next) {
        //cout << "traversal add: " << temp <<endl;
        temp = temp->prev;
    }
}

//--------------create_test_data-----------
template<typename T>
void CDAL<T>::create_test_data(){
    //create_node();
    //create_node();
   // create_node();
    T * tptr = head->next->ptr;

    for (int i = 1; i<50; i++) {
        tptr += i - 1;
        *tptr = i;
        head->next->cur_arr_size++;
        head->next->is_empty = false;
        tptr = head->next->ptr;
        if (head->next->cur_arr_size == 50) {
            head->next->is_full = true;
        }
    }

//    tptr = head->next->next->ptr;
//    for (int i = 51; i<=100; i++) {
//        tptr += i - 51;
//        *tptr = i;
//        head->next->next->cur_arr_size++;
//        head->next->next->is_empty = false;
//        tptr = head->next->next->ptr;
//        if (head->next->next->cur_arr_size == 50) {
//            head->next->next->is_full = true;
//        }
//    }
}

//--------------printnode status-----------
template<typename T>
void CDAL<T>::print_node_status(Node<T> * node){
    cout << "------NODE status-----" << endl;
    cout << "node add: "<< node << endl;
    cout << "node arr len: "<< node->cur_arr_size << endl;
    cout << "node is_empty: "<< node->is_empty << endl;
    cout << "node is_full: "<< node->is_full << endl;
    cout << "head->next" << head->next <<endl;
    cout << "tail->next" << tail->next <<endl;
    cout << "find node count: " << find_node_count() <<endl;
    cout << "find node count used: " << find_node_count_used() <<endl;
    cout << "find last used node: " << find_last_used_node() << endl;
    cout << "find last Full node: " << find_last_full_node() << endl;

}

//--------------print all nodes-----------
template<typename T>
void CDAL<T>::print_all_nodes(){
    Node<T> * front = new Node<T>;
    Node<T> * back = new Node<T>;
    front = head->next;
    back = front;

    if(head->next->cur_arr_size ==0)
    {
    cout << "list is empty" << endl;
    }
    else{
    while (front != find_last_used_node()) {
       // print_cur_node(back);
        print_cur_node(front);
        back = front;
        front = front->next;
    }
    print_cur_node(front);
    //print_cur_node(back);
    }
}
}
#endif /* CDAL_h */
