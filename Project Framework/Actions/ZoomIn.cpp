#include "ZoomIn.h"

#include <windows.h>
#include <stdio.h>

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;
ZoomIn::ZoomIn(ApplicationManager *pAppManager):Action(pAppManager)
{}
void ZoomIn::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Zoom In: Click at the point where you want to zoom in.");

	pIn->GetPointClicked(Position);
	
	pOut->ClearStatusBar();
}
void ZoomIn::Execute()
{
	ReadActionParameters();
	int dx = Position.x, dy = Position.y;
	int xx = 200;
	int yy = xx;
	if (dx-xx < 0)
		dx = xx;
	if(dy-yy < 50)
		dy = 50+yy;
	if (dx+xx > 881)
		dx = 881-xx;
	if (dy+yy > 535)
		dy = 535-yy;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pIn->TakeScreenShot(dx-xx, dy-yy,dx+xx, dy+yy);
	pIn->GetPointClicked(Position);
	pOut->CreateBackground();

}