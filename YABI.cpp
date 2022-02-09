#include <iostream>
#include <fstream>
#include <string>
#include "BfInterpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
	string instructions;
	
	//Checking the arguments
	if (argc != 2) {
		cout << "[!] Usage: " << argv[0] << " input.bf" << endl;
		return 1;
	}

	//Reading the file
	ifstream file;
	file.open(argv[1]);
	while (file.good()) {
		char c = file.get();
		if ((int)c > 0)
			instructions.push_back(c);
	}
	file.close();

	//Check the loaded instructions
	if (!instructions.length()) {
		cerr << "[x] No instructions have been loaded" << endl;
		return 1;
	}

	//I start interpreting the code
	BfInterpreter bf = { instructions };
	bf.runCode();

	return 0;
}