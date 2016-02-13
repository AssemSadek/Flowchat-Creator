#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"

#include "MemoryStack\MemoryStack.h"

#include "Statements\Statement.h"
#include "Statements\SmplAssign.h"
#include "Statements\VariableAssign.h"
#include "Statements\StartEnd.h"
#include "Statements\Conditional.h"
#include "Statements\ReadWrite.h"
#include "Statements\Connector.h"

#include "Actions\AddReadWrite.h"
#include "Actions\AddConnector.h"
#include "Actions\AddSmplAssign.h"
#include "Actions\AddVariableAssign.h"
#include "Actions\AddConditional.h"
#include "Actions\AddConnector.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Paste.h"
#include "Actions\Save.h"
#include "Actions\Load.h"
#include "Actions\Comment.h"
#include "Actions\ZoomIn.h"

#include "Actions\Switch.h"

#include "Actions\Validate.h"
#include "Actions\Run.h"
#include "Actions\GenerateCode.h"

#include "GUI\Input.h"
#include "GUI\Output.h"

#include <fstream>
#include <sstream>


#include <list>
#include <map>
#include <vector>

class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	MemoryStack MemStack;
	list<Statement*> StatList;	//List of all statements (Array of pointers)
	list<Connector*> ConnList;	//List of all connectors (Array of pointers)
	list<Statement*> SelectedStatements;
	Statement *pSelectedStat; //a pointer to the last selected statement
	list<Connector*> SelectedConnectors;
	list<Statement*> CopiedOrCutStatements;  //List of Copied or Cut Statements

	//Sherif
	map<Statement*, int> SimulationMap;
	list<string> generatedCode; //Container that contains the final code

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	MemoryStack& GetMemoryStack();

	int GetStatCount();
	list<Statement*> GetStatList();
	list<Statement*>* GetStatList_Editable(); //Return address to edit outside class
	
	int GetConnCount();
	list<Connector*>& GetConnList();
	list<Connector*>* GetConnList_Editable(); //Return address to edit outside class
	list<Connector*> GetSelectedConnectors() const;



	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction(Point &P) const;
	void ExecuteAction(ActionType ActType, Point P) ; //Creates an action and executes it
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	void DeleteStatement(Statement *pStat);
	Statement* GetStatement(Point P, int &Type);	//search for a statement where point P belongs

	//void AddConnector(Connector* pConn); //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) ;	//search for a Connector where point P belongs


	list<Statement*> GetSelectedStatements() const;	//Returns the selected Statement
	list<Statement*>* GetSelectedStatements_Editable();
	void EmptySelectedStatements();
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	void UpdateSelectedStatements(Statement *S);
	void UpdateSelectedConnectors(Connector *C);
	void UpdateCopiedOrCutStatements(int CopiedOrCut); //Update the list of copied or cut statements
	list<Statement*> GetCopiedOrCutStatements();  //Returns the list of CopiedOrCutStatements


	int GetCorners(Statement *S, Point &LeftCornerUp, Point &LeftCornerDown, Point &RightCornerUp, Point &RightCornerDown);
	void GetCorners(Point P, int Type, Point &LeftCornerUp, Point &LeftCornerDown, Point &RightCornerUp, Point &RightCornerDown);
	bool PointIncludedInCorners(Point P, Point LEFTUP, Point LEFTDOWN, Point RIGHTUP, Point RIGHTDOWN);
	bool IsOverlapping(Statement *S);
	bool IsOverlapping(StatementAction *SA, Point P);
	bool IsOutOfBounds(Statement *S, bool &Top, bool &Bottom, bool &Left, bool &Right);
	bool IsOutOfBounds(StatementAction *SA, Point P);

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface();	//Redraws all the drawing window
	void SaveALL(ofstream &OutFile);
	void LoadALL(ifstream &InFile);

	//Assem
	void AddConnector1(Connector* pConn); //Adds a new Connector to the Flowchart
	void DeleteConnector(Connector* pConn);
	//Sherif
	list<string> getGeneratedCode() { return generatedCode; }
	map<Statement*, int> GetSimulationMap() { return SimulationMap; }
	void SetSimulationMap(Statement* s, int i)	{ SimulationMap[s] = i; }
	void genCode(string s); //Adds a line to the code
	void genCode(list<string> s); //Adds many lines to the code
	//

	//7amada
	void RemoveStatementConnectors(Statement *Stat);
	void RemoveStatementFromStatListWithoutDeleting(Statement *Stat);
	void DeleteCutStatements();
};

#endif