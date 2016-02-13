#ifndef DELETE_H
#define DELETE_H

#include "Action.h"

class Delete : public Action
{
public:
	Delete(ApplicationManager *pAppManager);

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

#endif