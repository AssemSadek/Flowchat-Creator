#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1366;
	UI.height = 705;
	UI.wx = 0;
	UI.wy = 0;


	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////Hamada//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//We measured it using photoshop
	UI.BGWidth = 1352;
	UI.BGHeight = 690;
	//////////////////////////////////////////////////////////////////////////////////////////


	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StBrWdth = 60;
	UI.TlBrWdth = 50;
	UI.MnItWdth = 50;

	UI.DrawClr = BLUE;
	UI.HiClr = RED;
	UI.MsgClr = color(27, 83, 96);

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques 2015: Flow Chart Generator");


	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////Hamada//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	pWind->SetPen(RED, 3);
	CreateBackground();
	CreateDesignToolBar();
	CreateStatusBar();
	//////////////////////////////////////////////////////////////////////////////////////////
}

Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Hamada//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateBackground()
{
	pWind->DrawImage("images//Background.jpg", 0, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////


window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Hamada//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawImage("images//StatusBar.jpg", 0, UI.BGHeight - UI.StBrWdth);
}
//Draws the Design Menu
void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;	//Design Mode

	//fill the tool bar 
	//You can draw the tool bar icons in any way you want.
	pWind->DrawImage("images\\DesignToolBar.jpg", 0, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////


void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	///TODO: add code to create the simulation tool bar
	pWind->DrawImage("images\\SimulationToolBar.jpg", 0, 0);

}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Hamada//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Draw Empty Status Bar
	CreateStatusBar();
}
void Output::ClearDrawArea()
{
	pWind->DrawImage("images//DrawingArea.jpg", 0, 50);
	this->CreateDesignToolBar();
}

window* Output::GetWindow()
{
	return this->pWind;
}

void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar	

	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(30, PLAIN, BY_NAME, "Impact");
	pWind->DrawString(10, UI.BGHeight - (int)(UI.StBrWdth / 1.5) + 2, msg);
}
//////////////////////////////////////////////////////////////////////////////////////////


//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//


//Draw assignment statement and write the "Text" on it
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Mostafa//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawAssign(Point P, string Text, bool High)
{
	if (High)
		pWind->DrawImage("images\\AssignmentHigh.jpg", P.x, P.y);
	else
		pWind->DrawImage("images\\Assignment.jpg", P.x, P.y);
	pWind->DrawString(P.x + 10, P.y + 25, Text);
}

void Output::DrawAssign(Point P, int width, int height, string Text, bool High)//DrawAssignment To scale
{
	if (High)
		pWind->DrawImage("images\\AssignmentHigh.jpg", P.x, P.y, width, height);
	else
		pWind->DrawImage("images\\Assignment.jpg", P.x, P.y, width, height);
	pWind->DrawString(P.x - 70, P.y - 20, Text);
}

void Output::DrawStart(Point P, bool High)
{
	if (High)
		pWind->DrawImage("images\\StartHigh.jpg", P.x, P.y);
	else
		pWind->DrawImage("images\\Start.jpg", P.x, P.y);
}

void Output::DrawEnd(Point P, bool High)
{
	if (High)
		pWind->DrawImage("images\\EndHigh.jpg", P.x, P.y);
	else
		pWind->DrawImage("images\\End.jpg", P.x, P.y);

}

void Output::DrawConditional(Point P, string Text, bool High)
{
	if (High)
		pWind->DrawImage("images\\ConditionalHigh.jpg", P.x, P.y);
	else
		pWind->DrawImage("images\\Conditional.jpg", P.x, P.y);
	pWind->DrawString(P.x + 20, P.y + 60, Text);
}

void Output::DrawConditional(Point P, int width, int height, string Text, bool High)
{
	if (High)
		pWind->DrawImage("images\\ConditionalHigh.jpg", P.x - 70, P.y - 70, width, height);
	else
		pWind->DrawImage("images\\Conditional.jpg", P.x - 70, P.y - 70, width, height);
	pWind->DrawString(P.x - 40, P.y - 40, Text);
}

void Output::DrawInputOrOutput(Point P, string Text, bool High)
{
	if (High)
		pWind->DrawImage("images\\InputOutputHigh.jpg", P.x, P.y);
	else
		pWind->DrawImage("images\\InputOutput.jpg", P.x, P.y);
	pWind->DrawString(P.x + 4, P.y + 4, Text);
}

