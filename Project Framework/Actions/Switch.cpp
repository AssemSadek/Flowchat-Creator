#include "Switch.h"
using namespace std;

Switch::Switch(ApplicationManager *pAppManager) : Action(pAppManager)
{}


void Switch::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
}


void Switch::Execute()
{
	ReadActionParameters();
	//Clear Selected Statements
	list<Statement*> StatList = pManager->GetStatList();
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		(*it)->SetSelected(false);
		pManager->UpdateSelectedStatements((*it));
	}
	if (UI.AppMode == DESIGN) //We want to switch to simulation
	{
		pManager->GetOutput()->PrintMessage("Switching to Simulation Mode. Press any key to continue");
		Point P;
		pManager->GetInput()->GetPointClicked(P);
		pManager->GetOutput()->CreateSimulationToolBar();
	}
	else
	{
		pManager->GetOutput()->PrintMessage("Switching to Design Mode. Press any key to continue");
		Point P;
		pManager->GetInput()->GetPointClicked(P);
		pManager->GetOutput()->CreateDesignToolBar();
	}
	pManager->GetOutput()->PrintMessage("");
}