#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

//Statement Sizes
const int StartEndX = 140;
const int StartEndY = 70;
const int AssignX = 160;
const int AssignY = 80;
const int ConditionalX = 140;
const int ConditionalY = 140;
const int IOX = 180;
const int IOY = 80;


class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();
	window* CreateWind(int, int, int, int);


	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////Hamada//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	void CreateBackground(); //Draws Background Image which contains all tool bars
	void CreateDesignToolBar();	//Tool bar of the design mode
	//////////////////////////////////////////////////////////////////////////////////////////


	void CreateSimulationToolBar();//Tool bar of the simulation mode
	void CreateStatusBar();
	Input* CreateInput(); //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area

	window* GetWindow();

	// -- Statements Drawing Functions
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////Mostafa//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//void DrawAssign(Point Left, int width, int height, string Text, bool Selected=false);
	void DrawAssign(Point P, string Text, bool High);
	void DrawAssign(Point P, int width, int height, string Text, bool High);//DrawAssignment To scale
	void DrawStart(Point P, bool High);
	void DrawEnd(Point P, bool High);
	void DrawConditional(Point P, string Text, bool High);
	void DrawConditional(Point P, int width, int height, string Text, bool High);//DrawConditional to scale
	void DrawInputOrOutput(Point P, string Text, bool High);
	void DrawInputOrOutput(Point P, int width, int height, string Text, bool High);//DrawInputOrOutput to scale
	//////////////////////////////////////////////////////////////////////////////////////////
	//Assem
	void DrawConnector(Input *pIn, Point t);
	void DrawConnectorLine(Point P1, Point P2);
	void DrawConnectorLine(Point P1, Point P2, bool S);
	void PrintMessage(string msg);	//Prints a message on Status bar
	~Output();
};

#endif