void Output::DrawInputOrOutput(Point P, int width, int height, string Text, bool High)//DrawInputOrOutput to scale
{
	if (High)
		pWind->DrawImage("images\\ConditionalHigh.jpg", P.x - 90, P.y - 40, width, height);
	else
		pWind->DrawImage("images\\Conditional.jpg", P.x - 90, P.y - 40, width, height);
	pWind->DrawString(P.x - 80, P.y - 30, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Assem
void Output::DrawConnector(Input *pIn, Point t)
{
	Point t2;
	int deltaX;
	int deltaY;
	int flag;
	char m;
	PrintMessage("Click on the starting point");
	pIn->GetPointClicked(t);
	if (t.y < 50 || t.y>UI.BGHeight - UI.StBrWdth)
	{
		ClearStatusBar();
		return;
	}
	PrintMessage("Click on the next point");
	pIn->GetPointClicked(t2);
	while (t2.y < 50 || t2.y>UI.BGHeight - UI.StBrWdth)
	{
		if (t2.y < 50)
			PrintMessage("Tool bar zone!!");
		else
			PrintMessage("Status bar zone!!");
		pIn->GetPointClicked(t2);
	}
	deltaX = t2.x - t.x;
	deltaY = t2.y - t.y;
	flag = 0;
	while (abs(deltaX) > 10 || abs(deltaY) > 10)
	{
		if (abs(deltaX) > abs(deltaY))
		{
			t2.y = t.y;
			DrawConnectorLine(t, t2);
			flag = 1;
			if (deltaX < 0)  m = 'l';
			else m = 'r';
		}
		if (abs(deltaX) <= abs(deltaY))
		{
			t2.x = t.x;
			DrawConnectorLine(t, t2);
			flag = 1;
			if (deltaY < 0)  m = 'u';
			else m = 'd';
		}
		t.x = t2.x;
		t.y = t2.y;
		PrintMessage("Click on the next point or on the last drawn point if finished");
		pIn->GetPointClicked(t2);
		while (t2.y < 50 || t2.y>UI.BGHeight - UI.StBrWdth)
		{
			if (t2.y < 50)
				PrintMessage("Tool bar zone!!");
			else
				PrintMessage("Status bar zone!!");
			pIn->GetPointClicked(t2);
		}
		deltaX = t2.x - t.x;
		deltaY = t2.y - t.y;
	}
	if (flag == 0)
	{
		PrintMessage("Nothing connected between this range !!");
		pIn->GetPointClicked(t);
	}
	else
	{
		switch (m)
		{
		case'r':
			t2.x = t.x - 6;
			t2.y = t.y + 6;
			DrawConnectorLine(t, t2);
			t2.y = t.y - 6;
			DrawConnectorLine(t, t2);
			break;
		case'l':
			t2.x = t.x + 6;
			t2.y = t.y + 6;
			DrawConnectorLine(t, t2);
			t2.y = t.y - 6;
			DrawConnectorLine(t, t2);
			break;
		case'u':
			t2.y = t.y + 6;
			t2.x = t.x + 6;
			DrawConnectorLine(t, t2);
			t2.x = t.x - 6;
			DrawConnectorLine(t, t2);
			break;
		case'd':
			t2.y = t.y - 6;
			t2.x = t.x + 6;
			DrawConnectorLine(t, t2);
			t2.x = t.x - 6;
			DrawConnectorLine(t, t2);
			break;
		}
		PrintMessage("The Statements are connected.");
		pIn->GetPointClicked(t);
	}
}
void Output::DrawConnectorLine(Point P1, Point P2)
{
	pWind->SetPen(UI.MsgClr, 3);
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
}

Output::~Output()
{
	delete pWind;
}

void Output::DrawConnectorLine(Point P1, Point P2, bool S)
{
	if (S)
	{
		pWind->SetPen(PURPLE, 3);
		pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
		pWind->SetPen(UI.MsgClr, 3);
	}
	else
	{
		pWind->SetPen(UI.MsgClr, 3);
		pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
	}
}