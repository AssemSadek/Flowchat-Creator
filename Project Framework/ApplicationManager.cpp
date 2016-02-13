#include "ApplicationManager.h"

#include "MemoryStack\MemoryStack.h"

#include "Actions\AddSmplAssign.h"
#include "Actions\AddVariableAssign.h"
#include "Actions\AddStartEnd.h"
#include "Actions\AddConditional.h"
#include "Actions\AddConnector.h"
#include "Actions\Select.h"
#include "Actions\Move.h"
#include "Actions\UndoRedo.h"
#include "Actions\Delete.h"
#include "Actions\Edit.h"
#include "Actions\Switch.h"
#include "Actions\Comment.h"
#include "Actions\ZoomIn.h"

#include "Actions\Switch.h"

#include "Actions\Validate.h"
#include "Actions\Run.h"
#include "Actions\GenerateCode.h"

#include "GUI\Input.h"
#include "GUI\Output.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	pSelectedStat = NULL;	//no Statement is selected yet
	
	//Save tmp first state for undo redo
	//to keep track of history and steps for Undo and Redo
	UndoRedo::UnReSAVE(this);
}

///*
MemoryStack& ApplicationManager::GetMemoryStack()
{
	return MemStack;
}


//Assem
int ApplicationManager::GetStatCount()
{
	return StatList.size();
}

list<Statement*> ApplicationManager::GetStatList()
{
	return StatList;
}

list<Statement*>* ApplicationManager::GetStatList_Editable()
{
	return &StatList;
}

//Hamada
int ApplicationManager::GetConnCount()
{
	return ConnList.size();
}

list<Connector*>& ApplicationManager::GetConnList()
{
	return ConnList;
}

list<Connector*>* ApplicationManager::GetConnList_Editable()
{
	return &ConnList;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction(Point &P) const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction(P);
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType,Point P)
{
	Action* pAct = NULL;
	string s;

	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
	case ADD_BEGIN_END:
		pAct = new AddStartEnd(this);
		break;
	case ADD_SMPL_ASSIGN:
		pAct = new AddSmplAssign(this);
		break;
	case ADD_VAR_ASSIGN:
		pAct = new AddVariableAssign(this);
		break;
	case ADD_CONDITIONAL:
		pAct = new AddConditional(this);
		break;
	case ADD_IN_OUT:
		pAct = new AddReadWrite(this);
		break;
	case ADD_CONNECTOR:
		pAct = new AddConnector(this);
		break;
	case EDIT_STAT:
		///create EDIT_STAT Action here
		pAct = new Edit(this);
		break;
	case COMMENT:
		///create COMMENT Action here
		pAct = new Comment(this);
		break;
	case DEL:
		///create DEL Action here
		pAct = new Delete(this);
		break;
	case SELECT:
		pAct = new Select(this, P);
		break;
	case MOVE:
		///create MOVE Action here
		pAct = new Move(this, P);
		break;
	case COPY:
		pAct = new Copy(this);
		break;
	case CUT:
		pAct = new Cut(this);
		break;
	case PASTE:
		pAct = new Paste(this);
		break;
	case UNDO:
		///create UNDO Action here
		pAct = new UndoRedo(this, true); // true means Undo
		break;
	case REDO:
		///create REDO Action here
		pAct = new UndoRedo(this, false); // false means Redo
		break;
	case SAVE:
		///create SAVE Action here
		pOut->PrintMessage("Please Enter File Name: ");
		s = pIn->GetString(pOut);
		s += ".txt";
		pAct = new Save(this,s);
		break;
	case LOAD:
		///create LOAD Action here
		pOut->PrintMessage("Please Enter File Name: ");
		s = pIn->GetString(pOut);
		pAct = new Load(this, s);
		break;
	case ZOOM:
		pAct = new ZoomIn(this);
		break;
	case SIM_MODE:
	case DSN_MODE:
		///create SIM_MODE Action here
		pAct = new Switch(this);
		break;
	case EXIT:
		///create Exit Action here
		break;
	case STATUS:
		return;
	case DRAWING_AREA:
		pAct = new Select(this, P);
		break;

		//Simulation Mode Actions
	case VALIDATE:
		pAct = new Validate(this);
		break;
	case RUN:
		pAct = new Run(this, false);
		break;
	case STEPS:
		pAct = new Run(this, true);
		break;
	case GENCODE:
		pAct = new GenerateCode(this);
		break;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}

	//If any action except Undo or Redo or Save or Load or Select or Click on Drawing Area we save a temp file
	//to keep track of history and steps for Undo and Redo
	if (ActType != UNDO && ActType != REDO && ActType != SAVE && ActType != LOAD && ActType != DRAWING_AREA)
		UndoRedo::UnReSAVE(this);

}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	StatList.push_back(pStat);
}

