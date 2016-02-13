#include "Select.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Select::Select(ApplicationManager *pAppManager, Point P) : StatementAction(pAppManager)
{
	Position = P;
}

void Select::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Statement *SelectedStatement;
	Connector* SelectedConnector;
	int Type;
	SelectedStatement = pManager->GetStatement(this->Position, Type);
	SelectedConnector = pManager->GetConnector(this->Position);
	if (SelectedStatement != NULL || SelectedConnector != NULL)
	{
		if (SelectedStatement)
		{
			SelectedStatement->SetSelected(!SelectedStatement->IsSelected());
			pManager->UpdateSelectedStatements(SelectedStatement);
		}
		else
		{
			SelectedConnector->SetSelected(!SelectedConnector->IsSelected());
			pManager->UpdateSelectedConnectors(SelectedConnector);
		}
	}
	if (pManager->GetSelectedStatements().size() == 1)
		pManager->GetOutput()->PrintMessage(pManager->GetSelectedStatements().front()->GetComment());
	else
		pManager->GetOutput()->PrintMessage("");
	pManager->UpdateInterface();
}