#ifndef VALIDATE_H
#define VALIDATE_H

#include "../ApplicationManager.h"

class Validate : public Action
{
	bool Mode;
public:
	Validate(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
	int ValidateForRun();
	int ValidationLogic();
};

#endif