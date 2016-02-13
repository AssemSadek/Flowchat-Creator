#ifndef CUT_H
#define CUT_H
#pragma once
#include "StatementAction.h"
#include "..\ApplicationManager.h"


class Cut : public StatementAction
{
public:
	Cut(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif