#include "Connector.h"
#include "Conditional.h"
#include "..\ApplicationManager.h"

Connector::Connector()
{
	SrcStat = NULL;
	DstStat = NULL;
	BranchType = 0;
}

Connector::Connector(Statement* Src, Statement* Dst, int BT)
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{

	SrcStat = Src;
	DstStat = Dst;
	BranchType = BT;
	if (BranchType == 2)
	{
		Start = ((Conditional*)SrcStat)->GetOutletLeft();
		((Conditional*)SrcStat)->SetpConnL(this);
	}
	else
	{
		Start = SrcStat->GetOutlet();
		SrcStat->SetpConn(this);
	}

	End = DstStat->GetInlet();
	Selected = false;
}

void Connector::setSrcStat(Statement *Src)
{
	SrcStat = Src;
}

Statement* Connector::getSrcStat()
{
	return SrcStat;
}

void Connector::setDstStat(Statement *Dst)
{
	DstStat = Dst;
}

Statement* Connector::getDstStat()
{
	return DstStat;
}


void Connector::setStartPoint(Point P)
{
	Start = P;
}

Point Connector::getStartPoint()
{
	return Start;
}

void Connector::setEndPoint(Point P)
{
	End = P;
}

Point Connector::getEndPoint()
{
	return End;
}

void Connector::Draw(Output* pOut)
{
	///TODO: Call output to draw a connector from SrcStat to DstStat on the output window
	UpdateIntermediate();
	if (CopiedOrCut != 2)
	{
		if (AllIntermediateUsed)
		{
			pOut->DrawConnectorLine(Start, Intermediate1, Selected);
			pOut->DrawConnectorLine(Intermediate1, Intermediate2, Selected);
			pOut->DrawConnectorLine(Intermediate2, Intermediate3, Selected);
			pOut->DrawConnectorLine(Intermediate3, Intermediate4, Selected);
			pOut->DrawConnectorLine(Intermediate4, End, Selected);
			Point Arrow;
			Arrow.y = End.y - 4;
			Arrow.x = End.x + 4;
			pOut->DrawConnectorLine(End, Arrow, Selected);
			Arrow.x = End.x - 4;
			pOut->DrawConnectorLine(Arrow, End, Selected);
		}
		else
		{
			pOut->DrawConnectorLine(Start, Intermediate1, Selected);
			pOut->DrawConnectorLine(Intermediate1, Intermediate2, Selected);
			pOut->DrawConnectorLine(Intermediate2, End, Selected);
			Point Arrow;
			Arrow.y = End.y - 4;
			Arrow.x = End.x + 4;
			pOut->DrawConnectorLine(End, Arrow, Selected);
			Arrow.x = End.x - 4;
			pOut->DrawConnectorLine(Arrow, End, Selected);
		}
	}
	else
	{
	}
}

void Connector::Save(ofstream &OutFile)
{
	OutFile << SrcStat->GetID() << "\t" << DstStat->GetID() << "\t" << BranchType << endl;
}
void Connector::Load(ifstream &InFile, ApplicationManager *pManager)
{
	int x, y;
	InFile >> x >> y >> BranchType;

	/*
	list<Statement*> S = pManager->GetStatList();
	list<Statement*>::iterator it = S.begin();
	*/

	list<Statement*> S = pManager->GetStatList();
	list<Statement*>::iterator it = S.begin();


	while ((*it)->GetID() != x)
		it++;
	SrcStat = *it;

	it = S.begin();
	while ((*it)->GetID() != y)
		it++;
	DstStat = *it;

	if (BranchType == 2)
	{
		Start = ((Conditional*)SrcStat)->GetOutletLeft();
		((Conditional*)SrcStat)->SetpConnL(this);
	}
	else
	{
		Start = SrcStat->GetOutlet();
		SrcStat->SetpConn(this);
	}

	End = DstStat->GetInlet();
	Selected = false;

}


