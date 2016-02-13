#include "AddVariableAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddVariableAssign::AddVariableAssign(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{}

void AddVariableAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	while (!this->ValidateDrawingPoint())
	{
		pOut->PrintMessage("Variable Assignment Statement: Click on a suitable point");
		pIn->GetPointClicked(Position);
	}

	pOut->ClearStatusBar();
}

void AddVariableAssign::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Please assign");
	string TempLHS = pIn->GetString(pOut);
	pOut->PrintMessage("");
	string TempRHS = pIn->GetNormalString(pOut);
	pOut->PrintMessage("");
	VariableAssign *pVariableAssign = new VariableAssign(Position, TempLHS, TempRHS);
	
	pManager->AddStatement(pVariableAssign);
}

