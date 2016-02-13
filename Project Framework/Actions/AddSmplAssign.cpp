#include "AddSmplAssign.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddSmplAssign::AddSmplAssign(ApplicationManager *pAppManager):StatementAction(pAppManager)
{}

void AddSmplAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Simple Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	
	while (!this->ValidateDrawingPoint())
	{
		pOut->PrintMessage("Simple Value Assignment Statement: Click on a suitable point");
		pIn->GetPointClicked(Position);
	}
	
	pOut->ClearStatusBar();		
}

void AddSmplAssign::Execute()
{
	ReadActionParameters();
	
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Please assign");
	string TempLHS = pIn->GetString(pOut);
	pOut->PrintMessage("");
	bool TempRHSType;
	string TempRHSString;
	double TempRHSDouble;
	pIn->GetMixed(pOut, TempRHSType, TempRHSString, TempRHSDouble);
	SmplAssign *pAssign = new SmplAssign(Position, TempLHS, TempRHSString, TempRHSDouble, TempRHSType);

	pManager->AddStatement(pAssign);
}
