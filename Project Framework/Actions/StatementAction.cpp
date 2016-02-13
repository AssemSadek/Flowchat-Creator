#include "StatementAction.h"
#include "..\ApplicationManager.h"

StatementAction::StatementAction(ApplicationManager *pAppManager) : Action(pAppManager)
{}
//Validates the drawing point for all statements
bool StatementAction::ValidateDrawingPoint()
{
	if (pManager->IsOverlapping(this, Position) || pManager->IsOutOfBounds(this,Position))
		return false;

	return true;
}