//Assem
void ApplicationManager::AddConnector1(Connector *pCon)
{
	ConnList.push_back(pCon);
}
//

//Delete a statement from the list of statements
void ApplicationManager::DeleteStatement(Statement *pStat)
{
	delete pStat;
	StatList.remove(pStat);
	SelectedStatements.remove(pStat);
}


////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
list<Statement*> ApplicationManager::GetSelectedStatements() const
{
	return SelectedStatements;
}

list<Statement*>* ApplicationManager::GetSelectedStatements_Editable()
{
	return &SelectedStatements;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{
	pSelectedStat = pStat;
}

int ApplicationManager::GetCorners(Statement *S, Point &LeftCornerUp, Point &LeftCornerDown, Point &RightCornerUp, Point &RightCornerDown)
{
	int Type = S->GetStatementType();
	//to check overlapping, see if any of 4 corners belongs to a statment
	LeftCornerUp = LeftCornerDown = RightCornerUp = RightCornerDown = S->GetLeftCorner();
	switch (Type)
	{
	case 0:
		LeftCornerDown.y += StartEndY;
		RightCornerUp.x = RightCornerDown.x = LeftCornerUp.x + StartEndX;
		RightCornerDown.y += StartEndY;
		break;
	case 1:
	case 2:
		LeftCornerDown.y += AssignY;
		RightCornerUp.x = RightCornerDown.x = LeftCornerUp.x + AssignX;
		RightCornerDown.y += AssignY;
		break;
	case 3:
		LeftCornerDown.y += ConditionalY;
		RightCornerUp.x = RightCornerDown.x = LeftCornerUp.x + ConditionalX;
		RightCornerDown.y += ConditionalY;
		break;
	case 4:
		LeftCornerDown.y += IOY;
		RightCornerUp.x = RightCornerDown.x = LeftCornerUp.x + IOX;
		RightCornerDown.y += IOY;
		break;
	}
	return Type;
}
void ApplicationManager::GetCorners(Point P, int Type, Point &LeftCornerUp, Point &LeftCornerDown, Point &RightCornerUp, Point &RightCornerDown)
{
	LeftCornerUp = LeftCornerDown = RightCornerUp = RightCornerDown = P;
	switch (Type)
	{
	case 0:
		LeftCornerUp.y = RightCornerUp.y = P.y - StartEndY / 2;
		LeftCornerDown.y = RightCornerDown.y = P.y + StartEndY / 2;
		LeftCornerUp.x = LeftCornerDown.x = P.x - StartEndX / 2;
		RightCornerUp.x = RightCornerDown.x = P.x + StartEndX / 2;
		break;
	case 1:
		LeftCornerUp.y = RightCornerUp.y = P.y - AssignY / 2;
		LeftCornerDown.y = RightCornerDown.y = P.y + AssignY / 2;
		LeftCornerUp.x = LeftCornerDown.x = P.x - AssignX / 2;
		RightCornerUp.x = RightCornerDown.x = P.x + AssignX / 2;
		break;
	case 2:
		LeftCornerUp.y = RightCornerUp.y = P.y - ConditionalY / 2;
		LeftCornerDown.y = RightCornerDown.y = P.y + ConditionalY / 2;
		LeftCornerUp.x = LeftCornerDown.x = P.x - ConditionalX / 2;
		RightCornerUp.x = RightCornerDown.x = P.x + ConditionalX / 2;
		break;
	case 3:
		LeftCornerUp.y = RightCornerUp.y = P.y - IOY / 2;
		LeftCornerDown.y = RightCornerDown.y = P.y + IOY / 2;
		LeftCornerUp.x = LeftCornerDown.x = P.x - IOX / 2;
		RightCornerUp.x = RightCornerDown.x = P.x + IOX / 2;
		break;
	}
}

bool ApplicationManager::PointIncludedInCorners(Point P, Point LEFTUP, Point LEFTDOWN, Point RIGHTUP, Point RIGHTDOWN)
{
	if (P.x >= LEFTUP.x && P.x <= RIGHTUP.x &&
		P.y >= LEFTUP.y && P.y <= LEFTDOWN.y)
		return true;
	return false;
}

bool ApplicationManager::IsOverlapping(Statement *S)
{
	//Check overlapping with another statement
	Point LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown;
	int Type = GetCorners(S, LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown);
	Point Center, CenterLeft, CenterRight;
	Center.x = (LeftCornerUp.x + RightCornerUp.x) / 2;
	Center.y = (LeftCornerUp.y + RightCornerDown.y) / 2;
	CenterLeft.x = LeftCornerUp.x;
	CenterLeft.y = CenterRight.y = Center.y;
	CenterRight.x = RightCornerUp.x;
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		//If trying checking overlapping with the same statement just continue and don't check
		if ((*it) == S)
			continue;

		//Get Statement Type and Corners
		//// 0 StartEnd
		//// 1 SMPLAssignment
		//// 2 VARAssignment
		//// 3 Conditional
		//// 4 Read Write
		Point itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown;
		int Type = GetCorners((*it), itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown);

		//Check if any of Statement S's corners is included between the Statement it's corner
		if (
			////Check LeftCorner Up
			PointIncludedInCorners(LeftCornerUp, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown) ||
			////or Check LeftCorner Down
			PointIncludedInCorners(LeftCornerDown, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown) ||
			////or Check RightCorner Up
			PointIncludedInCorners(RightCornerUp, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown) ||
			////or Check RightCorner Down
			PointIncludedInCorners(RightCornerDown, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown) ||
			////or Check Center
			PointIncludedInCorners(Center, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown) ||
			////or Check CenterLeft
			PointIncludedInCorners(CenterLeft, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown) ||
			////or Check CenterRight
			PointIncludedInCorners(CenterRight, itLeftCornerUp, itLeftCornerDown, itRightCornerUp, itRightCornerDown)
			)
			return true;
	}
	return false;
}
bool ApplicationManager::IsOverlapping(StatementAction *SA, Point P)
{
	int Type;
	if (dynamic_cast<AddStartEnd*>(SA))
	{
		Type = 0;
	}
	else if (dynamic_cast<AddSmplAssign*>(SA) || dynamic_cast<AddVariableAssign*>(SA))
	{
		Type = 1;
	}
	else if (dynamic_cast<AddConditional*>(SA))
	{
		Type = 2;
	}
	else if (dynamic_cast<AddReadWrite*>(SA))
	{
		Type = 3;
	}
	//to check overlapping, see if any of 4 corners belongs to a statment
	Point LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown;
	GetCorners(P, Type, LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown);
	
	//if returns any statement->overlapping,, if returns all null->not overlapping
	if (GetStatement(LeftCornerUp, Type) || GetStatement(LeftCornerDown, Type) || GetStatement(RightCornerUp, Type) || GetStatement(RightCornerDown, Type) || GetStatement(P, Type))
		return true;
	return false;
}

