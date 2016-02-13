#ifndef SWITCH_H
#define SWITCH_H

#include "../ApplicationManager.h"

class Switch : public Action
{
public:
	Switch(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif