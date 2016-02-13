#include "StartEnd.h"

#include "../ApplicationManager.h"

bool StartEnd::StartDrawn = false;
bool StartEnd::EndDrawn = false;

StartEnd::StartEnd(Point Centre)
{
	if (StartDrawn == false)
	{
		//Draw Start
		this->Mode = false;
		StartDrawn = true;
	}
	else if (EndDrawn == false)
	{
		//Draw End
		this->Mode = true;
		EndDrawn = true;
	}

	pConn = NULL;	//No connectors yet

	LeftCorner.x = Centre.x - 70;
	LeftCorner.y = Centre.y - 34;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 34;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 34;
}

StartEnd::StartEnd(Point Centre, bool Type)
{
	this->Mode = Type;
	if (Type) //End
		EndDrawn = true;
	else //Start
		StartDrawn = true;

	pConn = NULL;	//No connectors yet

	LeftCorner.x = Centre.x - 70;
	LeftCorner.y = Centre.y - 34;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 34;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 34;
}

StartEnd::~StartEnd()
{
	if (this->Mode == false)
	{
		//It is Start
		StartDrawn = false;
	}
	else
	{
		//It is End
		EndDrawn = false;
	}
}

bool StartEnd::CanCreate()
{
	return !(StartDrawn&&EndDrawn);
}

void StartEnd::Draw(Output* pOut) const
{
	//Call Output::DrawStartEnd function to draw assignment statement 	
	if (this->Mode == false)
	{
		//Draw Start
		pOut->DrawStart(LeftCorner, Selected);
	}
	else
	{
		//Draw End
		pOut->DrawEnd(LeftCorner, Selected);
	}
}

bool StartEnd::GetMode()
{
	return this->Mode;
}

bool StartEnd::GetStartDrawn()
{
	return StartDrawn;
}

bool StartEnd::GetEndDrawn()
{
	return EndDrawn;
}

int StartEnd::GetStatementType()
{
	return 0;
}

void StartEnd::Save(ofstream &OutFile)
{
	if (Mode)
		OutFile << "END \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y << "\t" << " \" " << Comment << " \"" << endl;
	else
		OutFile << "START \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y << "\t" << " \" " << Comment << " \" " << endl;
}

void StartEnd::Load(ifstream &Infile)
{
	char x;
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> x;
	getline(Infile, Comment, '\"');
	UpdateStatementText();
	this->UpdatePoints();
}

void StartEnd::UpdatePoints()
{
	Point Centre;

	Centre.x = LeftCorner.x + 70;
	Centre.y = LeftCorner.y + 34;

	Inlet.x = Centre.x;
	Inlet.y = Centre.y - 34;

	Outlet.x = Centre.x;
	Outlet.y = Centre.y + 34;
}

int StartEnd::Run(ApplicationManager *pManager, Statement *&NextStat)
{
	if (this->Mode==false) //Start Mode
	{
		pManager->GetOutput()->PrintMessage("Starting the Flow Chart");
		NextStat = pConn->getDstStat();
	}
	else
	{
		pManager->GetOutput()->PrintMessage("Ending the Flow Chart");
		NextStat = NULL;
	}
	return 1;
}
void StartEnd::Edit(ApplicationManager* pManager)
{}
