#include "GenerateCode.h"

#include <windows.h>
#include <stdio.h>

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

bool GenerateCode::IsDeclared(vector<string> V, string Var)
{
	for (unsigned int i = 0; i < V.size(); i++)
	{
		if (V[i] == Var)
			return true;
	}
	return false;
}

GenerateCode::GenerateCode(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void GenerateCode::ReadActionParameters() {}

//Old - Unused - Sherif & Mostafa
list<string> GenerateCode::getCode(Statement* s, int e)
{
	vector<string> VariableCheck; //All Declared Variables are added here
	string str;
	list<string> l;
	map<Statement*, int> m = pManager->GetSimulationMap();
	//next statement
	switch (s->GetStatementType())
	{
	case 0: //End
		return l;
		break;
	case 1: //SMPLAssignment
	case 2: //VARAssignment
		if (!IsDeclared(VariableCheck, s->getText()))
		{
			l.push_back("double " + s->getText() + ";\n");
			VariableCheck.push_back(s->getText());
		}
		else
			l.push_back(s->getText() + ";\n");
		return l;
		break;
	case 3: //Conditional
	{
				if (!s->GetStatCode().empty())
					return s->GetStatCode();
				auto d = s->GetpConn();

				Statement * after = d->getDstStat();
				if (m[after] < m[s]) //Check if statement is before the conditional statement
				{
					l.push_back("while(" + s->getText() + ")\n{\n");
					for (int i = m[after]; i < m[s]; i++) //First (True) While Loop
					{
						if ((e == 0) || (after->GetStatementType() != 3))
						{
							if (e == 0 && after->GetStatementType() == 3 || !after->GetStatCode().empty())
							{
								if (!after->GetStatCode().empty())
									return s->GetStatCode();
								auto c = getCode(after, 1);
								copy(c.begin(), c.end(), back_inserter(l));
							}
							else
							{
								auto c = getCode(after, e);
								copy(c.begin(), c.end(), back_inserter(l));
							}

						}
						after = after->GetpConn()->getDstStat();
						if (!after->GetStatCode().empty())
							return s->GetStatCode();
					}
					l.push_back("}\n");
					after = ((Conditional*)s)->GetpConnL()->getDstStat();
					if (m[after] < m[s]) //First (false) while Loop
					{
						l.push_back("while(!" + s->getText() + ")\n{\n");
						for (int i = m[after]; i < m[s]; i++)
						{
							if ((e == 0) || (after->GetStatementType() != 3))
							{
								if (e == 0 && after->GetStatementType() == 3 || !after->GetStatCode().empty())
								{
									if (!after->GetStatCode().empty())
										return s->GetStatCode();
									auto c = getCode(after, 1);
									copy(c.begin(), c.end(), back_inserter(l));
								}
								else
								{
									auto c = getCode(after, e);
									copy(c.begin(), c.end(), back_inserter(l));
								}

							}
							after = after->GetpConn()->getDstStat();
						}
						l.push_back("}\n");
					}
					else
					{

						while (after != NULL && after->GetStatementType() != 3 && after->GetStatementType() != 0) //(False) Continue without loops or if statements
						{
							if ((e == 0) || (after->GetStatementType() != 3))
							{
								if (e == 0 && after->GetStatementType() == 3 || !after->GetStatCode().empty())
								{
									if (!after->GetStatCode().empty())
										return s->GetStatCode();
									auto c = getCode(after, 1);
									copy(c.begin(), c.end(), back_inserter(l));
								}
								else
								{
									auto c = getCode(after, e);
									copy(c.begin(), c.end(), back_inserter(l));
								}

							}
							after = after->GetpConn()->getDstStat();
							if (!after->GetStatCode().empty())
								return s->GetStatCode();
						}
						if ((e == 0) || (after->GetStatementType() != 3))
						{
							auto c = getCode(after, 1);
							copy(c.begin(), c.end(), back_inserter(l));
						}
					}
				}
				else //Second True condition isn't a loop
				{
					l.push_back("if(" + s->getText() + ")\n{\n"); //(True) if statement
					while (after->GetStatementType() != 0)
					{
						if ((e == 0) || (after->GetStatementType() != 3))
						{
							if (e == 0 && after->GetStatementType() == 3 || !after->GetStatCode().empty())
							{
								if (!after->GetStatCode().empty())
									return s->GetStatCode();
								auto c = getCode(after, 1);
								copy(c.begin(), c.end(), back_inserter(l));
							}
							else
							{
								auto c = getCode(after, e);
								copy(c.begin(), c.end(), back_inserter(l));
							}

						}
						auto qw = after->GetpConn();
						after = qw->getDstStat();
						if (!after->GetStatCode().empty())
							return s->GetStatCode();
					}
					l.push_back("}\n");
					l.push_back("else\n{\n"); //(False) else statement
					after = ((Conditional*)s)->GetpConnL()->getDstStat();
					if (m[after] < m[s]) //Check if statement is before the conditional statement
					{
						l.push_back("while(!" + s->getText() + ")\n{\n"); //Second (False) While Loop
						for (int i = m[after]; i < m[s]; i++)
						{
							if ((e == 0) || (after->GetStatementType() != 3))
							{
								if (e == 0 && after->GetStatementType() == 3 || !after->GetStatCode().empty())
								{
									if (!after->GetStatCode().empty())
										return s->GetStatCode();
									auto c = getCode(after, 1);
									copy(c.begin(), c.end(), back_inserter(l));
								}
								else
								{
									auto c = getCode(after, e);
									copy(c.begin(), c.end(), back_inserter(l));
								}

							}
							if (after->GetStatementType() != 0)
								after = after->GetpConn()->getDstStat();
							if (!after->GetStatCode().empty())
								return s->GetStatCode();
						}
						l.push_back("}\n}\n");
					}
					else
					{
						while (after != NULL && after->GetStatementType() != 3 && after->GetStatementType() != 0) //Second (False) Continue as normal
						{
							if ((e == 0) || (after->GetStatementType() != 3))
							{
								if (e == 0 && after->GetStatementType() == 3 || !after->GetStatCode().empty())
								{
									if (!after->GetStatCode().empty())
										return s->GetStatCode();
									auto c = getCode(after, 1);
									copy(c.begin(), c.end(), back_inserter(l));
								}
								else
								{
									auto c = getCode(after, e);
									copy(c.begin(), c.end(), back_inserter(l));
								}

							}
							if (after->GetStatementType() != 0)
								after = after->GetpConn()->getDstStat();
							if (!after->GetStatCode().empty())
								return s->GetStatCode();
						}
						if ((e == 0) || (after->GetStatementType() != 3))
						{
							auto c = getCode(after, 1);
							copy(c.begin(), c.end(), back_inserter(l));
						}
					}
					l.push_back("}\n");
				}
				//s->setStatCode(l);
				return l;

				break;
	}
	case 4: //Read Write
		if (((ReadWrite*)s)->GetRW() == true) //Read
		{
			l.push_back("cin>>" + ((ReadWrite*)s)->GetVar() + ";\n");
		}
		else //Write
		{
			if (((ReadWrite*)s)->GetVOT())
				l.push_back("cout<<" + ((ReadWrite*)s)->GetVar() + ";\n");
			else
				l.push_back("cout<<" + ((ReadWrite*)s)->GetText() + ";\n");
		
		}
		return l;
		break;
	}
	return l; //Dummy return to eliminate warnings
}

string GenerateCode::Codegen(Statement* CS, int &E, string S)
{
	int Type = CS->GetStatementType();
	if (Type == 0)
	{
		S += "return 0;\n";
		return S;
	}
	if (Type == 1 || Type == 2)
	{
		//if (!CS->GetVisited())
		//{
			S += CS->getText();
			S += ";\n";
		//}
		CS->SetVisited(true);
		return Codegen(CS->GetpConn()->getDstStat(), E, S);
	}
	if (Type == 4)
	{
		//if (!CS->GetVisited())
		//{
			if (((ReadWrite*)(CS))->GetRW()) //Read: True
			{
				S += "cin>>";
				S += ((ReadWrite*)(CS))->GetVar();
				S += ";\n";
			}
			else //Write
			{
				S += "cout<<";
				if (((ReadWrite*)(CS))->GetVOT()) //Variable True
				{
					S += ((ReadWrite*)(CS))->GetVar();
					S += ";\n";
				}
				else
				{
					S += "\"";
					S += ((ReadWrite*)(CS))->GetText();
					S += "\";\n";
				}
			}
		//}
		CS->SetVisited(true);
		return Codegen(CS->GetpConn()->getDstStat(), E, S);
	}
	if (Type == 3) //Conditional
	{
		if (CS->GetVisited()) //If Visited then loop
		{
			E = CS->GetID();
			return S;
		}
		CS->SetVisited(true);
		string YES = "";
		string NO = "";
		int R = 0, L = 0;
		YES = Codegen(((Conditional*)(CS))->GetpConn()->getDstStat(), R, YES);
		NO = Codegen(((Conditional*)(CS))->GetpConnL()->getDstStat(), L, NO);
		if (R == CS->GetID()) //While loops from Right
		{
			E = L;
			S += "while(";
			S += CS->getText();
			S += ")\n{\n";
			S += YES;
			S += "}\n";
			S += NO;
			S += "\n";
		}
		else if (L == CS->GetID()) //Loop from Left
		{
			E = R;
			S += "while(!(";
			S += CS->getText();
			S += "))\n{\n";
			S += NO;
			S += "}\n";
			S += YES;
			S += "\n";
		}
		else //Not visited IF
		{
			if (R != 0)
				E = R;
			else
				E = L;
			S += "if(";
			S += CS->getText();
			S += ")\n{\n";
			S += YES;
			S += "}\n";
			S += "\nelse\n{\n";
			S += NO;
			S += "}\n";
		}
		//return Codegen(CS->GetpConn()->getDstStat(), E, S);
		return S;
	}

	//Dummy return to eliminate warnings
	return "";
}

void GenerateCode::Execute()
{
	/*
	int z = 0;
	auto g = pManager->GetStatList();
	for (list<Statement*>::iterator x = g.begin(); x != g.end(); x++)
	{

	pManager->SetSimulationMap(*x, z);
	z++;
	}

	pManager->genCode("void main()\n{\n");
	Statement* afterbegin = pManager->GetSimulationMap().begin()->first->GetpConn()->getDstStat();
	while (afterbegin->GetStatementType() != 3 && afterbegin->GetStatementType() != 0) //Conditional writes code till the end
	{
	pManager->genCode(getCode(afterbegin));
	afterbegin = afterbegin->GetpConn()->getDstStat();
	}
	pManager->genCode(getCode(afterbegin));
	ofstream fout("GeneratedCode.txt");
	auto f = pManager->getGeneratedCode();
	copy(f.begin(), f.end(), ostream_iterator<string>(fout));
	fout.close();
	*/

	//Hamada
	//Validate before generating the code
	Validate *ValidatingAction = new Validate(pManager);
	if (ValidatingAction->ValidateForRun() == 0)
		return;

	list<Statement*> StatList = pManager->GetStatList();
	list<Connector*> ConnList = pManager->GetConnList();
	Statement* CurrentStatement;
	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		(*it)->SetVisited(false);
		if ((*it)->GetStatementType() == 0 && ((StartEnd*)(*it))->GetMode() == false)
			CurrentStatement = (*it);
	}

	CurrentStatement->SetVisited(true);
	string Code = "#include<iostream>\nusing namespace std;\nint main()\n{\n";
	
	set<string> DeclaredVariables;

	for (list<Statement*>::iterator it = StatList.begin(); it != StatList.end(); it++)
	{
		int Type = (*it)->GetStatementType();
		

		switch (Type)
		{
		case 1:
			if (DeclaredVariables.find(((SmplAssign*)(*it))->GetLHS()) == DeclaredVariables.end())
			{
				Code += "double ";
				Code += ((SmplAssign*)(*it))->GetLHS();
				Code += ";\n";
				DeclaredVariables.insert(((SmplAssign*)(*it))->GetLHS());
			}
			break;
		case 2:
			if (DeclaredVariables.find(((VariableAssign*)(*it))->GetLHS()) == DeclaredVariables.end())
			{
				Code += "double ";
				Code += ((VariableAssign*)(*it))->GetLHS();
				Code += ";\n";
				DeclaredVariables.insert(((VariableAssign*)(*it))->GetLHS());
			}
			break;
		case 4:
			if (((ReadWrite*)(*it))->GetRW() == true)
			{
				if (DeclaredVariables.find(((ReadWrite*)(*it))->GetVar()) == DeclaredVariables.end())
				{
					Code += "double ";
					Code += ((ReadWrite*)(*it))->GetVar();
					Code += ";\n";
					DeclaredVariables.insert(((ReadWrite*)(*it))->GetVar());
				}
			}
			break;
		}
	}

	int E = -1;;
	Code = Codegen(CurrentStatement->GetpConn()->getDstStat(), E, Code);
	Code += "}";
	int BracketsCounter = 0;
	string FinalCode;
	for (unsigned int i = 0; i < Code.size(); i++)
	{
		char Temp = Code[i];
		if (Code[i] == '{')
		{
			FinalCode += '{';
			BracketsCounter++;
		}
		else if (Code[i] == '}')
		{
			FinalCode += '}';
		}
		else if (Code[i] == '\n' && FinalCode.size() > 0 && FinalCode[FinalCode.size() - 1] != '\n')
		{
			FinalCode += '\n';
			if (Code[i + 1] == '}')
				BracketsCounter--;
			for (int j = 0; j < BracketsCounter; j++)
				FinalCode += '\t';
		}
		else
			FinalCode += Code[i];
	}
	ofstream Out("GCODE.txt");
	Out << FinalCode;
	Out.close();
}
