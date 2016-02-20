#include "stackint.h"
#include <iostream>

using namespace std;

StackInt::StackInt(){
	LListInt list;
}
StackInt::~StackInt(){
	list.clear();

}

/**
   * Returns true if the stack is empty, false otherwise
   */
bool StackInt::empty() const{
	return list.empty();
}

  /**
   * Pushes a new value, val, onto the top of the stack
   */
void StackInt::push(const int& val){
	list.insert(0,val);
}

  /**
   * Returns the top value on the stack
   */
int const &  StackInt::top() const{
	list.get(0);
}

  /**
   * Removes the top element on the stack
   */
void StackInt::pop(){
	list.remove(0);

}
