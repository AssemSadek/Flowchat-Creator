#include "VariableAssign.h"
#include <sstream>

#include "../ApplicationManager.h"

using namespace std;

VariableAssign::VariableAssign(Point Centre, string LeftHS, string RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	pConn = NULL;	//No connectors yet

	LeftCorner.x = Centre.x - 80;
	LeftCorner.y = Centre.y - 40;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 40;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 40;
}

void VariableAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}


void VariableAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, Text, Selected);
}


//This function should be called when LHS or RHS changes
void VariableAssign::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = " << RHS;
		Text = T.str();
	}
}

int VariableAssign::GetStatementType()
{
	return 2;
}

void VariableAssign::Save(ofstream &OutFile)
{
	OutFile << "VarAssign \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y << "\t" << LHS << "\t \" " << RHS << "\" \t \" " << Comment << " \"" << endl;
}

void VariableAssign::Load(ifstream &Infile)
{
	char x;
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS;
	Infile >> x;
	getline(Infile, RHS, '\"');
	Infile >> x;
	getline(Infile, Comment, '\"');
	UpdateStatementText();
	this->UpdatePoints();
}


void VariableAssign::UpdatePoints()
{
	Point Centre;

	Centre.x = LeftCorner.x + 80;
	Centre.y = LeftCorner.y + 40;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 40;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 40;
}

int VariableAssign::Run(ApplicationManager *pManager, Statement *&NextStat)
{
	string Expression = RHS;
	string RPN; //Reverse Polish Notation
	pManager->GetInput()->Pad(Expression);
	if (pManager->GetInput()->ValidateExpression(Expression, pManager) != 1)
	{
		//Temporarily set any value in order to check if it is working
		return -3; //Error '-3': Invalid Complex Expression
		///////////////////////////////

	}
	
	pManager->GetInput()->ShuntingYardRPN(RHS, RPN);
	pManager->GetInput()->ConvertVariableToValue(RPN,pManager);
	double ExpressionValue = pManager->GetInput()->EvaluateRPN(RPN);
	if (pManager->GetMemoryStack().Contains(LHS)) //If Variable already exists
	{
		pManager->GetMemoryStack()[LHS] = ExpressionValue;
	}
	else //Add Variable to Memory Stack
	{
		pManager->GetMemoryStack() += {LHS, ExpressionValue};
	}
	NextStat = pConn->getDstStat();
	return 1;
}

void VariableAssign::Edit(ApplicationManager* pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Please assign");
	string TempLHS = pIn->GetString(pOut);
	pOut->PrintMessage("");
	string TempRHS = pIn->GetNormalString(pOut);
	pOut->PrintMessage("");

	LHS = TempLHS;
	RHS = TempRHS;
	UpdateStatementText();
	pOut->ClearDrawArea();
}