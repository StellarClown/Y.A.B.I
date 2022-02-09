#include <string>

using std::string;

class BfInterpreter {
	private:
		string _instructions;
		bool errorSyntax = false;
		bool checkSyntax(const string& toCheck) const;
		unsigned matchingBrackets(const string& cmd, const unsigned& pos) const;
	public:
		BfInterpreter(const string& commands);
		void runCode();
};