#ifndef AddReadWrite_H
#define AddReadWrite_H
#include "StatementAction.h"
#include "..\Statements\ReadWrite.h"
class AddReadWrite : public StatementAction
{
public:
	AddReadWrite(ApplicationManager *pAppManager);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};







#endif