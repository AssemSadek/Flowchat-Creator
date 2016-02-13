#ifndef ACTION_H
#define ACTION_H

//#include "CMUgraphicsLib\CMUgraphics.h"
class ApplicationManager; //forward class declaration
class Input;
class Output;

#include "..\GUI\UI_Info.h"


//Base class for all possible actions
class Action
{
protected:
	//Pointer to ApplicationManager because action needs this pointer for its functions
	ApplicationManager *pManager;	

public:
	Action(ApplicationManager *pAppManager) 
	{ pManager = pAppManager; }
	
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(){};
	
	//Execute action (code depends on action type)
	virtual void Execute() = 0;
};

#endif