#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Statement.h"

class ApplicationManager;

class Conditional : public Statement
{
private:
	string LHSString;	//Left Handside of the assignment
	double LHSDouble;
	bool LHSType;
	string RHSString;	//Right Handside of the assignmentSS
	double RHSDouble;
	bool RHSType;
	string Operator;
	Point OutletLeft;
	/*int DeltaR, DeltaL; */ //Assem
	Connector* pConnL;   //Assem
	virtual void UpdateStatementText();

public:
	Conditional(Point Centre, string LHSStr = "", double LHSDbl = 0, bool LHSTYP = true, string Oprtr = "", string RHSStr = "", double RHSDbl = 0, bool RHSTYP = true);
	void setLHS(const string &LS, const double &LD, bool LType);
	void setOperator(const string &O);
	void setRHS(const string &RS, const double &RD, bool RType);

	void GetLHS(string &LS, double &LD, bool &LType);
	void GetRHS(string &RS, double &RD, bool &RType);

	Point GetOutletLeft();
	void SetOutletLeft(Point P);

	virtual int GetStatementType();

	virtual void Draw(Output* pOut) const;
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	//virtual void Edit();
	/*void SetDeltaR(int x);
	void SetDeltaL(int x);
	int GetDeltaR();
	int GetDeltaL();*/
	void SetpConnL(Connector* p);
	Connector*& GetpConnL();

	virtual void UpdatePoints();
	virtual void Edit(ApplicationManager* pManager);
	virtual int Run(ApplicationManager *pManager, Statement *&NextStat);
};

#endif