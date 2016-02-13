#ifndef Save_H
#define Save_H
#include <fstream>
#include "..\ApplicationManager.h"

class Save : public Action
{
	ofstream OutFile;

public:
	Save(ApplicationManager *pManager, string S = "MyFlowChart.txt");
	~Save();
	virtual void ReadActionParameters();
	virtual void Execute();

};









#endif