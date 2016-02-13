#include "AddConnector.h"



AddConnector::AddConnector(ApplicationManager* pManager) :StatementAction(pManager)
{

}
AddConnector::~AddConnector()
{}

void AddConnector::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Add a Connector: choose your source statement");
	pIn->GetPointClicked(SourcePoint);
	int Type;
	StartEnd* pSE;
	//First: Get Correctly my SourcePoint
	Statement* SourceStatement = pManager->GetStatement(SourcePoint, Type);
	if (Type == 0)
		pSE = dynamic_cast<StartEnd*>(SourceStatement);
	while (!SourceStatement || (Type == 0 && pSE->GetMode()))
	{
		pOut->PrintMessage("Add a Connector: choose your source statement");
		pIn->GetPointClicked(SourcePoint);
		SourceStatement = pManager->GetStatement(SourcePoint, Type);
		if (Type == 0)
			pSE = dynamic_cast<StartEnd*>(SourceStatement);
	}
	if (Type == 3)
	{

		int DeltaR = abs(((Conditional*)SourceStatement)->GetOutlet().x - SourcePoint.x);
		int DeltaL = abs(((Conditional*)SourceStatement)->GetOutletLeft().x - SourcePoint.x);
		if (DeltaR <= DeltaL)
		{
			BranchType = 1;
			pOut->PrintMessage("You choosed the \"yes\" branch, please choose your destination statement");
		}
		else
		{
			BranchType = 2;
			pOut->PrintMessage("You choosed the \"No\" branch, please choose destination statement");
		}
	}
	else
	{
		BranchType = 0;
		pOut->PrintMessage("Please choose your destination statement");
	}

	pIn->GetPointClicked(DestinationPoint);
	Statement* DestinationStatement = pManager->GetStatement(DestinationPoint, Type);
	if (Type == 0)
		pSE = dynamic_cast<StartEnd*>(DestinationStatement);
	while (!DestinationStatement || (Type == 0 && !pSE->GetMode()))
	{
		pOut->PrintMessage("Add a Connector: choose your destination statement");
		pIn->GetPointClicked(DestinationPoint);
		DestinationStatement = pManager->GetStatement(DestinationPoint, Type);
		if (Type == 0)
			pSE = dynamic_cast<StartEnd*>(DestinationStatement);
	}
	pOut->ClearStatusBar();
}

//Execute action (code depends on action type)
void AddConnector::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	int Type, Type2;
	Statement* SourceStatement = pManager->GetStatement(SourcePoint, Type);
	Statement* DestStatement = pManager->GetStatement(DestinationPoint, Type2);


	if (Type == 3)
	{
		if (((Conditional*)SourceStatement)->GetpConn() && BranchType == 1)
		{
			pManager->DeleteConnector(((Conditional*)SourceStatement)->GetpConn());
		}
		if (((Conditional*)SourceStatement)->GetpConnL() && BranchType == 2)
		{
			pManager->DeleteConnector(((Conditional*)SourceStatement)->GetpConnL());
		}
	}
	else if (SourceStatement->GetpConn())
		pManager->DeleteConnector(SourceStatement->GetpConn());


	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
	Connector *pConnector = new Connector(SourceStatement, DestStatement, BranchType);
	pManager->AddConnector1(pConnector);
}


bool AddConnector::ValidRegionForConnectors(Point P)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (P.y < 50 || P.y>UI.BGHeight - UI.StBrWdth)
	{
		if (P.y < 50)
			pOut->PrintMessage("Tool bar zone!!");
		else
			pOut->PrintMessage("Status bar zone!!");
		return false;
	}
	else return true;
}


//void AddConnector::CalculateData(int &Delta1, int &Delta2, char &Arrow,Point P1,Point &P2)
//{
//	Delta1 = P1.x - P2.x;
//	Delta2 = P1.y- P2.y;
//	Input *pIn = pManager->GetInput();
//	Output *pOut = pManager->GetOutput();
//	if (abs(Delta1) > abs(Delta2))
//	{
//		P2.y = P1.y;
//		if (Delta1 < 0)  Arrow = 'l';
//		else Arrow = 'r';
//	}
//	if (abs(Delta1) <= abs(Delta2))
//	{
//		P2.x = P1.x;
//		if (Delta2 < 0)  Arrow = 'u';
//		else Arrow = 'd';
//	}
//}


//void AddConnector::ChooseThePoints()
//{
//	Input *pIn = pManager->GetInput();
//	Output *pOut = pManager->GetOutput();
//	Point t2;
//	int DeltaX;
//	int DeltaY;
//	char Arrow;
//	 
//
//	//Second: get correctly my first broken point and calculate my straight line and arrow position
//	pIn->GetPointClicked(Intermediate1);
//	Statement* StatementExist = pManager->GetStatement(Intermediate1, Type2);
//	while (StatementExist || !ValidRegionForConnectors(Intermediate1))
//	{
//		if (BranchType == 0)
//			pOut->PrintMessage("Please choose your first broken point");
//		else if (BranchType == 1)
//			pOut->PrintMessage("You choosed the \"yes\" branch, please choose your first broken point");
//		else
//			pOut->PrintMessage("You choosed the \"No\" branch, please choose your first broken point");
//		pIn->GetPointClicked(Intermediate1);
//		StatementExist = pManager->GetStatement(Intermediate1, Type2);
//	}
//	
//	CalculateData(DeltaX, DeltaY, Arrow,SourceStatement->GetOutlet(),Intermediate1);
//	
//
//	//Third: see if the user wants a second broken point or he will end it with the destination statement
//	Point P;
//	pOut->PrintMessage("First Branch is connected, please Choose your second broken point or a destination statement");
//	pIn->GetPointClicked(P);
//	StatementExist = pManager->GetStatement(P, Type2);
//	if (Type2 == 0) 
//		pSE = dynamic_cast<StartEnd*>(StatementExist);
//	while (!ValidRegionForConnectors(P) || (Type == 0 && (!pSE->GetMode())))
//	{
//		pIn->GetPointClicked(P);
//		StatementExist = pManager->GetStatement(P, Type2);
//		if (Type2 == 0)
//			pSE = dynamic_cast<StartEnd*>(StatementExist);
//		
//	}
//
//	
//
//	if (StatementExist)
//	{
//		DestinationPoint = P;
//		pOut->PrintMessage("Second Branch is connected, you Choosed The destination Statement");
//
//	}
//	else
//	{
//		Intermediate2 = P;
//		CalculateData(DeltaX, DeltaY, Arrow, Intermediate1, Intermediate2);
//		pIn->GetPointClicked(DestinationPoint);
//		StatementExist = pManager->GetStatement(DestinationPoint, Type2);
//		if (Type2 == 0)
//			pSE = dynamic_cast<StartEnd*>(StatementExist);
//			StatementExist = pManager->GetStatement(DestinationPoint, Type2);
//			while (!StatementExist || (Type == 0 && (!pSE->GetMode())))
//			{
//				pOut->PrintMessage("Second Branch is connected, click on the source statement");
//				pIn->GetPointClicked(DestinationPoint);
//				StatementExist = pManager->GetStatement(DestinationPoint, Type2);
//			}
//			
//
//	}
//	//CalculateData(DeltaX, DeltaY, Arrow);
//	//pOut->DrawMyArrow(Arrow, DestinationPoint);
//}
