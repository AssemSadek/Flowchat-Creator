#ifndef COPY_H
#define COPY_H

#include "../ApplicationManager.h"

class Copy:public StatementAction
{
public:
	Copy(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif