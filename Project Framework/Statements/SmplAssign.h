#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"

class ApplicationManager;

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class SmplAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	string RHSString;	//Right Handside (Value)
	double RHSDouble;
	bool RHSType;
	virtual void UpdateStatementText();
	
public:
	SmplAssign(Point Centre, string LeftHS = "", string RHSStr = "", double RHSDbl = 0, bool RHSTYP = true);
	
	void setLHS(const string &L);
	void setRHS(double R);
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