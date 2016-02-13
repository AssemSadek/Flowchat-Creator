#include "AddReadWrite.h"
#include "..\ApplicationManager.h"


#include <sstream>

using namespace std;



AddReadWrite::AddReadWrite(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{
}

void AddReadWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Read/Write Statement: Click to add the statement");

	pIn->GetPointClicked(Position);

	while (!this->ValidateDrawingPoint())
	{
		pOut->PrintMessage("Read/Write Statement: Click on a suitable point");
		pIn->GetPointClicked(Position);
	}

	pOut->ClearStatusBar();

}

void AddReadWrite::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	bool b, v = true, F = true;
	pOut->PrintMessage("Do you want to Read or Write \"r/w\" ?");
	string Decision = pIn->GetString(pOut);
	if (Decision == "r")
	{
		b = true;
		
		pOut->PrintMessage("Do you want to read from GUI or File\"g/f\" ?");
		Decision = pIn->GetString(pOut);
		if (Decision == "g")
			F = true;
		else
			F = false;

		pOut->PrintMessage("Please Enter the variable to read");
	}
	else
	{
		b = false;
		pOut->PrintMessage("Do you want to write Variable or Text \"v/t\" ?");
		Decision = pIn->GetString(pOut);
		if (Decision == "v")
		{
			pOut->PrintMessage("Please Enter the Variable to write");
			v = true;
		}
		else
		{
			pOut->PrintMessage("Please Enter the Text to write");
			v = false;
		}
	}
	//pOut->PrintMessage("");
	string TempVar;
	if (v)
		TempVar = pIn->GetString(pOut);
	else
		TempVar = pIn->GetNormalString(pOut);
	pOut->PrintMessage("");
	
	ReadWrite *pAssign = new ReadWrite(Position, b, TempVar, v, F, TempVar);

	pManager->AddStatement(pAssign);
}