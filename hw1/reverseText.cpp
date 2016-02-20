#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void reversePrint( stringstream &input, int stringCount ){
	if (stringCount == 1){
		string current;
		input >>  current;
		cout << current << endl;
	}
	else{
		string hold;
		input >> hold;
		reversePrint(input, stringCount -1);
		cout << hold << endl;
	}
}

int main(int argc, char* argv[]){
	if(argc < 2){
		cerr<<"Please provide a string of characters.";
		return 1;
	}
	ifstream inFile(argv[1]);
	stringstream ss;
	int wordCounter =0;
	inFile >> wordCounter;
	ss << inFile.rdbuf();
	reversePrint (ss, wordCounter);
}