bool ApplicationManager::IsOutOfBounds(Statement *S, bool &Top, bool &Bottom, bool &Left, bool &Right)
{
	Point LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown;
	int Type = GetCorners(S, LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown);
	bool FlagIsOOB = false;
	//Check Upper Bounds
	if (LeftCornerUp.y <= UI.TlBrWdth + 30)
	{
		Top = true;
		FlagIsOOB = true;
	}
		//Check Lower Bounds
	if (LeftCornerDown.y >= (UI.BGHeight - UI.StBrWdth)-10)
	{
		Bottom = true;
		FlagIsOOB = true;
	}
	//Check Left Bounds
	if (LeftCornerUp.x < 60)
	{
		Left = true;
		FlagIsOOB = true;
	}
	if (RightCornerUp.x>(UI.BGWidth-50))
	{
		Right = true;
		FlagIsOOB = true;
	}
	return FlagIsOOB;

}

bool ApplicationManager::IsOutOfBounds(StatementAction *SA, Point P)
{
	int Type;
	if (dynamic_cast<AddStartEnd*>(SA))
	{
		Type = 0;
	}
	else if (dynamic_cast<AddSmplAssign*>(SA) || dynamic_cast<AddVariableAssign*>(SA))
	{
		Type = 1;
	}
	else if (dynamic_cast<AddConditional*>(SA))
	{
		Type = 2;
	}
	else if (dynamic_cast<AddReadWrite*>(SA))
	{
		Type = 3;
	}
	//to check overlapping, see if any of 4 corners belongs to a statment
	Point LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown;
	GetCorners(P, Type, LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown);

	//Check Upper Bounds
	if (LeftCornerUp.y <= UI.TlBrWdth + 30)
		return true;
	//Check Lower Bounds
	if (LeftCornerDown.y >= (UI.BGHeight - UI.StBrWdth) - 10)
		return true;
	//Check Left Bounds
	if (LeftCornerUp.x < 60)
		return true;
	if (RightCornerUp.x>(UI.BGWidth - 50))
		return true;
	return false;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface()
{

	//Draw all statements
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		if ((*it)->GetCopiedOrCut() != 2)
			(*it)->Draw(pOut);
	}
	//Draw all connections
	for (list<Connector*>::iterator it = ConnList.begin(); it != ConnList.end(); it++)
		(*it)->Draw(pOut);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	//Delete all Tmp Files of Undo and Redo
	UndoRedo::UnReTMPDelete();
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
		delete (*it);
	for (list<Connector*>::iterator it = ConnList.begin(); it != ConnList.end(); it++)
		delete (*it);
	delete pIn;
	delete pOut;
}

