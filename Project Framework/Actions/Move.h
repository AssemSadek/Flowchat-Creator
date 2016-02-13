#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
#include "..\Statements\Conditional.h"

#include <list>

class Move : public Action
{
	Point BeginningPoint;
	list<Statement*> SelectedStatements;
	window *pWind;
public:
	Move(ApplicationManager *pAppManager, Point P);

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

#endif