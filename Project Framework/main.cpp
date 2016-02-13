#include "ApplicationManager.h"


int main()
{
	ActionType ActType;
	Point PointClicked;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	do
	{		
		//Step I - Read user input (action)
		ActType = AppManager.GetUserAction(PointClicked);

		//Steps II & III - Create & Exexute the action
		AppManager.ExecuteAction(ActType, PointClicked);

		//Step IV - Update the interface
		AppManager.UpdateInterface();

	}while(ActType != EXIT);
	return 0;
}