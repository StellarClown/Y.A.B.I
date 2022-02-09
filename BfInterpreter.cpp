#include <iostream>
#include <string>
#include <vector>
#include "BfInterpreter.h"

using namespace std;

bool BfInterpreter::checkSyntax(const string& toCheck) const {
	int squareBrackets = 0;
	for (const char c : toCheck) {
		switch (c) {
			case '>':
			case '<':
			case '+':
			case '-':
			case '.':
			case ',':
				break;
			case '[':
				squareBrackets++;
				break;
			case ']':
				squareBrackets--;
				break;
			default:
				return true;
		}
	}
	if (squareBrackets) {
		cerr << "[x] Brackets are missing in the code..." << endl;
		return true;
	}
	return false;
}

unsigned BfInterpreter::matchingBrackets(const string& cmd, const unsigned& pos) const {
	if (cmd[pos] == '[') {
		int count = 1;
		for (unsigned i = pos + 1; i < cmd.length(); i++) {
			if (cmd[i] == '[')
				count++;
			else if (cmd[i] == ']') {
				count--;
				if (count == 0)
					return i;
			}
		}
	}
	else if (cmd[pos] == ']') {
		int count = 1;
		for (int i = pos - 1; i >= 0; i--) {
			if (cmd[i] == ']')
				count++;
			else if (cmd[i] == '[') {
				count--;
				if (count == 0)
					return i;
			}
		}
	}
}

void BfInterpreter::runCode() {
	if (this->errorSyntax) {
		cerr << "[x] A syntax error was encountered in the code: Unable to interpret commands" << endl;
		return;
	}

	//Assets
	vector<char> data(30000, 0);
	unsigned short dataPtr = 0;
	unsigned instructionPtr = 0;

	while (instructionPtr < this->_instructions.length()) {
		switch (this->_instructions[instructionPtr]) {
			case '>':
				if (dataPtr < 30000)
					dataPtr++;
				break;
			case '<':
				if (dataPtr > 0)
					dataPtr--;
				break;
			case '+':
				if (data[dataPtr] < 255)
					data[dataPtr]++;
				break;
			case '-':
				if (data[dataPtr] > 0)
					data[dataPtr]--;
				break;
			case '.':
				cout << data[dataPtr];
				break;
			case ',':
				char input;
				cin >> input;
				data[dataPtr] = input;
				break;
			case '[':
				if (!data[dataPtr])
					instructionPtr = matchingBrackets(this->_instructions, instructionPtr);
				break;
			case ']':
				if (data[dataPtr])
					instructionPtr = matchingBrackets(this->_instructions, instructionPtr) - 1;
				break;
		}
		instructionPtr++;
	}
}

BfInterpreter::BfInterpreter(const string& commands) {
	if (checkSyntax(commands)) {
		this->_instructions = "";
		this->errorSyntax = true;
		cerr << "[x] Syntax error in code..." << endl;
	}
	else
		this->_instructions = commands;
}
