/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment#4: Registrar's Office Simulation
*/
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "DoubleLinkedList.h"

template <class Type>
class GenQueue{
  public:
    GenQueue(); // deafult constructor
    ~GenQueue(); //destructor

    //core functions
    void Enqueue(Type d);
    Type Dequeue();
    Type Peek();

    //aux functions
    bool isEmpty();
    unsigned int getSize();

  private:
    int currentSize;
    DoubleLinkedList<Type> *myList;

#endif
};

//constructor
template <class Type>
GenQueue<Type> :: GenQueue(){
  myList = new DoubleLinkedList<Type>();
  currentSize = 0;
}

//destructor
template <class Type>
GenQueue<Type> :: ~GenQueue(){
  delete myList;
}

//adds an item to the queue
template <class Type>
void GenQueue<Type> :: Enqueue(Type d){
  myList->Append(d);
  currentSize++;
}

//removes the item at the front of the queue
template <class Type>
Type GenQueue<Type> :: Dequeue(){
  if(isEmpty()){
    cout<<"Queue is empty!"<<endl;
  } else {
    Type tempData = myList->RemoveFront();
    currentSize--;
    return tempData;
  }
}

//shows what's at the front of the queue
template <class Type>
Type GenQueue<Type> :: Peek(){
  return (myList->Peek());
}

//shows us if there are any items left in the queue
template <class Type>
bool GenQueue<Type> :: isEmpty(){
  return (currentSize == 0);
}

//returns the number of items in the queue
template <class Type>
unsigned int GenQueue<Type> :: getSize(){
  return currentSize;
}
