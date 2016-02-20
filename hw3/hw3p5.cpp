#include <iostream>
#include <fstream>
#include "stackint.h"
#include <sstream>
#include <cmath>

using namespace std;

const int OPEN_PAREN = -1;
const int PLUS = -2;
const int MULTIPLY = -3;
const int SHIFTLEFT = -4;
const int SHIFTRIGHT = -5;
const int CLOSE_PAREN = -6;

//This function helps push an integer to the stack

void pushNum(StackInt& thisStack2){
	int firstNum = thisStack2.top();
	thisStack2.pop();
	int digit=1;
	int sum = firstNum;
	if(thisStack2.empty()){

	}
	else{
		while(thisStack2.top()>=0){
			int besumed = thisStack2.top();
			thisStack2.pop();
			int fang = (pow(10,digit));
			sum = sum + fang*besumed;
			digit++;
		} 
	}
	thisStack2.push(sum);
}

/*
This function calculates the operatoins in a parenthesis
*/
int calculateBack(StackInt& thisStack){
	int first = thisStack.top();
	thisStack.pop();
	int op = thisStack.top();
	if(thisStack.empty()){
		thisStack.push(first);
		return -1;
	}
	if(op==OPEN_PAREN){
		thisStack.pop();
		thisStack.push(first);
		return first;
	}
	int second;
	while(op!=OPEN_PAREN){
		thisStack.pop();
		if(op == PLUS){
			second = thisStack.top();
			thisStack.pop();
			second = second+first;
		}
		else if(op == MULTIPLY){
			second = thisStack.top();
			thisStack.pop();
			second = second*first;
		}
		first = second;
		if(op!=thisStack.top()&&thisStack.top()!=OPEN_PAREN){
			return -1;
		}
		op = thisStack.top();
	}
	thisStack.pop();
	if(thisStack.empty()){
		thisStack.push(first);
	    return first;
	}
	int checkshift = thisStack.top();
	int left = 0, right = 0;
	while(checkshift==SHIFTLEFT||checkshift==SHIFTRIGHT){
		if(checkshift==SHIFTLEFT){
			left++;
			thisStack.pop();
			if(thisStack.empty()){
				break;
			}
			checkshift = thisStack.top();
		}
		else if(checkshift==SHIFTRIGHT){
			right++;
			thisStack.pop();
			if(thisStack.empty()){
				break;
			}
			checkshift = thisStack.top();
		}
	}
	first = first/pow(2,right)*pow(2,left);
	thisStack.push(first);
	return first;
}

void numPro(stringstream & s, StackInt& a){
	int fnum = a.top();
	a.pop();
	if(a.empty()){
		a.push(fnum);
	}
	else{
		a.push(fnum);
		while(a.top()>=0){		
			char fornumber;
			s >> fornumber;
			if(fornumber == '<'){
				a.push(SHIFTLEFT);
			}
			else if(fornumber =='>'){
				a.push(SHIFTRIGHT);
			}
			else if(fornumber=='+'){
				a.push(PLUS);
			}
			else if(fornumber=='*'){
				a.push(MULTIPLY);
			}
			else{
				a.push((int)fornumber - 48);
			}
		}
		s.unget();
		a.pop();
	}
	pushNum(a);
}

int main(int argc, char* argv[] ){
	if(argc < 2){
    cout << "Please provide an input and output file." << endl;
    return 1;
  }
	ifstream inFile(argv[1]);
	string myline;
	while( getline(inFile, myline) ){
		if(myline.empty()){
		}
		else{
			StackInt myStack;
			int doopen = 0;
			int fault = 0;
			stringstream ss(myline);
			char current;		
			while(ss >> current){
				if(current == '('){
					doopen = 1;
					myStack.push(OPEN_PAREN);
					char temp;
					ss >> temp;
					if(temp=='+'||temp=='*'){
						fault = 1;
						break;
					}
					ss.unget();	
				}
				else if(current == '+'){
					if(doopen==0){
						fault = 1;
						break;
					}
					myStack.push(PLUS);
					char temp;
					ss >> temp;
					if(temp=='+'||temp=='*'){
						fault = 1;
						break;
					}
					ss.unget();	
				}
				else if(current == '*'){
					if(doopen==0){
						fault = 1;
						break;
					}
					myStack.push(MULTIPLY);
					char temp;
					ss >> temp;
					if(temp=='+'||temp=='*'){
						fault = 1;
						break;
					}
					ss.unget();	
				}
				/*
				The following function deal with the operations after '<'/'>';
				it immediately round down the number right after the operator,
				and pushes the number into the stack
				if it is a opern parenthesis after the operator, the function will
				push the shiftleft/shiftright signs for later computation. 
				*/
				else if(current == '<'||current == '>'){
					int left = 0, right = 0;
					if(current == '<'){
						left++;
						myStack.push(SHIFTLEFT);
					}
					if(current == '>'){
						right++;
						myStack.push(SHIFTRIGHT);
					}
					while(myStack.top()!=PLUS && myStack.top()!=MULTIPLY && myStack.top()!= CLOSE_PAREN){
						char myOperator;
						ss>>myOperator;
						if(myOperator=='<'){
							left++;
							myStack.push(SHIFTLEFT);
						}
						else if(myOperator=='>'){
							right++;
							myStack.push(SHIFTRIGHT);
						}
						else if(myOperator=='+'){
							myStack.push(PLUS);
						}
						else if(myOperator=='*'){
							myStack.push(MULTIPLY);
						}
						else if(myOperator == ')'){
							myStack.push(CLOSE_PAREN);
						}
						else if(myOperator == '('){
						    myStack.push(OPEN_PAREN);
							break;
						}
						else{
							myStack.push((int)myOperator - 48);
							numPro(ss, myStack);
							if(doopen == 0){
								break;
							}
						}
					}
					int currentOp = myStack.top();
					int currentNum;
					if(currentOp==OPEN_PAREN){
						myStack.pop();
						ss.unget();
					}
					else if(currentOp>0){
						currentNum = currentOp;
						myStack.pop();
						currentNum = currentNum/pow(2,right)*pow(2,left);
						for(int i = 0; i <(left+right);++i){
							myStack.pop();
						}
						myStack.push(currentNum);
					}
					else if(currentOp<0){
						myStack.pop();
						currentNum = myStack.top();
						myStack.pop();
						currentNum = currentNum/pow(2,right)*pow(2,left);
						for(int i = 0; i <(left+right);++i){
							myStack.pop();
						}
						myStack.push(currentNum);
						ss.unget();
					}
				}
					
				else if(current == ')'){
					int result =calculateBack(myStack);
					if(result == -1){
						break;
					}
				}
				else{
					myStack.push((int)current - 48);
					numPro(ss, myStack);			
				}
			}
			if(fault==1){
				cerr<<"Malformed"<<endl;
			}
			else{
				int final = myStack.top();
	    		myStack.pop();
	    		if(myStack.empty()){
				    cout<< final<<endl;
	    		}
	    		else{
				    cout<<"Malformed"<<endl;
	    		}
			}
		}
	}
}