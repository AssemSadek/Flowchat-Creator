#include "Conditional.h"
#include <sstream>

#include "../ApplicationManager.h"

using namespace std;

Conditional::Conditional(Point Centre, string LHSStr, double LHSDbl, bool LHSTYP, string Oprtr, string RHSStr, double RHSDbl, bool RHSTYP)
{
	LHSDouble = LHSDbl;
	LHSString = LHSStr;
	LHSType = LHSTYP;

	RHSDouble = RHSDbl;
	RHSString = RHSStr;
	RHSType = RHSTYP;

	Operator = Oprtr;

	UpdateStatementText();

	pConn = NULL;	//No connectors yet
	pConnL = NULL;
	LeftCorner.x = Centre.x - 70;
	LeftCorner.y = Centre.y - 70;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 70;

	Outlet.x = Centre.x + 70;
	Outlet.y = Centre.y;
	OutletLeft.x = Centre.x - 70;
	OutletLeft.y = Centre.y;
}

void Conditional::setLHS(const string &LS, const double &LD, bool LType)
{
	LHSDouble = LD;
	LHSString = LS;
	LHSType = LType;
	UpdateStatementText();
}

void Conditional::setRHS(const string &RS, const double &RD, bool RType)
{
	RHSDouble = RD;
	RHSString = RS;
	RHSType = RType;
	UpdateStatementText();
}

void Conditional::GetLHS(string &LS, double &LD, bool &LType)
{
	LS = LHSString;
	LD = LHSDouble;
	LType = LHSType;
}
void Conditional::GetRHS(string &RS, double &RD, bool &RType)
{
	RS = RHSString;
	RD = RHSDouble;
	RType = RHSType;
}

//7mada
Point Conditional::GetOutletLeft()
{
	return OutletLeft;
}

void Conditional::SetOutletLeft(Point P)
{
	OutletLeft = P;
}
//

void Conditional::setOperator(const string &O)
{
	Operator = O;
	UpdateStatementText();
}

void Conditional::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawConditional(LeftCorner, Text, Selected);
}

//This function should be called when LHS or RHS changes
void Conditional::UpdateStatementText()
{
	if (LHSString == "" && LHSDouble == 0)	//No left handside ==>statement have no valid text yet
		Text = "    ";
	else
	{
		//Build the statement text: LHS then Operator then RHS
		ostringstream T;

		if (LHSType) //LHS
			T << LHSString;
		else
			T << LHSDouble;

		T << " " << Operator << " ";

		if (RHSType) //RHS
			T << RHSString;
		else
			T << RHSDouble;
		Text = T.str();
	}
}

int Conditional::GetStatementType()
{
	return 3;
}

void Conditional::Save(ofstream &OutFile)
{
	OutFile << "Conditional \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y;
	OutFile << "\t" << this->LHSType << "\t" << this->LHSDouble << "\t" << this->LHSString;
	OutFile << "\t" << this->Operator;
	OutFile << "\t" << this->RHSType << "\t" << this->RHSDouble << "\t" << this->RHSString << "\t \" " << Comment << " \"" << endl;
}

void Conditional::Load(ifstream &Infile)
{
	char x;
	Infile >> ID >> LeftCorner.x >> LeftCorner.y;
	Infile >> LHSType >> LHSDouble >> LHSString;
	Infile >> this->Operator;
	Infile >> RHSType >> RHSDouble >> RHSString >> x;
	getline(Infile, Comment, '\"');
	UpdateStatementText();
	this->UpdatePoints();
}

//void Conditional::SetDeltaR(int x)
//{
//	DeltaR = x;
//}
//void Conditional::SetDeltaL(int x)
//{
//	DeltaL = x;
//}
//int Conditional::GetDeltaR()
//{
//	return DeltaR;
//}
//int Conditional::GetDeltaL()
//{
//	return DeltaL;
//}
void Conditional::SetpConnL(Connector* p)
{
	pConnL = p;
}

Connector*& Conditional::GetpConnL()
{
	return pConnL;
}

void Conditional::UpdatePoints()
{
	Point Centre;

	Centre.x = LeftCorner.x + 70;
	Centre.y = LeftCorner.y + 70;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 70;

	Outlet.x = Centre.x + 70;
	Outlet.y = Centre.y;
	OutletLeft.x = Centre.x - 70;
	OutletLeft.y = Centre.y;
}

int Conditional::Run(ApplicationManager *pManager, Statement *&NextStat)
{
	double TempLHS;
	double TempRHS;
	
	//LHS Variable
	if (LHSType)
	{
		if (pManager->GetMemoryStack().Contains(LHSString))
			TempLHS = pManager->GetMemoryStack()[LHSString];
		else
			return -1; //Error '-1': LHS not in stack memory
	}
	//LHS Value
	else
		TempLHS = LHSDouble;

	//RHS Variable
	if (RHSType)
	{
		if(pManager->GetMemoryStack().Contains(RHSString))
			TempRHS = pManager->GetMemoryStack()[RHSString];
		else
			return -2; //Error '-1': RHS not in stack memory
	}
	//RHS Value
	else
		TempRHS = RHSDouble;

	if (this->Operator == "<" )
	{
		if (TempLHS < TempRHS) //True
			NextStat = this->pConn->getDstStat();
		else
			NextStat = this->pConnL->getDstStat();
	}
	else if(this->Operator == ">")
	{
		if (TempLHS > TempRHS) //True
			NextStat = this->pConn->getDstStat();
		else
			NextStat = this->pConnL->getDstStat();
	}
	else if (this->Operator == "<=")
	{
		if (TempLHS <= TempRHS) //True
			NextStat = this->pConn->getDstStat();
		else
			NextStat = this->pConnL->getDstStat();
	}
	else if (this->Operator == ">=")
	{
		if (TempLHS >= TempRHS) //True
			NextStat = this->pConn->getDstStat();
		else
			NextStat = this->pConnL->getDstStat();
	}
	else if (this->Operator == "==")
	{
		if (TempLHS == TempRHS) //True
			NextStat = this->pConn->getDstStat();
		else
			NextStat = this->pConnL->getDstStat();
	}
	else if (this->Operator == "!=")
	{
		if (TempLHS != TempRHS) //True
			NextStat = this->pConn->getDstStat();
		else
			NextStat = this->pConnL->getDstStat();
	}
	return 1;
}

void Conditional::Edit(ApplicationManager* pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Get LeftHandSide
	pOut->PrintMessage("Please enter variable name or value");
	bool TempLHSType;
	string TempLHSString;
	double TempLHSDouble;
	pIn->GetMixed(pOut, TempLHSType, TempLHSString, TempLHSDouble);

	//Get Operator
	pOut->PrintMessage("Please enter operator");
	string TempOprtr = pIn->GetOperator(pOut);

	//Get RightHandSide
	pOut->PrintMessage("Please enter variable name or value");
	bool TempRHSType;
	string TempRHSString;
	double TempRHSDouble;
	pIn->GetMixed(pOut, TempRHSType, TempRHSString, TempRHSDouble);
	LHSString = TempLHSString;
	LHSDouble = TempLHSDouble;
	LHSType = TempLHSType;
	RHSString = TempRHSString;
	RHSDouble = TempRHSDouble;
	RHSType = TempRHSType;
	Operator = TempOprtr;
	UpdateStatementText();
	pOut->ClearStatusBar();
	pOut->ClearDrawArea();
}