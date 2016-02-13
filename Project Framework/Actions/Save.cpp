#include "Save.h"




Save::Save(ApplicationManager *pManager, string S) :Action(pManager)
{
	OutFile.open(S);
}

Save::~Save()
{
	OutFile.close();
}


void Save::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//pOut->PrintMessage("The Flow chart is Saved");
}
void Save::Execute()
{
	ReadActionParameters();

	list<Statement*> StatList = pManager->GetStatList();
	list<Connector*> ConnList = pManager->GetConnList();
	OutFile << StatList.size() << endl;
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
		(*it)->Save(OutFile);
	OutFile << ConnList.size() << endl;
	for (list<Connector*>::iterator it = ConnList.begin(); it != ConnList.end(); it++)
		(*it)->Save(OutFile);
	//pManager->SaveALL(OutFile);
	OutFile.close();
}
