#include "Delete.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
#include <list>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete::Delete(ApplicationManager *pAppManager) : Action(pAppManager)
{}

void Delete::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Get List of selected statements
	list<Statement*> SelectedStatements = pManager->GetSelectedStatements();
	list<Connector*> SelectedConnectors = pManager->GetSelectedConnectors();
	Point TempP;
	//list<Connector*>ConnList = pManager->GetConnList();

	//Print Message and Wait for any click
	pOut->PrintMessage("Delete: Deleting Selected Statements if any, press any key to continue");
	pIn->GetPointClicked(TempP);
	for (list<Connector*>::iterator it = SelectedConnectors.begin(); it != SelectedConnectors.end(); it++)
	{
		pManager->DeleteConnector((*it));
	}


	list<Connector*>ConnList = pManager->GetConnList();

	for (list<Statement*>::iterator it = SelectedStatements.begin(); it != SelectedStatements.end(); it++)
	{
		//Delete Input Connectors
		if ((*it)->GetStatementType() != 0 || ((*it)->GetStatementType() == 0 && ((StartEnd*)(*it))->GetMode() == true))
		{
			list<Connector*> InputConnectors;

			for (list<Connector*>::iterator itConn = ConnList.begin(); itConn != ConnList.end(); itConn++)
			{
				if ((*itConn)->getDstStat() == (*it))
					InputConnectors.push_back((*itConn));
			}
			for (list<Connector*>::iterator itConn = InputConnectors.begin(); itConn != InputConnectors.end(); itConn++)
			{
				/*
				if ((*itConn)->getSrcStat()->GetpConn == (*itConn))
				(*itConn)->getSrcStat()->SetpConn(NULL);
				else if (((Conditional*)(*itConn)->getSrcStat())->GetpConnL() == (*itConn))
				((Conditional*)(*itConn)->getSrcStat())->SetpConnL(NULL);
				*/
				if ((*itConn)->GetBranchType() == 2)
					((Conditional*)(*itConn)->getSrcStat())->SetpConnL(NULL);
				else
					(*itConn)->getSrcStat()->SetpConn(NULL);

				pManager->DeleteConnector((*itConn));
			}
		}

		//Conditional
		if ((*it)->GetStatementType() == 3)
		{
			//Yes
			if (((Conditional*)(*it))->GetpConn() != NULL)
				pManager->DeleteConnector(((Conditional*)(*it))->GetpConn());
			//No
			if (((Conditional*)(*it))->GetpConnL() != NULL)
				pManager->DeleteConnector(((Conditional*)(*it))->GetpConnL());
		}
		else //Not Conditional
		{
			if ((*it)->GetpConn() != NULL)
				pManager->DeleteConnector((*it)->GetpConn());
		}
		pManager->DeleteStatement((*it));
	}

	pOut->PrintMessage("");
	pOut->ClearDrawArea();
	pManager->UpdateInterface();
}