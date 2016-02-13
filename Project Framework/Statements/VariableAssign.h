#ifndef VariableAssign_H
#define VariableAssign_H

#include "Statement.h"

class ApplicationManager;

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class VariableAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (another variable)

	virtual void UpdateStatementText();

public:
	VariableAssign(Point Centre, string LeftHS = "", string RightHS = "");

	void setLHS(const string &L);
	void setRHS(string R);
	string GetLHS(){ return LHS; }

	virtual void Draw(Output* pOut) const;
	
	virtual int GetStatementType();

	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);

	virtual void UpdatePoints();

	virtual int Run(ApplicationManager *pManager, Statement *&NextStat);
	virtual void Edit(ApplicationManager* pManager);
};

#endif