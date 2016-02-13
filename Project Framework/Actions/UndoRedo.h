#ifndef Undo_Redo_H
#define Undo_Redo_H
#include <fstream>
#include "..\ApplicationManager.h"

class UndoRedo : public Action
{
	bool Mode; //Mode: (True:Undo), (False,Redo)
	static int MaxCounter; //Represents number of times we can undo or redo
	static int HistoryCounter; //Represents number of times we can undo or redo
	static int CurrentStep;
public:
	UndoRedo(ApplicationManager *pManager, bool M);
	static void UnReSAVE(ApplicationManager *pAppManager);
	static void UnReTMPDelete();
	virtual void Execute();
};

#endif