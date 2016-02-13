#ifndef ZoomIn_H
#define ZoomIn_H

#include "Action.h"
#include "..\Statements\SmplAssign.h"

class ZoomIn : public Action
{
private:
	Point Position;
public:
	ZoomIn(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	virtual void Execute() ;
	
};

#endif