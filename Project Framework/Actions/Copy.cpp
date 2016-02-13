#include "Copy.h"
#include "StatementAction.h"
using namespace std;

Copy::Copy(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{
}


void Copy::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Your selected statement(s) are ready to be copied");
	
	//pOut->ClearStatusBar();
}


void Copy::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pManager->UpdateCopiedOrCutStatements(1);//Set the CopiedOrCut variable to 1 which is the flag for copying	
}