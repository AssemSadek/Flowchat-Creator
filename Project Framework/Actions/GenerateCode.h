#ifndef GenerateCode_H
#define GenerateCode_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include <list>
#include <vector>

class GenerateCode : public Action
{
private:
	bool IsDeclared(vector<string> V, string Var);
public:
	GenerateCode(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
	list<string> getCode(Statement* s, int e = 0); //Used to get each statement's code
	
	//7amada
	string Codegen(Statement* CS, int &E, string S);
};

#endif