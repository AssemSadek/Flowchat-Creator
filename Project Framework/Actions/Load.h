#ifndef Load_H
#define Load_H
#include "Action.h"
#include "..\ApplicationManager.h"
#include <fstream>

class Load : public Action
{
	ifstream InFile;
public:
	Load(ApplicationManager *pManager,string s);
	~Load();
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
};



#endif