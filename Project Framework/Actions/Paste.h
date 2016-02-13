#ifndef PASTE_H
#define PASTE_H

#include "../ApplicationManager.h"

class Paste :public StatementAction
{
	Point P;
	bool FlagToPaste; //Flag to check the existance of statements ready to be copied or cut
public:
	Paste(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};




#endif