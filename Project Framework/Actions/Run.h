#ifndef RUN_H
#define RUN_H

#include "../ApplicationManager.h"

class Run : public Action
{
	bool Mode;
public:
	Run(ApplicationManager *pAppManager, bool Mode);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif