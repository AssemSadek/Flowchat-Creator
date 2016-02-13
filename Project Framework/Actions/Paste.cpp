#include "Paste.h"

Paste::Paste(ApplicationManager *pAppManager) :StatementAction(pAppManager)
{
	FlagToPaste = false;
}


void Paste::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	list<Statement*> CopiedOrCutStatements = pManager->GetCopiedOrCutStatements();
	if (CopiedOrCutStatements.size() == 0)
	{
		pOut->PrintMessage("Please, Select statement(s) then Copy before Pasting!");
	}
	else
	{
		pOut->PrintMessage("Please Click where you want to paste your statements!");
		pIn->GetPointClicked(P);
		FlagToPaste = true;
	}
}


void Paste::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	ReadActionParameters();

	if (FlagToPaste == true) //Check that the user had already chosen Copy Or Cut to execute Paste action
	{
		//Get the List of Copied or Cut Statements
		list<Statement*> CopiedOrCutStatements = pManager->GetCopiedOrCutStatements();
		
		//If they are Copied
		if (CopiedOrCutStatements.front()->GetCopiedOrCut() == 1) //Copy Action
		{
			Point LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown;
			//Get First Copied statement type to help in calculating dx & dy
			int Type = CopiedOrCutStatements.front()->GetStatementType();
			//Get 4 corners of the point based on its type;
			pManager->GetCorners(P, Type, LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown);
			int dx, dy;

			//Calculate dx and dy due to the first selectes statement
			dx = LeftCornerUp.x - CopiedOrCutStatements.front()->GetLeftCorner().x;
			dy = LeftCornerUp.y - CopiedOrCutStatements.front()->GetLeftCorner().y;

			//Add New Statements to this list
			list<Statement*> NewStatements;

			for (list<Statement*>::iterator it = CopiedOrCutStatements.begin(); it != CopiedOrCutStatements.end(); it++)
			{
				Statement* NewStatement;

				//Get Type of each statement
				Type = (*it)->GetStatementType();
				Point NewStatementPoint = (*it)->GetLeftCorner();

				//This should be the new point for the current statement after copying
				NewStatementPoint.x += dx;
				NewStatementPoint.y += dy;

				//Create New statement of the same type
				//Types:
				// 0 StartEnd
				// 1 SMPLAssignment
				// 2 VARAssignment
				// 3 Conditional
				// 4 Read Write
				switch (Type)
				{
					//No case 0 because we will never have 0 type statements (Start End)
					//"Start and End" are not copied
				case 1:
					NewStatement = new SmplAssign(*((SmplAssign*)(*it)));
					break;
				case 2:
					NewStatement = new VariableAssign(*((VariableAssign*)(*it)));
					break;
				case 3:
					NewStatement = new Conditional(*((Conditional*)(*it)));
					((Conditional*)(NewStatement))->SetpConnL(NULL);
					break;
				case 4:
					NewStatement = new ReadWrite(*((ReadWrite*)(*it)));
					break;
				}

				Statement::IncrementIDCounter();
				NewStatement->SetID(Statement::GetIDCounter());
				NewStatement->SetLeftCorner(NewStatementPoint);
				NewStatement->SetSelected(false);
				NewStatement->SetCopiedOrCut(0);
				NewStatement->UpdatePoints();
				NewStatement->SetpConn(NULL);
				//Dummy variable
				bool tt;
				//Check validity of point
				if (pManager->IsOutOfBounds(NewStatement, tt, tt, tt, tt) || pManager->IsOverlapping(NewStatement))
				{
					//Print Error Message
					pOut->PrintMessage("Unsuitable point for copying. Action terminated! Press any key to continue");
					
					//Remove all new statements
					for (list<Statement*>::iterator it2 = NewStatements.begin(); it2 != NewStatements.end(); it2++)
					{
						delete (*it2);
					}
					NewStatements.clear();

					//Wait for key press
					pIn->GetPointClicked(P);
					pOut->PrintMessage("");
					return;
				}

				//Statement position is okay, add it
				NewStatements.push_back(NewStatement);
			}

			//All statements don't overlap, add them to Statements list
			for (list<Statement*>::iterator it = NewStatements.begin(); it != NewStatements.end(); it++)
			{
				pManager->AddStatement((*it));
			}
			pManager->UpdateCopiedOrCutStatements(0);

		}
		//If they are Cut
		else if (CopiedOrCutStatements.front()->GetCopiedOrCut() == 2) //Cut Action
		{
			//Cutting Statement Only

			Point LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown;
			//Get First Copied statement type to help in calculating dx & dy
			int Type = CopiedOrCutStatements.front()->GetStatementType();
			//Get 4 corners of the point based on its type;
			pManager->GetCorners(P, Type, LeftCornerUp, LeftCornerDown, RightCornerUp, RightCornerDown);
			int dx, dy;
			dx = LeftCornerUp.x - CopiedOrCutStatements.front()->GetLeftCorner().x;
			dy = LeftCornerUp.y - CopiedOrCutStatements.front()->GetLeftCorner().y;

			//Store Old points before cutting
			list<Point> OldPoints;

			for (list<Statement*>::iterator it = CopiedOrCutStatements.begin(); it != CopiedOrCutStatements.end(); it++)
			{
				//Get Type of each statement
				Point NewStatementPoint = (*it)->GetLeftCorner();
				
				//Save Old Point
				OldPoints.push_back(NewStatementPoint);

				//Calculate New Point
				NewStatementPoint.x += dx;
				NewStatementPoint.y += dy;

				//Edit Point
				(*it)->SetLeftCorner(NewStatementPoint);

				//Dummy variable
				bool tt;
				//Check validity of new position of pasted statement
				if (pManager->IsOutOfBounds((*it), tt, tt, tt, tt) || pManager->IsOverlapping((*it)))
				{
					//Print Error Message
					pOut->PrintMessage("Unsuitable point for cutting. Action terminated! Press any key to continue");

					//Return pasted statements to their old positions
					list<Statement*>::iterator it2 = CopiedOrCutStatements.begin();
					for (list<Point>::iterator Pointit = OldPoints.begin(); Pointit != OldPoints.end(); Pointit++)
					{
						(*it2)->SetLeftCorner((*Pointit));
						it2++;
					}
					OldPoints.clear();

					//Wait for key press
					pIn->GetPointClicked(P);
					pOut->PrintMessage("");

					pOut->ClearDrawArea();
					pManager->UpdateInterface();
					return;
				}

				
				(*it)->UpdatePoints();
			}

			for (list<Statement*>::iterator it = CopiedOrCutStatements.begin(); it != CopiedOrCutStatements.end(); it++)
			{
				(*it)->SetCopiedOrCut(0);
			}
			pManager->UpdateCopiedOrCutStatements(0);
		}
		pOut->ClearDrawArea();
		pManager->UpdateInterface();
	}
}