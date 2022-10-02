#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	ifstream ifile (argv[1]);
	if(ifile.fail()){
		cout << "\033[1;31mError:\033[0m Can't read the input file"<<endl;
		return 1;
	}
	int base;
	string text;
	ifile >> base;
	string pk;
	ifile >> pk;
	string num;
	ifile >> num;
	
	try
	{
		BigInt mod(num,base);
		BigInt pt(pk,base);
		while(ifile >> text)
		{
			BigInt ctext(text,base);
			BigInt dtext = modPow(ctext,pt,mod);
			cout << (char)dtext.to_int();
		}
		cout << endl;
	}

	catch(const exception& e){
      cout<<e.what()<<endl;
		return -1;
	}
	
	return 0;
}
