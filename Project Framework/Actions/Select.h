#ifndef SELECT_H
#define SELECT_H

#include "Action.h"
#include "StatementAction.h"

class Select : public StatementAction
{
public:
	Select(ApplicationManager *pAppManager, Point P);

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

#endif