void Connector::UpdateIntermediate()
{
	ConnPoints.clear();
	if (BranchType == 2)
		Start = ((Conditional*)SrcStat)->GetOutletLeft();
	else
		Start = SrcStat->GetOutlet();

	this->End = DstStat->GetInlet();


	int SrcType = SrcStat->GetStatementType();
	int DstType = DstStat->GetStatementType();
	int SrcWidth, DstWidth;
	if (SrcType == 0) SrcWidth = StartEndX;
	if (SrcType == 1 || SrcType == 2) SrcWidth = AssignX;
	if (SrcType == 3) SrcWidth = ConditionalX;
	if (SrcType == 4) SrcWidth = IOX;

	if (DstType == 0) DstWidth = StartEndX;
	if (DstType == 1 || DstType == 2) DstWidth = AssignX;
	if (DstType == 3) DstWidth = ConditionalX;
	if (DstType == 4) DstWidth = IOX;
	ConnPoints.push_back(Start);

	if (End.y>Start.y)
	{
		Intermediate1.x = Start.x;
		Intermediate2.x = End.x;
		Intermediate1.y = Start.y + 8;
		Intermediate2.y = Intermediate1.y;
		AllIntermediateUsed = false;
		ConnPoints.push_back(Intermediate1);
		ConnPoints.push_back(Intermediate2);

	}
	else
	{
		AllIntermediateUsed = true;
		Intermediate1.x = Start.x;
		Intermediate1.y = Start.y + 8;
		Intermediate4.x = End.x;
		Intermediate4.y = End.y - 8;
		Intermediate2.y = Intermediate1.y;
		Intermediate3.y = Intermediate4.y;
		if (abs(Start.x - DstStat->GetOutlet().x) > 0.5*(SrcWidth + DstWidth))
		{
			if (Start.x >= DstStat->GetOutlet().x)
				Intermediate2.x = (int)(Start.x - 0.5*SrcWidth - 8);
			else
				Intermediate2.x = (int)(Start.x + 0.5*SrcWidth + 8);
		}
		else
		{
			if (Start.x >= DstStat->GetOutlet().x)
				Intermediate2.x = (int)(End.x - 0.5*DstWidth - 8);
			else
				Intermediate2.x = (int)(End.x + 0.5*DstWidth + 8);
		}
		Intermediate3.x = Intermediate2.x;
		ConnPoints.push_back(Intermediate2);
		ConnPoints.push_back(Intermediate3);
		ConnPoints.push_back(Intermediate4);
	}
	ConnPoints.push_back(End);
}

int Connector::GetBranchType()
{
	return this->BranchType;
}


void Connector::Edit(ApplicationManager* pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Add a Connector: choose your source statement");
	pIn->GetPointClicked(Start);
	int Type;
	StartEnd* pSE;
	//First: Get Correctly my SourcePoint
	SrcStat = pManager->GetStatement(Start, Type);
	if (Type == 0)
		pSE = dynamic_cast<StartEnd*>(SrcStat);
	while (!SrcStat || (Type == 0 && pSE->GetMode()) || (SrcStat->GetpConn() != NULL && SrcStat->GetpConn() != this) || (Type == 3 && ((Conditional*)(SrcStat))->GetpConnL() != NULL && ((Conditional*)(SrcStat))->GetpConnL()!=this) )
	{
		pOut->PrintMessage("Edit Connector: choose your source statement");
		pIn->GetPointClicked(Start);
		SrcStat = pManager->GetStatement(Start, Type);
		if (Type == 0)
			pSE = dynamic_cast<StartEnd*>(SrcStat);
	}
	if (Type == 3)
	{

		int DeltaR = abs(((Conditional*)SrcStat)->GetOutlet().x - Start.x);
		int DeltaL = abs(((Conditional*)SrcStat)->GetOutletLeft().x - Start.x);
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

	pIn->GetPointClicked(End);
	DstStat = pManager->GetStatement(End, Type);
	if (Type == 0)
		pSE = dynamic_cast<StartEnd*>(DstStat);
	while (!DstStat || (Type == 0 && !pSE->GetMode()))
	{
		pOut->PrintMessage("Edit Connector: choose your destination statement");
		pIn->GetPointClicked(End);
		DstStat = pManager->GetStatement(End, Type);
		if (Type == 0)
			pSE = dynamic_cast<StartEnd*>(DstStat);
	}

	if (BranchType == 2)
	{
		Start = ((Conditional*)SrcStat)->GetOutletLeft();
		((Conditional*)SrcStat)->SetpConnL(this);
	}
	else
	{
		Start = SrcStat->GetOutlet();
		SrcStat->SetpConn(this);
	}

	End = DstStat->GetInlet();
	SrcStat->SetpConn(this);
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
}




//void Connector::ZoomInOut(int f,int c)
//{}


vector<Point> Connector::GetConnPoints() const
{
	return ConnPoints;
}

bool Connector::LineInclinasion(Point P1, Point P2)
{
	if (P1.x == P2.x)
		return false;
	else
		return true;
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}
bool Connector::IsSelected()
{
	return Selected;
}

void Connector::SetCopiedOrCut(int C)
{
	CopiedOrCut = C;
}