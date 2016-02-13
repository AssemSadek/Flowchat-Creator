#ifndef MEMORY_STACK
#define MEMORY_STACK

#include <vector>


using namespace std;

class ApplicationManager;

class MemoryStack
{
	vector<pair<string, double>> VariableStack;
public:
	bool Contains(string VarName);
	MemoryStack& operator += (pair<string, double> Variable);
	double& operator [] (string VarName);
	vector<pair<string, double>> GetVS();
	void Display();
	void ClearStackMemory();
};
#endif