Statement* ApplicationManager::GetStatement(Point P, int &Type)
{
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		//Determine Type
		// 0 StartEnd
		// 1 SMPLAssignment
		// 2 VARAssignment
		// 3 Conditional
		// 4 Read Write
		Type = -1;
		if (dynamic_cast<StartEnd*>((*it)))
		{
			Type = 0;
		}
		else if (dynamic_cast<SmplAssign*>((*it)))
		{
			Type = 1;
		}
		else if (dynamic_cast<VariableAssign*>((*it)))
		{
			Type = 2;
		}
		else if (dynamic_cast<Conditional*>((*it)))
		{
			Type = 3;
		}
		else if (dynamic_cast<ReadWrite*>((*it)))
		{
			Type = 4;
		}
		switch (Type)
		{
		case 0:
			if (P.x >= (*it)->GetLeftCorner().x && P.x <= (*it)->GetLeftCorner().x + StartEndX &&
				P.y >= (*it)->GetLeftCorner().y && P.y <= (*it)->GetLeftCorner().y + StartEndY)
			{
				return (*it);
			}
			break;
		case 1:
		case 2:
			if (P.x >= (*it)->GetLeftCorner().x && P.x <= (*it)->GetLeftCorner().x + AssignX &&
				P.y >= (*it)->GetLeftCorner().y && P.y <= (*it)->GetLeftCorner().y + AssignY)
			{
				return (*it);
			}
			break;
		case 3:
			if (P.x >= (*it)->GetLeftCorner().x && P.x <= (*it)->GetLeftCorner().x + ConditionalX &&
				P.y >= (*it)->GetLeftCorner().y && P.y <= (*it)->GetLeftCorner().y + ConditionalY)
			{
				return (*it);
			}
			break;
		case 4:
			if (P.x >= (*it)->GetLeftCorner().x && P.x <= (*it)->GetLeftCorner().x + IOX &&
				P.y >= (*it)->GetLeftCorner().y && P.y <= (*it)->GetLeftCorner().y + IOY)
			{
				return (*it);
			}
			break;
		}
	}
	return NULL;
}

void ApplicationManager::UpdateSelectedStatements(Statement *S)
{
	if (S->IsSelected())
	{
		SelectedStatements.push_back(S);
	}
	else
	{

		SelectedStatements.remove(S);
	}
}

//Unneeded Function - replaced with Execute in Save Class
void ApplicationManager::SaveALL(ofstream &OutFile)
{
	OutFile << StatList.size() << endl;
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
		(*it)->Save(OutFile);
}

//Unneeded Function - replaced with Execute in Load Class
void ApplicationManager::LoadALL(ifstream &InFile)
{
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
		delete (*it);
	for (list<Connector*>::iterator it = ConnList.begin(); it != ConnList.end(); it++)
		delete (*it);

	StatList.clear();
	ConnList.clear();
	SelectedStatements.clear();
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
		AddStatement(pSE);
	}

	//Clear Screen
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
	this->UpdateInterface();
}

