#include "ReadWrite.h"
#include <fstream>
#include <sstream>

#include "../ApplicationManager.h"


ifstream ReadWrite::INFILE("INPUT.txt");
ofstream ReadWrite::OUTFILE("OUTPUT.txt",ios::app);

ReadWrite::ReadWrite()
{}
ReadWrite::ReadWrite(Point P, bool R, string MyVar, bool VOS, bool GOF, string Txt)
{
	GUIOrFile = GOF;
	RW = R;
	Var = MyVar;
	VarOrString = VOS;
	TextRunning = Txt;
	UpdateStatementText();
	pConn = NULL;	//No connectors yet

	LeftCorner.x = P.x - 90;
	LeftCorner.y = P.y - 40;

	Inlet.x = P.x;
	Inlet.y = P.y - 40;

	Outlet.x = P.x;
	Outlet.y = P.y + 40;
	Comment = "";
}


ReadWrite::~ReadWrite()
{
}

void ReadWrite::Save(ofstream &OutFile)
{
	if (RW)
		OutFile << "READ \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y << "\t \"" << Var << "\" \t" << VarOrString << "\t" << GUIOrFile << "\t \" " << TextRunning << "\" " << "\t \" " << Comment << "\"" << endl;
	else
		OutFile << "WRITE \t" << ID << "\t" << LeftCorner.x << "\t" << LeftCorner.y << "\t \"" << Var << "\" \t" << VarOrString << "\t" << GUIOrFile << "\t \" " << TextRunning << "\" " << "\t \" " << Comment << " \" " << endl;
}

void ReadWrite::UpdateStatementText()
{
	if (RW)
	{
		if (Var == "")	//No left handside ==>statement have no valid text yet
			Text = "Read ";
		else
		{
			//Build the statement text: Left handside then equals then right handside
			ostringstream T;
			T << " Read " << Var;
			Text = T.str();
		}
	}
	else
	{
		if (Var == "")	//No left handside ==>statement have no valid text yet
			Text = "Write ";
		else
		{
			//Build the statement text: Left handside then equals then right handside
			ostringstream T;
			T << " Write ";
			if (VarOrString)
				T << Var;
			else
				T << TextRunning;
			Text = T.str();
		}
	}
}

int ReadWrite::GetStatementType()
{
	return 4;
}

 void ReadWrite::Draw(Output* pOut) const
 {
	 //Call Output::DrawAssign function to draw assignment statement 	
	 pOut->DrawInputOrOutput(LeftCorner, Text, Selected);
 }

 void ReadWrite::Load(ifstream &Infile)
 {
	 char x;
	 Infile >> ID >> LeftCorner.x >> LeftCorner.y;
	 Infile >> x;
	 getline(Infile, Var, '\"');
	 Infile>> VarOrString >> GUIOrFile;
	 Infile >> x;
	 getline(Infile, TextRunning, '\"');
	 Infile >> x;
	 getline(Infile, Comment, '\"');
	 UpdateStatementText();
	 this->UpdatePoints();
 }

 void ReadWrite::UpdatePoints()
 {
	 Point Centre;

	 Centre.x = LeftCorner.x + 90;
	 Centre.y = LeftCorner.y + 40;

	 Inlet.x = Centre.x;
	 Inlet.y = Centre.y - 40;

	 Outlet.x = Centre.x;
	 Outlet.y = Centre.y + 40;
 }

 int ReadWrite::Run(ApplicationManager *pManager, Statement *&NextStat)
 {
	 if (RW) //Read
	 {
		 if (!pManager->GetMemoryStack().Contains(this->Var))
		 {
			 pManager->GetMemoryStack() += {this->Var, 0}; //Add with dummy value
		 }
		 string VARString;
		 double VARDouble;
		 bool VARType;
		 if (GUIOrFile) //True read from GUI
		 {
			 pManager->GetInput()->GetMixed(pManager->GetOutput(), VARType, VARString, VARDouble);
		 }
		 else //False read from File
		 {
			 INFILE >> VARType >> VARString >> VARDouble;
		 }

		 while(VARType && !pManager->GetMemoryStack().Contains(VARString)) //String
		 {
				 pManager->GetOutput()->PrintMessage("Wrong Variable, please assign again");
				 pManager->GetInput()->GetMixed(pManager->GetOutput(), VARType, VARString, VARDouble);
		 }
		 if (VARType)
			 pManager->GetMemoryStack()[Var] = pManager->GetMemoryStack()[VARString];
		 else
			 pManager->GetMemoryStack()[Var] = VARDouble;
	 }
	 else //Write
	 {
		 if (VarOrString)
		 {
			 if (!pManager->GetMemoryStack().Contains(this->Var))
			 {
				 return -1; //Error '-1': LHS not in Memory Stack
			 }
			 ostringstream Text;
			 Text << pManager->GetMemoryStack()[Var];
			 pManager->GetOutput()->PrintMessage(Text.str());

			 OUTFILE.close();
			 OUTFILE.open("OUTPUT.txt", ios::app);
			 OUTFILE << Text.str() << " ";
			 OUTFILE.close();
		 }
		 else
		 {
			 OUTFILE.close();
			 OUTFILE.open("OUTPUT.txt",ios::app);
			 pManager->GetOutput()->PrintMessage(TextRunning);
			 OUTFILE << TextRunning << " ";
			 OUTFILE.close();
		 }
	 }
	 NextStat = pConn->getDstStat();
	 return 1;
 }

 bool ReadWrite::GetRW()
 {
	 return RW;
 }

 bool ReadWrite::GetVOT()
 {
	 return VarOrString;
 }

 string ReadWrite::GetVar()
 {
	 return Var;
 }

 string ReadWrite::GetText()
 {
	 return TextRunning;
 }

 void ReadWrite::Edit(ApplicationManager* pManager)
 {
	 Input *pIn = pManager->GetInput();
	 Output *pOut = pManager->GetOutput();
	 pOut->PrintMessage("Do you want to Read or Write \"r/w\" ?");
	 string Decision = pIn->GetString(pOut);
	 if (Decision == "r")
	 {
		 RW = true;
		 pOut->PrintMessage("Do you want to read from GUI or File\"g/f\" ?");
		 Decision = pIn->GetString(pOut);
		 if (Decision == "g")
			 GUIOrFile = true;
		 else
			 GUIOrFile = false;

		 pOut->PrintMessage("Please Enter the variable to read");
	 }
	 else
	 {
		 RW = false;
		 pOut->PrintMessage("Do you want to write Variable or Text \"v/t\" ?");
		 Decision = pIn->GetString(pOut);
		 if (Decision == "v")
		 {
			 pOut->PrintMessage("Please Enter the Variable to write");
			 VarOrString = true;
		 }
		 else
		 {
			 pOut->PrintMessage("Please Enter the Text to write");
			 VarOrString = false;
		 }
	 }
	 //pOut->PrintMessage("");
	 if (VarOrString)
		 Var = pIn->GetString(pOut);
	 else
		 TextRunning = pIn->GetNormalString(pOut);
	 pOut->PrintMessage("");
	 UpdateStatementText();

	 pOut->ClearDrawArea();
 }
