#include "Load.h"



Load::Load(ApplicationManager *pManager, string s) :Action(pManager)
{
	string s1 = s;
	if (s.size()>3 && s[s.size() - 4] != '.') //for undo&redo file name already ends with ".tmp"
		s1 += ".txt"; //This is a file name entered by user for normal loading
	InFile.open(s1, ios::in);
}

Load::~Load()
{
	InFile.close();
}

void Load::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("The Flow chart is Loaded");
}

void Load::Execute()
{
	ReadActionParameters();

	list<Statement*> *StatList = pManager->GetStatList_Editable();
	list<Connector*> *ConnList = pManager->GetConnList_Editable();
	list<Statement*> *SelectedStatements = pManager->GetSelectedStatements_Editable();


	for (list<Statement*>::iterator it = StatList->begin(); it != StatList->end(); it++)
		delete (*it);
	for (list<Connector*>::iterator it = ConnList->begin(); it != ConnList->end(); it++)
		delete (*it);

	StatList->clear();
	ConnList->clear();
	SelectedStatements->clear();
	int x;
	InFile >> x;
	string Name;
	Point P;
	P.x = 0, P.y = 0;
	string str = "x";
	double d = 0;
	for (int i = 0; i < x; i++)
	{
		InFile >> Name;
		Statement* pSE;
		if (Name == "START")
			pSE = new StartEnd(P, false);
		if (Name == "END")
			pSE = new StartEnd(P, true);
		if (Name == "SmplAssign")
			pSE = new SmplAssign(P, str, str, d, true);
		if (Name == "VarAssign")
			pSE = new VariableAssign(P, str, str);
		if (Name == "Conditional")
			pSE = new Conditional(P, str, d, true, str, str, d, true);
		if (Name == "READ")
			pSE = new ReadWrite(P, true, str);
		if (Name == "WRITE")
			pSE = new ReadWrite(P, false, str);

		pSE->Load(InFile);
		pManager->AddStatement(pSE);
	}
	
	InFile >> x; //Connector Numbers
	for (int i = 0; i < x; i++)
	{
		Connector *NewConn = new Connector();
		NewConn->Load(InFile, pManager);
		pManager->AddConnector1(NewConn);
	}

	//Clear Screen
	pManager->GetOutput()->ClearDrawArea();
	pManager->GetOutput()->ClearStatusBar();
	pManager->UpdateInterface();


	//pManager->LoadALL(InFile);
	InFile.close();
}

