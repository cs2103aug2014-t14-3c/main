#include "stdafx.h"
#include "CmdGoToBaseScreen.h"


CmdGoToBaseScreen::CmdGoToBaseScreen(OutputControl::CurrentScreenType currentBaseScreen){
	switch (currentBaseScreen) {
		case OutputControl::CurrentScreenType::HOME_SCREEN: {
				baseScreenCmd = new CmdHome();
				break;
															}
		case OutputControl::CurrentScreenType::TO_DO_LIST_VIEW: {
				baseScreenCmd = new CmdGoToListView();
				break;
								  }
	//case CALENDAR_VIEW: {
			
	//						}
		default:{
				baseScreenCmd = new CmdHome();
				break;
				}
	}
}
	
CmdGoToBaseScreen::~CmdGoToBaseScreen(void){
	delete baseScreenCmd;
}
	
vector<string> CmdGoToBaseScreen::execute(){
	return baseScreenCmd->execute();

}