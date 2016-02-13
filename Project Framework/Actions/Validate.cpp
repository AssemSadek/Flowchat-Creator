#include "Validate.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

Validate::Validate(ApplicationManager *pAppManager) : Action(pAppManager)
{}


void Validate::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
}


void Validate::Execute()
{
	ValidationLogic();
}


int Validate::ValidateForRun()
{
	return ValidationLogic();
}
int Validate::ValidationLogic()
{
	list<Statement*> StatList = pManager->GetStatList();
	list<Connector*> ConnList = pManager->GetConnList();
	string ErrorMessage; //Holds the Error Message
	Point P; //Temp Point for Waiting for the user to click to continue
	int StartEndNumber = 0; //Variable to hold number of start end statements

	//Check no goto and no Statements has many Connectors going to it except the Conditional Statements
	map<int, int> StatementIDCounter; //Holds number of connectors going into any ID

	//Check Variables and initialize Statement IDs with Zero Values
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		//Get Statement Type
		int Type = (*it)->GetStatementType();

		//Initialize map of Statement IDs with 0 values except start initialize with one as if a connector is connected to it
		if (Type == 0 && ((StartEnd*)(*it))->GetMode() == false)
			StatementIDCounter[(*it)->GetID()] = 1;
		else
			StatementIDCounter[(*it)->GetID()] = 0;

		//Check all statements except end has a connector going out of it
		if (Type != 0 && ((StartEnd*)(*it))->GetMode() != true) //If Type 0 and Mode is true (End Statement) will not do
		{
			//Check of pConn is NULL or in case of Conditional check pConnL is NUll
			if ((*it)->GetpConn() == NULL || (Type == 3 && ((Conditional*)(*it))->GetpConnL() == NULL))
			{
				ErrorMessage += "Please connect all the statements with connectors, Press any key to continue";
				pManager->GetOutput()->PrintMessage(ErrorMessage);
				pManager->GetInput()->GetPointClicked(P);
				pManager->GetOutput()->PrintMessage("");
				return 0;
			}
		}
		if (Type == 0)
			StartEndNumber++;
	}

	//Check presence of Start and End Statements
	if (StartEndNumber < 2)
	{
		ErrorMessage = "Please insert both the Start and End Statements, Press any key to continue";
		pManager->GetOutput()->PrintMessage(ErrorMessage);
		pManager->GetInput()->GetPointClicked(P);
		pManager->GetOutput()->PrintMessage("");
		return 0;
	}

	//Get Number of Connectors going to all IDs "except start and end"

	for (list<Connector*>::iterator it = ConnList.begin(); it != ConnList.end(); it++)
		//StatementIDCounter[(*it)->getDstStat()->GetID()] = StatementIDCounter[(*it)->getDstStat()->GetID()] + 1;
		(StatementIDCounter[(*it)->getDstStat()->GetID()])++;

	//Check if any statement has no connectors going to it (the value of its index in the map == 0)
	for (map<int, int>::iterator it = StatementIDCounter.begin(); it != StatementIDCounter.end(); it++)
	{
		if ((*it).second == 0)
		{
			ErrorMessage += "Please connect all the statements with input connectors, Press any key to continue";
			pManager->GetOutput()->PrintMessage(ErrorMessage);
			pManager->GetInput()->GetPointClicked(P);
			pManager->GetOutput()->PrintMessage("");
			return 0;
		}
	}

	ErrorMessage += "Validation Done, Press any key to continue";
	pManager->GetOutput()->PrintMessage(ErrorMessage);
	pManager->GetInput()->GetPointClicked(P);
	pManager->GetOutput()->PrintMessage("");
	return 1;
}