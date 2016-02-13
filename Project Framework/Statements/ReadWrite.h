#pragma once
#include "Statement.h"

class ApplicationManager;

class ReadWrite : public Statement
{
	//Read: True
	//Write: False
	bool RW;
	string Var; //variable to read or to write
	bool VarOrString; //True Variable, False String
	bool GUIOrFile; //True GUI, False File
	string Text;
	string TextRunning;
	virtual void UpdateStatementText();
public:
	ReadWrite();
	ReadWrite(Point P, bool R, string MyVar, bool VOS = true,bool GOF = true, string Txt = "");

	~ReadWrite();

	virtual void Draw(Output* pOut) const;
	string GetLHS(){ return Var; }
	virtual int GetStatementType();
	bool GetRW();
	bool GetVOT();
	string GetVar();
	string GetText();

	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);

	virtual void UpdatePoints();
	virtual int Run(ApplicationManager *pManager, Statement *&NextStat);
	virtual void Edit(ApplicationManager* pManager);

	//For reading from files

	static ifstream INFILE;
	static ofstream OUTFILE;

};
