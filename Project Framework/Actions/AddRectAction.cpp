#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddRectAction::AddRectAction(ApplicationManager *pManager):Action(pManager)
{}


void AddRectAction::ReadActionParameters()
	 
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Rectangle: Click at first corner");
	
	//Read 1st corner and store in x1,y1
	pIn->GetPointClicked(x1, y1);

	pOut->PrintMessage("Rectangle: Click at second corner");

	//Read 2nd corner and store in x2,y2
	pIn->GetPointClicked(x2, y2);

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	CRectangle *R=new CRectangle(x1, y1, x2, y2);

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
}
