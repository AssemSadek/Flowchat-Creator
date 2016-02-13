#pragma once
#include "Action.h"
#include "StatementAction.h"
#include "..\Statements\StartEnd.h"

class AddStartEnd :
	public StatementAction
{
public:
	AddStartEnd(ApplicationManager *pAppManager);
	
	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

