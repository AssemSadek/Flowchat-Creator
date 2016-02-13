#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class ApplicationManager;
class Output;

class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor
	void GetPointClicked(Point &P) const;//Gets coordinate where user clicks
	void GetMouseLocation(Point &P);
	void GetCoords(Input *pIn, Output *pOut);
	double GetValue(Output* pO, bool &Mixed, string Str) const;	// Reads a double value from the user 
	string GetString(Output* pO, bool &Mixed, string Str) const; //Returns a string entered by the user
	double GetValue(Output* pO) const;	// Reads a double value from the user 
	string GetString(Output* pO) const; //Returns a string entered by the user
	string GetNormalString(Output *pO) const;
	bool PadAndValidateExpression(string &S);
	void GetMixed(Output* pO, bool &Type, string &S, double &d); //Returns a string entered by the user(Can be digits or charachters)
	string GetOperator(Output *pO);
	ActionType GetUserAction(Point &P) const; //Reads the user click and maps it to an action
	//ScreenShot
	void TakeScreenShot(int ix, int iy, int ex, int ey);
	~Input();

	//Hamada
	//Complex Expression Evaluation
	void Pad(string &S);
	int ShuntingYardRPN(string &S, string &RPN);
	double EvaluateRPN(string RPN);
	bool IsNumber(string S);
	bool IsMathOperator(string S);
	int ValidateExpression(string S, ApplicationManager *pManager);
	void ConvertVariableToValue(string &RPN, ApplicationManager *pManager);
};

#endif