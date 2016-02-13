#pragma once
#include "Action.h"

class StatementAction : public Action
{
protected:
	Point Position;
public:
	StatementAction(ApplicationManager *pAppManager);
	//Validates the drawing point for all statements
	bool ValidateDrawingPoint();

};

