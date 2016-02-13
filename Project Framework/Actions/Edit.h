#ifndef Edit_H
#define Edit_H
#include "Action.h"
class Statement;
class Connector;
class ApplicationManager;

class Edit : public Action
{
	Statement* EditStatement;
	Connector* EditConnector;
public:
	Edit(ApplicationManager *pAppManager);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	
	virtual void Execute();
};


#endif