//////////////Mostafa//////////////////////////////////
void ApplicationManager::UpdateCopiedOrCutStatements(int CopiedOrCut)
{
	if (CopiedOrCut == 0)
	{
		CopiedOrCutStatements.clear();
		return;
	}
	if (SelectedStatements.size() == 0 && CopiedOrCut == 1)
	{
		pOut->PrintMessage("Please, Select Statement(s) before copying!");
	}
	else if (SelectedStatements.size() == 0 && CopiedOrCut == 2)
	{
		pOut->PrintMessage("Please, Select Statement(s) before cutting!");
	}
	else
	{
		CopiedOrCutStatements.clear();
		for (list<Statement*>::iterator it = SelectedStatements.begin(); it != SelectedStatements.end(); it++)
		{
			(*it)->SetCopiedOrCut(CopiedOrCut);
			//Push back any statement if not copying a StartEnd Statement
			if (!(CopiedOrCut == 1 && (*it)->GetStatementType() == 0))
				CopiedOrCutStatements.push_back((*it));
			(*it)->SetSelected(false);
		}
		SelectedStatements.clear();
	}

}

list<Statement*> ApplicationManager::GetCopiedOrCutStatements()
{
	return CopiedOrCutStatements;
}

//Assem
void ApplicationManager::DeleteConnector(Connector* pConn)
{
	if (pConn == NULL)
		return;
	Statement *Src = pConn->getSrcStat();
	if (Src != NULL)
	{
		if (pConn->GetBranchType() == 2)
			((Conditional*)(Src))->SetpConnL(NULL);
		else
			Src->SetpConn(NULL);
	}
	delete pConn;
	ConnList.remove(pConn);
	SelectedConnectors.remove(pConn);
}

//Sherif & Mostafa - Unused
void ApplicationManager::genCode(string s)
{
	generatedCode.push_back(s);
}
void ApplicationManager::genCode(list<string> s)
{
//	copy(s.begin(), s.end(), back_inserter(generatedCode));
}

Connector* ApplicationManager::GetConnector(Point P) 
{
	list <Connector*> Temp = ConnList;
	for (list<Connector*>::iterator it = Temp.begin(); it != Temp.end(); it++)
	{
		(*it)->UpdateIntermediate();
		for (unsigned int i = 0; i < (*it)->GetConnPoints().size() - 1; i++)
		{
			Point P1 = (*it)->GetConnPoints()[i];
			Point P2 = (*it)->GetConnPoints()[i + 1];
			if ((*it)->LineInclinasion(P1, P2))
			{
				if (P1.x <= P2.x)
				if (P.x >= P1.x && P.x <= P2.x && P.y >= P1.y - 5 && P.y <= P1.y + 5)
					return (*it);
				if (P1.x>P2.x)
				if (P.x <= P1.x && P.x >= P2.x && P.y >= P1.y - 5 && P.y <= P1.y + 5)
					return (*it);
			}
			else
			{
				if (P1.y <= P2.y)
				if (P.y >= P1.y && P.y <= P2.y && P.x >= P1.x - 5 && P.x <= P1.x + 5)
					return (*it);
				if (P1.y >= P2.y)
				if (P.y <= P1.y && P.y >= P2.y && P.x >= P1.x - 2 && P.x <= P1.x + 2)
					return (*it);
			}

		}
	}
	return NULL;
}

list<Connector*>ApplicationManager::GetSelectedConnectors() const
{
	return SelectedConnectors;
}

void ApplicationManager::UpdateSelectedConnectors(Connector *C)
{
	if (C->IsSelected())
	{
		SelectedConnectors.push_back(C);
	}
	else
	{

		SelectedConnectors.remove(C);
	}
}

void ApplicationManager::RemoveStatementConnectors(Statement *Stat)
{
	int Type = Stat->GetStatementType();
	this->DeleteConnector(Stat->GetpConn());
	if (Type == 3)
		this->DeleteConnector(((Conditional*)(Stat))->GetpConnL());
	list<Connector*> TempConnList = this->ConnList;
	for (list<Connector*>::iterator it = TempConnList.begin(); it != TempConnList.end(); it++)
	{
		if ((*it)->getDstStat() == Stat)
			this->DeleteConnector((*it));
	}
}

void ApplicationManager::RemoveStatementFromStatListWithoutDeleting(Statement *Stat)
{
	StatList.remove(Stat);
}

void ApplicationManager::DeleteCutStatements()
{
	for (list<Statement*>::iterator it = CopiedOrCutStatements.begin(); it != CopiedOrCutStatements.end(); it++)
	{
		this->DeleteStatement((*it));
	}
	CopiedOrCutStatements.clear();
}