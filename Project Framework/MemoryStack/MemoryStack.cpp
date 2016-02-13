#include "MemoryStack.h"

#include "../ApplicationManager.h"
#include <iostream>

using namespace std;

bool MemoryStack::Contains(string VarName)
{
	for (unsigned int i = 0; i < this->VariableStack.size(); i++)
	{
		if (VariableStack[i].first == VarName)
			return true;
	}
	return false;
}

MemoryStack& MemoryStack::operator += (pair<string, double> Variable)
{
	this->VariableStack.push_back(Variable);
	return *this;
}

double& MemoryStack::operator [] (string VarName)
{
	for (unsigned int i = 0; i < this->VariableStack.size(); i++)
	{
		if (VariableStack[i].first == VarName)
			return VariableStack[i].second;
	}
	return VariableStack[0].second;
}

vector<pair<string, double>> MemoryStack::GetVS()
{
	return this->VariableStack;
}

void MemoryStack::Display()
{
	for (unsigned int i = 0; i < this->VariableStack.size(); i++)
	{
		cout << VariableStack[i].first << ":\t" << VariableStack[i].second << endl;
	}
}

void MemoryStack::ClearStackMemory()
{
	this->VariableStack.clear();
}