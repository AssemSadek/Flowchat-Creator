#include "Run.h"
#include "Validate.h"
#include <iostream>
#include <vector>

using namespace std;

Run::Run(ApplicationManager *pAppManager, bool M) : Action(pAppManager)
{
	Mode = M; //True Step by Step, False Normal Run
}


void Run::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
}


void Run::Execute()
{
	//For Bonus Read Write from File
	ReadWrite::INFILE.open("INPUT.txt",ios::in);
	//Validate before running
	Validate *ValidatingAction = new Validate(pManager);
	if (ValidatingAction->ValidateForRun() == 0)
		return;

	list<Statement*> StatList = pManager->GetStatList();
	list<Connector*> ConnList = pManager->GetConnList();
	pManager->GetSelectedStatements().clear();
	Statement *CurrentStatement;
	Statement *PreviousStatement;
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		(*it)->SetSelected(false);
		pManager->UpdateSelectedStatements((*it));
		if ((*it)->GetStatementType() == 0) //Get StartEndStatement and Unselect Statements
		{
			if (((StartEnd*)(*it))->GetMode()==false)//Start Statement "Beginning of FlowChart
			CurrentStatement = *it;
		}
	}
	PreviousStatement = CurrentStatement;
	while (CurrentStatement != NULL)
	{
		int Error;
		Point P; //Temp Point for getting point clicked
		CurrentStatement->SetSelected(true);
		Error = CurrentStatement->Run(pManager, CurrentStatement);
		switch (Error)
		{
		case -1:
			pManager->GetOutput()->PrintMessage("Error '-1': LHS Variable is not declared, Execution Ended");
			pManager->GetInput()->GetPointClicked(P);
			pManager->GetOutput()->PrintMessage("");
			return;
		case -2:
			pManager->GetOutput()->PrintMessage("Error '-2': RHS Variable is not declared, Execution Ended");
			pManager->GetInput()->GetPointClicked(P);
			pManager->GetOutput()->PrintMessage("");
			return;
		case -3:
			pManager->GetOutput()->PrintMessage("Error '-3': Invalid Complex Expression, Execution Ended");
			pManager->GetInput()->GetPointClicked(P);
			pManager->GetOutput()->PrintMessage("");
			return;
		case -4:
			pManager->GetOutput()->PrintMessage("Error '-1': LHS not in stack memory, Execution Ended");
			pManager->GetInput()->GetPointClicked(P);
			pManager->GetOutput()->PrintMessage("");
			return;

		}
		pManager->UpdateInterface();
		if (Mode) //Step By Step
			pManager->GetInput()->GetPointClicked(P);
		else
			Sleep(1000);

		pManager->GetOutput()->PrintMessage("");
		PreviousStatement->SetSelected(false);
		PreviousStatement = CurrentStatement;

		//
		if (Mode) //Step by Step
		{
			cout << "--------------------------\n";
			pManager->GetMemoryStack().Display();
		}
	}
	
	//Print the final values of all the variables;
	cout << "--------------------------\n";
	cout << "  Final Variable Values\n";
	cout << "--------------------------\n";
	pManager->GetMemoryStack().Display();
	cout << "--------------------------\n";

	//Clear the Memory Stack from Variables
	pManager->GetMemoryStack().ClearStackMemory();

	//Bonus
	ReadWrite::INFILE.close();
}