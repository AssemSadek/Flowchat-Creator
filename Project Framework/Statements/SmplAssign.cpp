#include "SmplAssign.h"
#include <sstream>

#include "../ApplicationManager.h"

using namespace std;

SmplAssign::SmplAssign(Point Centre, string LeftHS, string RHSStr, double RHSDbl, bool RHSTYP)
{
	LHS = LeftHS;
	RHSDouble = RHSDbl;
	RHSString = RHSStr;
	RHSType = RHSTYP;

	UpdateStatementText();

	pConn = NULL;	//No connectors yet

	LeftCorner.x = Centre.x - 80;
	LeftCorner.y = Centre.y - 40;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 40;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 40;
}

void SmplAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void SmplAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, Text, Selected);
}


//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if(LHS=="")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS;
		T << " = ";
		if (RHSType) //RHS
			T << RHSString;
		else
			T << RHSDouble;
		Text = T.str();	 
	}
}

int SmplAssign::GetStatementType()
{
	return 1;
}

void SmplAssign::Save(ofstream &OutFile)
{
	OutFile << "SmplAssign \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y << "\t" << LHS;
	OutFile << "\t" << this->RHSType << "\t" << this->RHSDouble << "\t" << this->RHSString << "\t \" " << Comment << " \"" << endl;
}

void SmplAssign::Load(ifstream &Infile)
{
	char x;
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS;
	Infile >> RHSType >> RHSDouble >> RHSString >> x;
	getline(Infile, Comment, '\"');
	UpdateStatementText();
	this->UpdatePoints();
}

void SmplAssign::UpdatePoints()
{
	Point Centre;

	Centre.x = LeftCorner.x + 80;
	Centre.y = LeftCorner.y + 40;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 40;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 40;
}

int SmplAssign::Run(ApplicationManager *pManager, Statement *&NextStat)
{
	//Check if Left Hand Side exists in the Memory Stack
	if (pManager->GetMemoryStack().Contains(this->LHS))
	{
		//If RHS is Variable Name
		if (this->RHSType)
		{
			//Check if Right Hand Side exists in the Memory Stack
			if (pManager->GetMemoryStack().Contains(this->RHSString))
			{
				pManager->GetMemoryStack()[LHS] = pManager->GetMemoryStack()[RHSString];
				NextStat = pConn->getDstStat();
				return 1; //Done Correctly
			}
			else
				return -2; //Error '-2': RHS doesn't exist in Memory Stack
		}
		//If RHS is Value
		else
		{
			pManager->GetMemoryStack()[LHS] = RHSDouble;
			NextStat = pConn->getDstStat();
			return 1; //Done Correctly
		}
	}
	//Add LHS to Memory Stack and Add its Value
	else
	{
		//If LHS is Variable Name
		if (this->RHSType)
		{
			//Check if Right Hand Side exists in the Memory Stack
			if (pManager->GetMemoryStack().Contains(this->RHSString))
			{
				pManager->GetMemoryStack() += {LHS, pManager->GetMemoryStack()[RHSString]};
				NextStat = pConn->getDstStat();
				return 1; //Done Correctly
			}
			else
				return -2; //Error '-2': RHS doesn't exist in Memory Stack
		}
		//If RHS is Value
		else
		{
			pManager->GetMemoryStack() += {LHS, RHSDouble};
			NextStat = pConn->getDstStat();
			return 1; //Done Correctly
		}
	}
}

void SmplAssign::Edit(ApplicationManager* pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Please re-assign");
	string TempLHS = pIn->GetString(pOut);
	pOut->PrintMessage("");
	bool TempRHSType;
	string TempRHSString;
	double TempRHSDouble;
	pIn->GetMixed(pOut, TempRHSType, TempRHSString, TempRHSDouble);
	pOut->PrintMessage("");
	LHS = TempLHS;
	RHSType = TempRHSType;
	RHSDouble = TempRHSDouble;
	RHSString = TempRHSString;
	UpdateStatementText();
	pOut->ClearDrawArea();
}