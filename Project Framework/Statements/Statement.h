#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "Connector.h"
//class Output;
#include "..\GUI\Output.h"
//
#include <sstream>
#include <fstream>
#include <list>

class ApplicationManager;
class Connector;

//Base class for all Statements
class Statement
{
protected:
	static int IDCounter;			//Each Statement has an ID
	int ID;
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	bool Selected;	//true if the statement is selected on the folwchart

	int CopiedOrCut; //1 if Copied, 2 if Cut, 0 if none

	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement
	
	//Sherif
	list<string> StatCode;
	//Connector *pConnL;  //Needed here for conditional
	///////

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement(Right in Conditional)
	Point LeftCorner;	//left corner of the statement block.
	string Comment;
	virtual void UpdateStatementText();	//is called when any part of the stat. is edited

	bool Visited;

	/// Add more parameters if needed.
public:
	Statement();
	virtual ~Statement();
	//Assem
	Point GetInlet();
	Point GetOutlet();
	//

	bool GetVisited(){ return Visited; }
	void SetVisited(bool V){ Visited = V; }

	void SetComment(string CMNT);
	///////////////////////////////
	//Sherif
//	void setStatCode(list<string> l) { copy(l.begin(), l.end(), back_inserter(StatCode)); }
	list<string> GetStatCode() { return StatCode; }
	string getText() { return Text; } //Needed for generating code

	//Hamada
	void SetInlet(Point P);
	void SetOutlet(Point P);
	virtual void UpdatePoints() = 0; //Update Inputs and Outputs
	//
	void SetSelected(bool s);
	bool IsSelected() const;
	void SetID(int i);
	virtual void Draw(Output* pOut) const = 0;	//Draw the statement
	Point GetLeftCorner();
	void SetLeftCorner(Point P);

	///////////////Mostafa//////////////
	void SetCopiedOrCut(int C);
	int GetCopiedOrCut()const;
	//////////////////////////////////////

	static int GetIDCounter();
	static void IncrementIDCounter();

	virtual int GetStatementType() = 0;
	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type


	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual void Edit(ApplicationManager* pManager) = 0;
	
	string GetComment();

	//Assem
	void SetpConn(Connector* p);
	Connector*& GetpConn();
	int GetID();
	//

	virtual int Run(ApplicationManager *pManager, Statement *&NextStat) = 0;
};

#endif