#include "UndoRedo.h"
#include <sstream>

int UndoRedo::HistoryCounter = -1;
int UndoRedo::CurrentStep = -1;
int UndoRedo::MaxCounter = 0;
UndoRedo::UndoRedo(ApplicationManager *pManager, bool M) : Action(pManager)
{
	Mode = M;
}

void UndoRedo::UnReSAVE(ApplicationManager *pAppManager)
{
	MaxCounter++;

	CurrentStep++;
	HistoryCounter = CurrentStep;

	ostringstream FileName;
	FileName << "TmpFC" << CurrentStep << ".txt";
	
	Save *S = new Save(pAppManager, FileName.str());
	S->Execute();
}

void UndoRedo::UnReTMPDelete()
{
	for (int i = 0; i <= MaxCounter; i++)
	{
		ostringstream FileName;
		FileName << "TmpFC" << i << ".txt";
		string S = FileName.str();
		remove(S.c_str());
	}
}

void UndoRedo::Execute()
{
	if (Mode) //Undo
	{
		if (CurrentStep == 0)
		{
			this->pManager->GetOutput()->PrintMessage("Can't Undo, press any key to continue");
			Point Temp;
			this->pManager->GetInput()->GetPointClicked(Temp);
			this->pManager->GetOutput()->PrintMessage("");
			return;
		}
		else
		{
			CurrentStep--;
			ostringstream FileName;
			FileName << "TmpFC" << CurrentStep << ".txt";
			Load *L = new Load(pManager, FileName.str());
			L->Execute();
			this->pManager->GetOutput()->PrintMessage("Undo, press any key to continue");
			Point Temp;
			this->pManager->GetInput()->GetPointClicked(Temp);
			this->pManager->GetOutput()->PrintMessage("");
			return;
		}
	}
	else //Redo
	{
		if (CurrentStep == HistoryCounter)
		{
			this->pManager->GetOutput()->PrintMessage("Can't Redo, press any key to continue");
			Point Temp;
			this->pManager->GetInput()->GetPointClicked(Temp);
			this->pManager->GetOutput()->PrintMessage("");
			return;
		}
		else
		{
			CurrentStep++;
			ostringstream FileName;
			FileName << "TmpFC" << CurrentStep << ".txt";
			Load *L = new Load(pManager, FileName.str());
			L->Execute();
			this->pManager->GetOutput()->PrintMessage("Redo, press any key to continue");
			Point Temp;
			this->pManager->GetInput()->GetPointClicked(Temp);
			this->pManager->GetOutput()->PrintMessage("");
			return;
		}
	}
}
