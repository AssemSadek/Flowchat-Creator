#include "Comment.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

Comment::Comment(ApplicationManager *pAppManager) :Action(pAppManager)
{}

//Reads parameters required for action to execute
void Comment::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point P;
	int Type;
	pOut->PrintMessage("Edit:Choose a statement to comment");
	pIn->GetPointClicked(P);
	ComStatement = pManager->GetStatement(P, Type);
	while (!ComStatement)
	{
		pIn->GetPointClicked(P);
		ComStatement = pManager->GetStatement(P, Type);
	}
	pOut->ClearStatusBar();
}


void Comment::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	string UserComment = pIn->GetNormalString(pOut);
	ComStatement->SetComment(UserComment);
	pOut->ClearStatusBar();
}