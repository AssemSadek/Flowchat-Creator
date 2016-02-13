#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Sherif//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
enum ActionType //The actions supported (you can add more if needed)
{
	//Design Mode Actions
	ADD_BEGIN_END,		//Add a Begin-End Statament
	ADD_SMPL_ASSIGN,	//Add Simple Assignment Statement
	ADD_VAR_ASSIGN,		//Add Variable Assignment Statement
	ADD_CONDITIONAL,	//Add a Conditional Statement
	ADD_IN_OUT,			//Add an Input-Output Statement
	ADD_CONNECTOR,		//Add a connector between two Statements
	EDIT_STAT,			//Edit a Statement
	COMMENT,			//Comment a Statement
	DEL,				//Delete a Statement
	SELECT,				//Select Statements
	MOVE,				//Move a Statement
	COPY,				//Copy a Statement
	CUT,				//Cut a Statement
	PASTE,				//Paste a Statement
	UNDO,				//Undo the last action
	REDO,				//Redo the last action
	SAVE,				//Save the whole Flow Chart to a file
	LOAD,				//Load a Flow Chart from a file
	SIM_MODE,			//Switch to simulatiom mode
	//Simulation Mode Actions
	VALIDATE,			//Validate the Flow Chart
	RUN,				//Run the Flow Chart
	STEPS,				//Run the Flow Chart Step by Step
	GENCODE,			//Generate C++ Code
	STATUS,				//A click on the status bar
	DSN_MODE,			//Switch to Design mode
	//Utility Actions
	DSN_TOOL,			//A click on an empty place in the Design Tool Bar
	SIM_TOOL,			//A click on an empty place in the Simulation Tool Bar
	DRAWING_AREA,		//A clock on an empty place in the Drawing Area
	EXIT,				//Exit the application
	ZOOM
};
//////////////////////////////////////////////////////////////////////////////////////////

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Sherif//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_BEGIN_END,		//Begin-End Statements
	ITM_SMPL_ASSIGN,	//Simple Assignment
	ITM_VAR_ASSIGN,		//Variable Assignment
	ITM_CONDITIONAL,	//Conditional Statements
	ITM_INPUT_OUTPUT,	//Input-Output Statements
	ITM_CONNECT,		//Connectors
	ITM_EDIT,			//Edit a Statement or a Connector
	ITM_COMMENT,		//Comment a Statement
	ITM_DEL,			//Delete a Statement or a Connector 
	ITM_SELECT,			//Select Statements
	ITM_MOVE,			//Move a Statement
	ITM_COPY,			//Copy a Statement
	ITM_CUT,			//Cut a Statement
	ITM_PASTE,			//Paste a Statement
	ITM_UNDO,			//Undo last action
	ITM_REDO,			//Redo last action
	ITM_SAVE,			//Save the current Flow Chart
	ITM_LOAD,			//Load a Flow Chart
	ITM_SWITCHSIM,		//Switch to Sumulation Mode
	ITM_DSN_CNT,		//no. of design menu items ==> This should be the last line in this enum
	ITM_EXITDSN = 26	//Exit the program
};
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Hamada//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,		//Validate
	ITM_RUN,			//Run
	ITM_STEPS,			//Step by step
	ITM_GENCODE,		//Generate C++ Code
	ITM_SWITCHDSN,		//Switch to Design Mode
	ITM_SIM_CNT,		//no. of simulation menu items ==> This should be the last line in this enum
	ITM_EXITSIM = 26	//Exit the program
};
//////////////////////////////////////////////////////////////////////////////////////////




#ifndef NULL
#define NULL 0
#endif

#endif