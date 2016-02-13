#ifndef AddConnector_H
#define AddConnector_H

#include "StatementAction.h"
#include "..\ApplicationManager.h"

class AddConnector : public StatementAction
{
	Point SourcePoint;
	Point DestinationPoint;
	int BranchType;
public:
	AddConnector(ApplicationManager* pManager);
	~AddConnector();
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	//void ChooseThePoints();
	bool ValidRegionForConnectors(Point P);
	//void CalculateData(int &Delta1, int &Delta2, char &Arrow,Point P1, Point &P2);
};

#endif