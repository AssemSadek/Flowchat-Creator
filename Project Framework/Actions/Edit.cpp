#include "Edit.h"
#include "..\Statements\Connector.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"


Edit::Edit(ApplicationManager *pAppManager) :Action(pAppManager)
{
	EditStatement = NULL;
	EditConnector = NULL;
}

//Reads parameters required for action to execute
void Edit::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point P;
	//int Type;
	//pOut->PrintMessage("Edit:Choose a statement/connector to edit");
	//pIn->GetPointClicked(P);
	//EditStatement = pManager->GetStatement(P, Type);
	//EditConnector = pManager->GetConnector(P);

	//while ((!EditStatement || Type ==0)  && !EditConnector)
	//{
	//	pIn->GetPointClicked(P);
	//	EditStatement = pManager->GetStatement(P, Type);
	//	EditConnector = pManager->GetConnector(P);
	//}
	bool StatementToEdit = (pManager->GetSelectedStatements().size() == 1) && (pManager->GetSelectedConnectors().size() == 0);
	bool ConnectorToEdit = (pManager->GetSelectedStatements().size() == 0) && (pManager->GetSelectedConnectors().size() == 1);
	if (StatementToEdit || ConnectorToEdit)
	{
		if (StatementToEdit)
			EditStatement = *(pManager->GetSelectedStatements().begin());
		else
			EditConnector = *(pManager->GetSelectedConnectors().begin());
	}
	else
	pOut->PrintMessage("Please choose one option ( one statement only or one connector only )");

}


void Edit::Execute()
{
	ReadActionParameters(); 
	Output *pOut = pManager->GetOutput();
	int Type;
	if (EditStatement) Type=EditStatement->GetStatementType();
	if (EditStatement)
	{
		if (Type == 0)
			pOut->PrintMessage("The SelectedStatement is either Start or End so you dont have to edit it");
		else
			EditStatement->Edit(pManager);
	}
	else
	if (EditConnector)
		EditConnector->Edit(pManager);
}