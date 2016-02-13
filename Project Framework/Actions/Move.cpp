#include "Move.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Move::Move(ApplicationManager *pAppManager, Point P) :Action(pAppManager)
{
	BeginningPoint = P;
	SelectedStatements = pManager->GetSelectedStatements();
	pWind = pManager->GetOutput()->GetWindow();
}

void Move::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	int X, Y, dx, dy;
	pWind->SetBuffering(true);
	while (pWind->GetButtonState(RIGHT_BUTTON, X, Y) == BUTTON_DOWN)
	{
		dx = X - BeginningPoint.x;
		dy = Y - BeginningPoint.y;
		BeginningPoint.x = X;
		BeginningPoint.y = Y;
		pOut->ClearDrawArea();
		for (list<Statement*>::iterator it = SelectedStatements.begin(); it != SelectedStatements.end(); it++)
		{
			bool Top, Bottom, Left, Right;
			Top = Bottom = Left = Right = false;
			Point NewLeftCorner = (*it)->GetLeftCorner();
			//////////////////////Look hhhhhhhhhhhhhhhhhheeeeeeeeeeeeeere
			///////////////////
			////////////////
			///////////////
			//Check overlapping
			//////////////////

			if (!pManager->IsOutOfBounds((*it), Top, Bottom, Left, Right))
			{
				NewLeftCorner.x += dx;
				NewLeftCorner.y += dy;
				(*it)->SetLeftCorner(NewLeftCorner);
				if (pManager->IsOverlapping((*it))) // if new point overlaps undo the movement
				{
					NewLeftCorner.x -= dx;
					NewLeftCorner.y -= dy;
					(*it)->SetLeftCorner(NewLeftCorner);
				}
				else // Complete the movement of other points of the statement
				{
					/*
					Point Temp = (*it)->GetInlet();//Edit Inlet
					Temp.x += dx;
					Temp.y += dy;
					(*it)->SetInlet(Temp);
					Temp = (*it)->GetOutlet();//Edit Original Outlet
					Temp.x += dx;
					Temp.y += dy;
					(*it)->SetOutlet(Temp);
					if ((*it)->GetStatementType() == 3) //It is a Conditional Statement
					{
					Temp = ((Conditional*)(*it))->GetOutlet();//Edit Original Outlet
					Temp.x += dx;
					Temp.y += dy;
					((Conditional*)(*it))->SetOutletLeft(Temp);
					}
					*/
					(*it)->UpdatePoints();
				}
			}
			else
			{
				if (Top)
				{
					NewLeftCorner.y = UI.TlBrWdth + 11 + 30;
				}
				if (Bottom)
				{
					if (dynamic_cast<Conditional*>((*it)))
						NewLeftCorner.y = (UI.BGHeight - UI.StBrWdth) - 141 - 10;
					else
						NewLeftCorner.y = (UI.BGHeight - UI.StBrWdth) - 100 - 10;
				}
				if (Left)
				{
					NewLeftCorner.x = 60;
				}
				if (Right)
				{
					NewLeftCorner.x = UI.BGWidth - 180 - 50;
				}
				(*it)->SetLeftCorner(NewLeftCorner);
				(*it)->UpdatePoints();
			}
		}
		pManager->UpdateInterface();
		pOut->PrintMessage("Moving");
		pWind->UpdateBuffer();
		Sleep(10);
	}
	pWind->SetBuffering(false);


}
