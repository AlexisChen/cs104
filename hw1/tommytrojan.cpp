#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int floors;
  int *floorsizes;
  
  string ***trojans;
  string curr;

  input >> floors;
  trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
  }
  getline(input,curr);
  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;

	  if (curr == "MOVEIN") {
		  int i,k;
		  ss >> i;
		  ss >> k;
		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	if(i >= floors){
		  		output << "Error - floor "<< i << " does not exist"<<endl;
		  	}
		  	else if(floorsizes[i]!= 0){
		  		output << "Error - floor "<< i << " is not empty" <<endl;
		  	}
		  	else{
		  		floorsizes[i] = k;
		  		trojans[i] = new string*[k];
		  		for(int j = 0; j < k; j++){
		  			trojans[i][j] = NULL;
		  		}
		  	}
		  }
	  }

	  else if (curr == "MOVEOUT") {
	  	int i;
	  	ss >> i;
	  	if(ss.fail()){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else{
	  		if(floorsizes[i]== 0){
		  		output << "Error - floor "<< i << " is already empty" <<endl;
		  	}
	  		else if(i >= floors){
	  			output << "Error - floor "<< i << " does not exist"<<endl;
	  		}
	  		else{
	  			int j = floorsizes[i];
	  			for(int k = 0; k < j; k++){
	  				if(!trojans[i][k]){
	  				
	  					delete[] trojans[i][k];
	  				}
	  			}
	  			floorsizes[i] = 0;
	  			delete[]trojans[i];
	  			trojans[i] = NULL;
	  		}
	  	}
	  }

	  else if (curr == "OBTAIN") {
	  	int i, j, k;
	  	ss >> i >> j >> k;
	  	if(ss.fail()){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else{
	  		if(i >= floors){
	  			output << "Error - There is no student "<< j << " on floor "<< i << endl;
	  		}
	  		else if(j >= floorsizes[i]){
	  			output << "Error - There is no student "<< j << " on floor "<< i << endl;
	  		}
	  		else if(trojans[i][j]){
	  			output << "Error - student "<< j << " already has possessions"<<endl;
	  		}
	  		else{
	  			trojans[i][j] = new string[k];
	  			for(int h = 0; h < k; h++){
	  				ss >> trojans[i][j][h];
	  			}
	  		}
	  	}
	  }

	  else if (curr == "OUTPUT") {
	  	int i, j;
	  	ss >> i >> j;
	  	if(ss.fail()){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else{
	  		if(i >= floors){
	  			output << "Error - There is no student "<< j << " on floor "<< i << endl;
	  		}
	  		else if(j >= floorsizes[i]){
	  			output << "Error - There is no student "<< j << " on floor "<< i << endl;
	  		}
	  		else if(trojans[i][j] == NULL){
	  			output << "Error - student "<< j << " has no possession"<<endl;
	  		}
	  		else{
	  			int k = sizeof(trojans[i][j])/sizeof(trojans[i][j]);
	  			for(int h = 0; h <= k; h++){
	  					output << trojans[i][j][h]<<endl;
	  			}
	  		}
	  	}
	  }
	  else {
	  	output <<"Error - incorrect command"<<endl;
	  }
  }

  for (int i = 0; i < floors; i++){
  	for(int j = 0; j < floorsizes[i]; j++){
	   delete[] trojans[i][j];
    }
  	delete[] trojans[i];
  }
  delete[] trojans;
  delete[] floorsizes;
  return 0;
}
