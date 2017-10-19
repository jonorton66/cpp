#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom(){
	
    return alphanum[rand() % stringLength];
}

int main(){
	
    srand(time(0));
    std::string Str;
    for(unsigned int i = 0; i < 9; ++i){
		Str += genRandom();
		
    }
	
	ofstream myfile;
	myfile.open ("/Users/mac/Desktop/Password.txt");
	myfile << Str;
	myfile.close();
	
	//cout << "\n";
	//cout << Str << endl;
	//cout << "\n";
	
return 0;
}


