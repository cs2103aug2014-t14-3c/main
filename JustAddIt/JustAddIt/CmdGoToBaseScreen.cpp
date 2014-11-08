//@author A0110770U
#include "stdafx.h"
#include "CmdGoToBaseScreen.h"

//Depending on the input base screen, a different screen
//will be constructed and stored.
CmdGoToBaseScreen::CmdGoToBaseScreen(OutputControl::CurrentScreenType currentBaseScreen){
	switch (currentBaseScreen) {
		case OutputControl::CurrentScreenType::HOME_SCREEN: {
				_baseScreenCmd = new CmdHome();
				break;
															}
		case OutputControl::CurrentScreenType::TO_DO_LIST_VIEW: {
				_baseScreenCmd = new CmdGoToListView();
				break;
																}
		case OutputControl::CurrentScreenType::SEARCH_RESULTS_SCREEN: {
				_baseScreenCmd = new CmdSearch(OutputControl::getCurrentKeywordSearched());
				break;
																	  }
		case OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN: {
				_baseScreenCmd = new CmdShowOverdueDeadlines;
				break;
																	 }
		default:{
				_baseScreenCmd = new CmdHome();
				break;
				}
	}
}
	
CmdGoToBaseScreen::~CmdGoToBaseScreen(void){
	delete _baseScreenCmd;
}
	
vector<string> CmdGoToBaseScreen::execute(){
	return _baseScreenCmd->execute();

}