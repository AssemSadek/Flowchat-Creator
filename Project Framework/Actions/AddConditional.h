#ifndef ADD_CONDITIONAL_H
#define ADD_CONDITIONAL_H

#include "Action.h"
#include "StatementAction.h"
#include "..\Statements\Conditional.h"

class AddConditional : public StatementAction
{
public:
	AddConditional(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

#endif