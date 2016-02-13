#include "AddConditional.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConditional::AddConditional(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{}

void AddConditional::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Conditional Statement: Click to add the statement");

	pIn->GetPointClicked(Position);

	while (!this->ValidateDrawingPoint())
	{
		pOut->PrintMessage("Conditional Statement: Click on a suitable point");
		pIn->GetPointClicked(Position);
	}

	pOut->ClearStatusBar();
}

void AddConditional::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Get LeftHandSide
	pOut->PrintMessage("Please enter variable name or value");
	bool TempLHSType;
	string TempLHSString;
	double TempLHSDouble;
	pIn->GetMixed(pOut, TempLHSType, TempLHSString, TempLHSDouble);

	//Get Operator
	pOut->PrintMessage("Please enter operator");
	string TempOprtr = pIn->GetOperator(pOut);
	
	//Get RightHandSide
	pOut->PrintMessage("Please enter variable name or value");
	bool TempRHSType;
	string TempRHSString;
	double TempRHSDouble;
	pIn->GetMixed(pOut, TempRHSType, TempRHSString, TempRHSDouble);
	
	pOut->ClearStatusBar();

	Conditional *pAssign = new Conditional(Position, TempLHSString, TempLHSDouble, TempLHSType, TempOprtr, TempRHSString, TempRHSDouble, TempRHSType);

	pManager->AddStatement(pAssign);
}
