#ifndef Comment_H
#define Comment_H

#include "Action.h"
class Statement;
class ApplicationManager;

class Comment : public Action
{
	Statement* ComStatement;
public:
	Comment(ApplicationManager *pAppManager);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	virtual void Execute();
};


#endif