#include "AddStartEnd.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

AddStartEnd::AddStartEnd(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{}

void AddStartEnd::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	bool Mode;
	if (!StartEnd::CanCreate())
	{
		//Can't Draw Again
		pOut->PrintMessage("Can't Create any more Start/End Statements, press any key to continue");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
		Position.x = -1;
		Position.y = -1;
		return;
	}
	if (!StartEnd::GetStartDrawn())
	{
		Mode = false;
	}
	else if (!StartEnd::GetEndDrawn())
	{
		Mode = true;
	}

	if (Mode == false)
		pOut->PrintMessage("Start Statement: Click to add the statement");
	else
		pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);

	while (!this->ValidateDrawingPoint())
	{
		if (Mode == false)
			pOut->PrintMessage("Start Statement: Click on a suitable point");
		else
			pOut->PrintMessage("End Statement: Click on a suitable point");

		pIn->GetPointClicked(Position);
	}

	pOut->ClearStatusBar();
}

void AddStartEnd::Execute()
{
	ReadActionParameters();
	if (Position.x != -1)
	{
		StartEnd *pStartEnd = new StartEnd(Position);
		pManager->AddStatement(pStartEnd);
	}
}

