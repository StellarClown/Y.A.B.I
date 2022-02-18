#include <string>

using std::string;

class BfInterpreter {
private:
	string _instructions;
	bool errorSyntax = false;
	bool checkSyntax(const string&) const;
	unsigned matchingBrackets(const string&, const unsigned&) const;
public:
	BfInterpreter(const string&);
	BfInterpreter(const char*); //Overloading constructor method for char*
	BfInterpreter(const BfInterpreter&); //Overloading constructor method for copy from an existing object
	~BfInterpreter() = default;
	void operator= (const string&);
	void operator= (const char*); //Overloading operator = for the char*
	void runCode() const;
};