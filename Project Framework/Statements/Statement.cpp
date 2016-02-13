#include "../ApplicationManager.h"
#include "Statement.h"
#include "StartEnd.h"
#include "SmplAssign.h"
#include "VariableAssign.h"
#include "ReadWrite.h"
#include "Conditional.h"

Statement::Statement()	
{ 
	ID = ++IDCounter;
	Text = "";
	Selected = false;	
	Visited = false;
}

Statement::~Statement()
{
}

void Statement::SetID(int i)
{
	ID = i;
}

void Statement::SetSelected(bool s)
{
	Selected = s;
}

bool Statement::IsSelected() const
{
	return Selected;
}

void Statement::UpdateStatementText()
{}

Point Statement::GetLeftCorner()
{
	return LeftCorner;
}

void Statement::SetLeftCorner(Point P)
{
	LeftCorner = P;
}

//Hamada
int Statement::GetIDCounter()
{
	return IDCounter;
}

void Statement::IncrementIDCounter()
{
	IDCounter++;
}

int Statement::GetStatementType()
{
	//Determine Type
	// 0 StartEnd
	// 1 SMPLAssignment
	// 2 VARAssignment
	// 3 Conditional
	// 4 Read Write
	int Type = -1;
	if (dynamic_cast<StartEnd*>(this))
	{
		Type = 0;
	}
	else if (dynamic_cast<SmplAssign*>(this))
	{
		Type = 1;
	}
	else if (dynamic_cast<VariableAssign*>(this))
	{
		Type = 2;
	}
	else if (dynamic_cast<Conditional*>(this))
	{
		Type = 3;
	}
	else if (dynamic_cast<ReadWrite*>(this))
	{
		Type = 4;
	}
	return Type;
}

int Statement::IDCounter = 0;

////////////////Mostafa//////////////////
void Statement::SetCopiedOrCut(int C)
{
	CopiedOrCut = C;
}


int Statement::GetCopiedOrCut()const
{
	return CopiedOrCut;
}
/////////////////////////////////////////

//Assem
Point Statement::GetInlet()
{
	return Inlet;
}
Point Statement::GetOutlet()
{
	return Outlet;
}
//

//7mada
void Statement::SetInlet(Point P)
{
	Inlet = P;
}
void Statement::SetOutlet(Point P)
{
	Outlet = P;
}
//
void Statement::SetpConn(Connector* p)
{
	pConn = p;
}

Connector*& Statement::GetpConn()
{
	return pConn;
}

int  Statement::GetID()
{
	return ID;
}

void Statement::SetComment(string CMNT)
{
	this->Comment = CMNT;
}

string Statement::GetComment()
{
	return this->Comment;
}