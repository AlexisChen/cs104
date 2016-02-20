#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
   Item* tobeInsert = new Item;
   tobeInsert->prev = NULL;
   tobeInsert->next = NULL;
   tobeInsert ->val = val;
    
  if(loc < 0 || loc > size_){
    return;
  }
  else if(size_ == 0){
    
    head_ = tobeInsert;
    tail_ = tobeInsert;
  }
  else if(loc == 0){
    tobeInsert->next = head_;
    tobeInsert->next ->prev = tobeInsert;
    head_ = tobeInsert;
  }
  else if(loc == size_){
    tail_ -> next = tobeInsert;
    tobeInsert->prev = tail_;
    tail_ = tobeInsert;
  }
  else{
    Item* temp = getNodeAt(loc);
    tobeInsert->prev = temp->prev;
    tobeInsert->next = temp;
    temp -> prev -> next = tobeInsert;
    temp->prev = tobeInsert;
  }
  
  size_++;
  //delete tobeInsert;

}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
//valid location from 0 to size -1
  if(size_ == 0){
    return;
  }
  if(loc < 0 || loc > size_ -1){
    return;
  }
  Item* temp = getNodeAt(loc);
  if(size_== 1){
    head_ = NULL;
    tail_ = NULL;
  }

  else if(loc == 0){
    head_ = temp -> next;
    temp -> next ->prev = NULL;
  }
  else if(loc == size_-1){
    temp->prev->next = NULL;
    tail_ = temp -> prev;
  }
  else{
    temp->next->prev = temp -> prev;
    temp -> prev -> next = temp -> next;
  }
  delete temp;
  size_ --;
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{
//return a pointer to the i-th node 
  //help with insert and remove
  Item* temp = head_;
  for(int i = 0; i< loc; i++){
      temp = temp -> next;
  }
  return temp;


}

  /**
   * Copy constructor (deep copy)
   */
  LListInt::LListInt(const LListInt& other){
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
    int s = other.size();
    for (int i = 0; i < s; ++i){
      this->insert(i,other.get(i));
    }
  }

  /**
   * Assignment Operator (deep copy)
   */
  LListInt& LListInt::operator=(const LListInt& other){
    if(this == & other){
      return *this;
    }     
    else{
      this->clear();
      for (int i = 0; i < other.size(); ++i){
        this->insert(i,other.get(i));
      }
      return *this;
    }     
  }
  /**
   * Concatenation Operator (other should be appended to the end of this)
   */
  LListInt LListInt::operator+(const LListInt& other) const{
    LListInt sum(*this);
    for(int i = 0; i < other.size_; ++i){
      sum.insert(sum.size_, other.get(i));
    }
    return sum;
  }
  /**
   * Access Operator
   */
  int const & LListInt::operator[](int position) const{
    return this->get(position);
  }

