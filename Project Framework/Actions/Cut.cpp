#include "Cut.h"


Cut::Cut(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{
}


void Cut::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Your selected statement(s) are ready to be cut");

	//pOut->ClearStatusBar();
}


void Cut::Execute()
{

	pManager->DeleteCutStatements();
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	list<Statement*> StatList = pManager->GetStatList();
	list<Statement*> SelectedStatements = pManager->GetSelectedStatements();
	
	pManager->UpdateCopiedOrCutStatements(2);//Set the CopiedOrCut variable to 2 which is the flag for cutting

	//Remove the Cut Statements
	for (list<Statement*>::iterator it = SelectedStatements.begin(); it != SelectedStatements.end(); it++)
	{
		pManager->RemoveStatementConnectors((*it));
		//pManager->RemoveStatementFromStatListWithoutDeleting((*it));
	}
	pManager->GetOutput()->ClearDrawArea();
	pManager->UpdateInterface();
}