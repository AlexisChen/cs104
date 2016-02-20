#include "llistint.h"
#include "gtest/gtest.h"

class LListIntTest : public testing::Test{
protected:
	LListIntTest(){

	}
	virtual ~LListIntTest(){

	}
	
	virtual void SetUp(){
		intlist.insert(0,4);
		intlist.insert(0,3);
		intlist.insert(0,2);
		intlist.insert(0,1);
		intlist.insert(0,0);
	}
	virtual void TearDown(){
		intlist.clear();

	}
	
	LListInt intlist;
};

TEST_F(LListIntTest, copyConstructorNominal){
	LListInt deepCopy(intlist);
	for(int i = 0; i < 5; ++i){
		EXPECT_EQ(deepCopy.get(i), i);
	}
	intlist.set(0,1);
	EXPECT_EQ(deepCopy.get(0), 0);
}

TEST_F(LListIntTest, AssignmentOperatorNominal){
	LListInt temp;
	temp.insert(0,1);
	temp.insert(0,1);
	temp.insert(0,1);
	temp = intlist;
	for(int i = 0; i < 5; ++i){
		EXPECT_EQ(temp.get(i), i);
	}
}

TEST_F(LListIntTest, ConcatenationOperatorNominal){
	LListInt temp;
	//LListInt sum;
	temp.insert(0,1);
	temp.insert(0,1);
	temp.insert(0,1);
	temp = temp + intlist;
	for(int i = 0; i < 3; ++i){
		EXPECT_EQ(temp.get(i), 1);
	} 
	for(int i = 3; i < 8; i++){
		EXPECT_EQ(temp.get(i), i-3);
	}
}

TEST_F(LListIntTest, AccessOperatorNominal){
	for(int i = 0; i < 5; ++i){
		EXPECT_EQ(intlist[i], i);
	}

}