#pragma once
#include "Statement.h"

class ApplicationManager;

class StartEnd : public Statement
{
	//False: Start, True: End
	bool Mode;
	//If start or end is already drawn its variable will be true
	static bool StartDrawn;
	static bool EndDrawn;
public:
	StartEnd(Point Centre);
	StartEnd::StartEnd(Point Centre, bool Type);
	~StartEnd();

	static bool CanCreate();
	virtual void Draw(Output* pOut) const;
	bool GetMode();
	static bool GetStartDrawn();
	static bool GetEndDrawn();

	virtual int GetStatementType();

	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);

	virtual void UpdatePoints();
	virtual void Edit(ApplicationManager* pManager);
	virtual int Run(ApplicationManager *pManager, Statement *&NextStat);
};

