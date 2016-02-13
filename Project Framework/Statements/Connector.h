#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"
#include "Statement.h"
#include <vector>
class ApplicationManager;
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	Point Intermediate1;  //The first broken point of the connector
	Point Intermediate2;
	Point Intermediate3;
	Point Intermediate4;
	bool AllIntermediateUsed;
	bool Selected;
	int CopiedOrCut;
	int BranchType; //0--> Normal  1--->YES Branch  2--->NO Branch

	vector<Point> ConnPoints;
	
public:
	Connector();
	Connector(Statement* Src, Statement* Dst, int BT);
	void UpdateIntermediate();
	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();
	vector<Point> GetConnPoints() const;
	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	int GetBranchType();

	void Draw(Output* pOut);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &InFile, ApplicationManager *pManager);
	//virtual void Edit();
	virtual void Edit(ApplicationManager* pManager);
	/*virtual void ZoomInOut(int f,int c);*/
	bool LineInclinasion(Point P1, Point P2);
	void SetCopiedOrCut(int C);
	void SetSelected(bool s);
	bool IsSelected();
};

#endif