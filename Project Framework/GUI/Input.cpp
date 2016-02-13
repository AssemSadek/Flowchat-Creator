#include "Input.h"
#include "Output.h"
#include <string.h>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include "../ApplicationManager.h"

using namespace std;

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Sherif//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void Input::GetMouseLocation(Point &P)
{
	pWind->GetMouseCoord(P.x, P.y);
}
void Input::GetCoords(Input *pIn, Output *pOut) //**********I made this so I can easily know which pixels I'm targeting in my functions**********
{
	int iX, iY;
	Point P;
	while (pIn->pWind->GetMouseClick(iX, iY) == NO_CLICK)
	{
		pIn->GetMouseLocation(P);
		pOut->ClearDrawArea();
		char s[50];
		_itoa_s(P.x, s, 10);
		pOut->PrintMessage(s);
		_itoa_s(P.y, s, 10);
		//pOut->PrintMessage(s);
		//Sleep(20);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
string Input::GetString(Output* pO, bool &Mixed, string Str) const
{
	char Key;
	int PointCounter = 0;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
		{
			Mixed = false;
			return Str;
		}
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
			{
				Str.erase(Str.size() - 1, 1);
				if (Str.size() == 0)
				{
					pO->ClearStatusBar();
					return "";
				}
			}
		}
		else if ((Key >= '0'&&Key <= '9')&&Str.size()==0)
		{
			//Do nothing
		}
		else if ((Key >= '0'&&Key <= '9') || (Key >= 'a'&&Key <= 'z') || (Key >= 'A'&&Key <= 'Z') || (Key=='_'))
		{
			if (Key != 8)
				Str += Key;
		}
		pO->PrintMessage(Str);
	}
}
string Input::GetString(Output* pO) const
{
	string Str = "";
	char Key;
	int PointCounter = 0;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Str;
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
				Str.erase(Str.size() - 1, 1);
		}
		else if ((Key >= '0'&&Key <= '9') && Str.size() == 0)
		{
			//Do nothing
		}
		else if ((Key >= '0'&&Key <= '9') || (Key >= 'a'&&Key <= 'z') || (Key >= 'A'&&Key <= 'Z') || (Key == '_'))
		{
			if (Key != 8)
				Str += Key;
		}
		pO->PrintMessage(Str);
	}
}

string Input::GetNormalString(Output *pO) const
{
	string Str = "";
	char Key;
	int PointCounter = 0;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Str;
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
				Str.erase(Str.size() - 1, 1);
		}
		else if ((Key >= '0'&&Key <= '9') || (Key == '.') || (Key >= 'a'&&Key <= 'z') || (Key >= 'A'&&Key <= 'Z') || (Key == '_') || (Key == '(') || (Key == ')') || (Key == ' ') || (Key == '+') || (Key == '-') || (Key == '*') || (Key == '/'))
		{
			if (Key != 8)
				Str += Key;
		}
		pO->PrintMessage(Str);
	}
}

bool PadAndValidateExpression(string &S)
{
	int Brackets = 0;
	return true;

}

string Input::GetOperator(Output *pO)
{
	string Str;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
		{
			if (Str.size() == 1)
			{
				if (Str[0] == '=' || Str[0] == '!')
					pO->PrintMessage(Str + " Please continue typing the operator");
				else
					return Str;
			}
			else if (Str.size() == 0)
				pO->PrintMessage("Please type the operator");
			else
				return Str;
		}
		else if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
				Str.erase(Str.size() - 1, 1);
		}
		else if (Str.size() == 0)
		{
			if (Key == '>' || Key == '<' || Key == '!' || Key == '=')
			{
				Str += Key;
			}
		}
		else if (Str.size() == 1)
		{
			if (Key == '=')
			{
				Str += Key;
			}
		}
		if (Key != 13)
			pO->PrintMessage(Str);
	}
}

void Input::GetMixed(Output *pO,bool &Type, string &S, double &D)
{
	S = "";
	D = 0;
	char Key;
	bool MixedResponse = true; // If True shows the function it is Mixed
	while (MixedResponse) // If MixedResponse true means restart input else Input is done
	{
		string Str;
		pWind->WaitKeyPress(Key);
		Str += Key;
		if ((Key >= '0'&&Key <= '9') || (Key == '-')) // Double
		{
			pO->PrintMessage(Str);
			Type = false;
			D = this->GetValue(pO, MixedResponse, Str);
			S = "NULL";
		}
		else if ((Key >= 'a'&&Key <= 'z') || (Key >= 'A'&&Key <= 'Z') || (Key == '_')) // Variable Name
		{
			pO->PrintMessage(Str);
			Type = true;
			S = this->GetString(pO, MixedResponse, Str);
			D = 0;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
double Input::GetValue(Output* pO, bool &Mixed, string Str) const
{
	char Key;
	int PointCounter = 0;
	if (Str[0] == '.')
		PointCounter++;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return 0;	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
		{
			Mixed = false;
			return atof(Str.c_str());
		}
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
			{
				if (Str[Str.size() - 1] == '.')
					PointCounter--;
				Str.erase(Str.size() - 1, 1);
				if (Str.size() == 0)
				{
					pO->ClearStatusBar();
					return 0;
				}
			}
		}
		else if ((Key >= '0'&&Key <= '9') || (Key == '.') || (Key == '-'))
		{
			if (Key == '-'&&Str.size() == 0)
				Str += Key;
			else if (Key == '.'&&PointCounter == 0)
			{
				PointCounter++;
				Str += Key;
			}
			else if (Key >= '0'&&Key <= '9')
				Str += Key;
		}
		pO->PrintMessage(Str);
	}
}
double Input::GetValue(Output* pO) const
{
	string Str = "";
	char Key;
	int PointCounter = 0;
	if (Str[0] == '.')
		PointCounter++;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return 0;	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return atof(Str.c_str());
		if (Key == 8)	//BackSpace is pressed
		{
			if (Str.size() != 0)
			{
				if (Str[Str.size() - 1] == '.')
					PointCounter--;
				Str.erase(Str.size() - 1, 1);
			}
		}
		else if ((Key >= '0'&&Key <= '9') || (Key == '.') || (Key == '-'))
		{
			if (Key == '-'&&Str.size() == 0)
				Str += Key;
			else if (Key == '.'&&PointCounter == 0)
			{
				PointCounter++;
				Str += Key;
			}
			else if (Key >= '0'&&Key <= '9')
				Str += Key;
		}
		pO->PrintMessage(Str);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Sherif//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;
int i = 0;
ActionType Input::GetUserAction(Point &P) const
{
	//This function reads the position where the user clicks to determine the desired action
	int x, y;
	//Hamada - Move
	//Get Mouse Button States
	pWind->FlushMouseQueue();
	buttonstate LB = pWind->GetButtonState(LEFT_BUTTON, x, y);
	buttonstate RB = pWind->GetButtonState(RIGHT_BUTTON, x, y);
	while (LB == NO_CLICK && RB == NO_CLICK)
	{
		LB = pWind->GetButtonState(LEFT_BUTTON, x, y);
		RB = pWind->GetButtonState(RIGHT_BUTTON, x, y);
	}
	//Right Click only in Drawing Area
	if (RB == BUTTON_DOWN && LB == BUTTON_UP && y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
	{
		P.x = x;
		P.y = y;
		return MOVE;
	}

	clicktype ct = pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	//Left Click anywhere or Right Click on toolbar/statusbar
	
	while (LB == BUTTON_DOWN) //Wait for completed click
	{
		LB = pWind->GetButtonState(LEFT_BUTTON, x, y);
	}
	while (RB == BUTTON_DOWN) //Wait for completed click
	{
		RB = pWind->GetButtonState(RIGHT_BUTTON, x, y);
	}
	P.x = x;
	P.y = y;
	//[1] If user clicks on the Toolbar
	if (y >= 0 && y < UI.TlBrWdth)
	{
		//Check which Menu item was clicked
		//This assumes that menu items are lined up horizontally
		int ClickedItem = (x / UI.MnItWdth);

		if (UI.AppMode == DESIGN)	//application is in design mode
		{
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_BEGIN_END: return ADD_BEGIN_END; //**********Adding a begin/end chart**********
				break;
			case ITM_SMPL_ASSIGN: return ADD_SMPL_ASSIGN; //**********Assigns a state**********
				break;
			case ITM_VAR_ASSIGN: return ADD_VAR_ASSIGN;  //**********Assigns a variable**********
				break;
			case ITM_CONDITIONAL: return ADD_CONDITIONAL; //**********Adding a conditional chart**********
				break;
			case ITM_INPUT_OUTPUT: return ADD_IN_OUT; //**********Adding an input/output chart**********
				break;
			case ITM_CONNECT: return ADD_CONNECTOR; //**********Adding/Editing a connection between charts**********
				break;
			case ITM_EDIT: return EDIT_STAT; //**********Edit Statement**********
				break;
			case ITM_COMMENT: return COMMENT; //**********Edit Statement**********
				break;
			case ITM_DEL: return DEL; //**********Delete a chart/statement/connection**********
				break;
			case ITM_SELECT: return SELECT; //**********Select a figure**********
				break;
			case ITM_MOVE: return ZOOM;
				break;
			case ITM_COPY: return COPY; //**********Copy anything to clipboard**********
				break;
			case ITM_CUT: return CUT; //**********Copy anything to clipboard**********
				break;
			case ITM_PASTE: return PASTE; //**********Paste from clipboard**********
				break;
			case ITM_UNDO: return UNDO; //**********Undo last action**********
				break;
			case ITM_REDO: return REDO; //**********Undo last action**********
				break;
			case ITM_SAVE: return SAVE; //**********Save progress**********
				break;
			case ITM_LOAD: return LOAD; //**********Load project**********
				break;
			case ITM_SWITCHSIM: return SIM_MODE; //**********Switch to Simulation Mide**********
				break;
			case ITM_EXITDSN: return EXIT; //**********Exit from project**********
				break;
			default: return DSN_TOOL; //**********Empty click**********
			}
		}
		else	//Application is in Simulation mode
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////Hamada//////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////
			switch (ClickedItem)
			{
			case ITM_VALIDATE: return VALIDATE; //**********Undo last action**********
				break;
			case ITM_RUN: return RUN; //**********Undo last action**********
				break;
			case ITM_STEPS: return STEPS; //**********Save progress**********
				break;
			case ITM_GENCODE: return GENCODE; //**********Load project**********
				break;
			case ITM_SWITCHDSN: return DSN_MODE; //**********Load project**********
				break;
			case ITM_EXITSIM: return EXIT; //**********Exit from project**********
				break;
			default: return SIM_TOOL; //**********Empty click**********
			}
			//////////////////////////////////////////////////////////////////////////////////////////
		}
	}
	//[2] User clicks on the drawing area
	else if (y >= UI.TlBrWdth && y < UI.height - UI.StBrWdth)
	{
		return DRAWING_AREA;	//user want to select/unselect a statement in the flowchart
	}

	//[3] User clicks on the status bar
	return STATUS;
}
//////////////////////////////////////////////////////////////////////////////////////////

//Screenshots
void Input::TakeScreenShot(int ix, int iy, int ex, int ey)
{
	image testImage("images//Zoom.jpg", JPEG);
	pWind->StoreImage(testImage, ix, iy, ex, ey);
	pWind->DrawImage(testImage, 0, 50, 1366, 595);
}

Input::~Input()
{
}


//Hamada
//Complex Expression Evaluation
void Input::Pad(string &S)
{
	stringstream T;
	for (unsigned int i = 0; i<S.size(); i++)
	{
		if ((S[i] >= '0'&&S[i] <= '9') || (S[i] >= 'a'&&S[i] <= 'z') || (S[i] >= 'A'&&S[i] <= 'Z') || S[i] == '.' || S[i] == '_')
		{
			T << S[i];
		}
		else
			T << " " << S[i] << " ";
	}
	S = T.str();
	string TempOld = "", TempNew;
	stringstream F;
	while (T >> TempNew)
	{
		if (TempNew != "-")
			F << TempNew << " ";
		else
		{
			if (TempOld == "+" || TempOld == "-" || TempOld == "*" || TempOld == "/" || TempOld == "(")
				F << TempNew;
			else
				F << TempNew << " ";
		}
		TempOld = TempNew;
	}
	S = F.str();
}

int Input::ShuntingYardRPN(string &S, string &RPN) //Converts to reverse Polish Notation
{
	Pad(S);
	stringstream T; T << S;
	string Temp;
	queue<string> OutputQ;
	stack<string> Operators;
	while (T >> Temp)
	{
		if (Temp == "+" || Temp == "-" || Temp == "*" || Temp == "/")
		{
			if (Temp == "+" || Temp == "-") //Lowest Precedence
			{
				while (Operators.size() != 0 && (((Operators.top()) == "*") || ((Operators.top()) == "/") || ((Operators.top()) == "+") || ((Operators.top()) == "-")))
				{
					string OPRTR = (Operators.top());
					OutputQ.push(OPRTR);
					Operators.pop();
				}
				Operators.push(Temp);
			}
			else
			{
				while (Operators.size() != 0 && (((Operators.top()) == "*") || ((Operators.top()) == "/")))
				{
					string OPRTR = (Operators.top());
					OutputQ.push(OPRTR);
					Operators.pop();
				}
				Operators.push(Temp);
			}
		}
		else if (Temp == "(")
			Operators.push(Temp);
		else if (Temp == ")")
		{
			while (Operators.size() != 0 && Operators.top() != "(")
			{
				string OPRTR = (Operators.top());
				OutputQ.push(OPRTR);
				Operators.pop();
			}
			if (Operators.top() != "(")
			{
				//Error mismatched Parantheses
				//Return Error Code : -1
				return -1;
			}
			else
				Operators.pop();
		}
		else
			OutputQ.push(Temp);
	}
	while (Operators.size() != 0)
	{
		if (Operators.top() == "(" || Operators.top() == ")")
		{
			//Error mismatched Parantheses
			//Return Error Code : -1
			return -1;
		}
		string OPRTR = (Operators.top());
		OutputQ.push(OPRTR);
		Operators.pop();
	}

	RPN = "";
	while (OutputQ.size() != 0)
	{
		RPN += OutputQ.front();
		RPN += " ";
		OutputQ.pop();
	}


	//Done Correctly
	return 1;
}

double Input::EvaluateRPN(string RPN)
{
	stringstream T;
	T << RPN;
	string Temp;
	stack<string> Values;
	while (T >> Temp)
	{
		if (Temp == "+" || Temp == "-" || Temp == "*" || Temp == "/")
		{
			double Y = atof(Values.top().c_str());
			Values.pop();
			double X = atof(Values.top().c_str());
			Values.pop();
			string OPRTR = Temp;
			if (OPRTR == "+")
			{
				stringstream V;
				V << (X + Y);
				Values.push(V.str());
			}
			else if (OPRTR == "-")
			{
				stringstream V;
				V << (X - Y);
				Values.push(V.str());
			}
			else if (OPRTR == "*")
			{
				stringstream V;
				V << (X * Y);
				Values.push(V.str());
			}
			else if (OPRTR == "/")
			{
				stringstream V;
				V << (X / Y);
				Values.push(V.str());
			}
		}
		else
			Values.push(Temp);
	}
	return atof(Values.top().c_str());
}

bool Input::IsNumber(string S)
{
	int P = 0;
	if (!((S[0] >= '0' && S[0] <= '9') || S[0] == '.' || S[0] == '-'))
		return false;
	if (S[0] == '.')
		P++;
	for (unsigned int i = 1; i < S.size(); i++)
	{
		if (S[i] == '.')
			P++;
		else if (!(S[i] >= '0' && S[i] <= '9'))
			return false;

		if (P>1)
			return false;
	}
	return true;
}

bool Input::IsMathOperator(string S)
{
	if (S == "+" || S == "-" || S == "*" || S == "/")
		return true;
	return false;
}

int Input::ValidateExpression(string S, ApplicationManager *pManager)
{
	stringstream T;
	T << S;
	string Temp;
	int brackets = 0;
	string TempOld = "";
	while (T >> Temp)
	{
		if (!IsMathOperator(Temp))
		{
			if ((Temp[0] >= '0' && Temp[0] <= '9') || Temp[0] == '-' || Temp[0] == '.') //Number
			{
				if (!IsNumber(Temp)) //Check Number Validity
					return -1; //Error Code: Invalid Number
			}
			else if ((Temp[0] >= 'a' && Temp[0] <= 'z') || (Temp[0] >= 'A' && Temp[0] <= 'Z') || Temp[0] == '_') //Variable
			{
				if (!pManager->GetMemoryStack().Contains(Temp))
					return -5; //Error Code: Variable not available in the Memory Stack
			}
			else if (Temp == "(")
				brackets++;
			else if (Temp == ")")
			{
				if (IsMathOperator(TempOld) || TempOld == "(")
					return -4; //Error Code: Invalid Operator Cascading
				brackets--;
			}
			else
				return -2; //Invalid Term
		}
		else //Mathematical Operator
		{
			if (IsMathOperator(TempOld) || TempOld == "(")
				return -4; //Error Code: Invalid Operator Cascading
		}
		TempOld = Temp;
		if (brackets < 0)
			return -3; //Error Code: Error in parantheses
	}
	if (brackets != 0)
		return -3; //Error Code: Number of parantheses wrong
	return 1;
}

void Input::ConvertVariableToValue(string &RPN, ApplicationManager *pManager)
{
	stringstream T,F;
	string Temp;
	T << RPN;
	while (T >> Temp)
	{
		if (IsMathOperator(Temp) || IsNumber(Temp))
			F << Temp << " ";
		else
			F << pManager->GetMemoryStack()[Temp] << " ";
	}
	RPN = "";
	while (F >> Temp)
	{
		RPN += Temp;
		RPN += " ";
	}

}