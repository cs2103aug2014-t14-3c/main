#include "stdafx.h"
#include "Parser.h"
#define MONTHS_IN_YEAR 12
#define DEFAULT_MONTH_START "1"
#define FORMAT_24H_SIZE 4

Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}

Command* Parser::stringToCommand(string userCommand) {
	

	
	//convert into a stream and get the first word
	istringstream commandStream(userCommand);
	string userAction;
	commandStream >> userAction;
	//translate the first word into a CommandType
	CommandType commandAction = determineCommandType(userAction, OutputControl::getCurrentScreen());
	
	
	switch (commandAction) {
		case ADD: {
			//Pass remaining stream as details
			
			Item* item1 = new Item;
			string stringDetails;
			getline(commandStream, stringDetails);
			embedDetailsInItem(item1, stringDetails);

			CmdAddItem* myAdd = new CmdAddItem(item1);
			return myAdd;

			break;
		}

		case SEARCH: {
			string keyword;
			getline(commandStream, keyword);
			CmdSearch* mySearch = new CmdSearch(keyword);
			return mySearch;
			break;
		}

		case EDIT: {
			int fieldNum;
			string newFieldInfo;
			commandStream >> fieldNum;
			getline(commandStream, newFieldInfo);
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, newFieldInfo);
			return myEdit;
			break;
				   }

		//TODO:DELETE IS UNTESTED (possibly use get getItemAddr instead)
		case DELETE: {
			int itemNum;
			commandStream >> itemNum;
	
			CmdDeleteItem* myDelete = new CmdDeleteItem(OutputControl::getCurrentDisplayedItemList()+itemNum-1);
			return myDelete;
			break;
					 }

		case MARK: {
			int itemNum;
			commandStream >> itemNum;
			CmdMarkItemDone* myMark = new CmdMarkItemDone(OutputControl::getCurrentDisplayedItemList()+itemNum-1);
			return myMark;
			break;
					 }

		case UNDO : {
			CmdUndo* myUndo = new CmdUndo();
			return myUndo;
			break;
					}
		case REDO : {
			CmdRedo* myRedo = new CmdRedo();
			return myRedo;
			break;
					}
		case CANCEL : {
			CmdDeleteItem* myDelete = new CmdDeleteItem(OutputControl::getCurrentDisplayedItemList());
			return myDelete;
			break;
					}
		case VIEW_CALENDAR : {
			CmdGoToCalendarView* myCalendar = new CmdGoToCalendarView();
			return myCalendar;
			break;
					}
		case VIEW_TODOLIST : {
			CmdGoToListView* myList = new CmdGoToListView();
			return myList;
			break;
					}
		case VIEW_OVERDUE : {
			CmdShowOverdueTasks* myOverdue = new CmdShowOverdueTasks();
			return myOverdue;
			break;
					}
		case HOME : {
			CmdHome* myHome = new CmdHome();
			return myHome;
			break;
					}

	
		//TODO: INVALID CASE AND DEFAULT CASE
	}
	return NULL;
}

void Parser::embedDetailsInItem(Item* myItem, string stringDetails){

	detectTitleAndEmbed(myItem, stringDetails);

	bool isDeadline = detectDeadlineKeywordAndTrim(stringDetails);
	bool foundMonthDate = detectMonthDateAndEmbedIsOk(myItem, stringDetails, isDeadline);
	bool foundDayOfWeek = detectDayOfWeekDateAndEmbedIsOk(myItem, stringDetails, isDeadline);
	bool foundTime = detectTimeAndEmbedIsOk(myItem, stringDetails, isDeadline);	

	bool foundDate = foundMonthDate || foundDayOfWeek;

	if(foundDate && !foundTime){
		//set as all day if no time
		myItem->setStartTime(0,0);
		myItem->setEndTime(23,59);
	}
	if(!foundDate && foundTime){
		//set as today if no day
		time_t nowTime;
		tm nowTimeTM;
		time(&nowTime);
		localtime_s (&nowTimeTM, &nowTime);
		myItem->setStartDate(nowTimeTM.tm_mday, nowTimeTM.tm_mon);
		myItem->setEndDate(nowTimeTM.tm_mday, nowTimeTM.tm_mon);
	}
	//if no date or no time, it is a task
	if(isDeadline){
		myItem->setItemType("deadline");
	}
	else if(!foundDate && !foundTime){
		myItem->setStartEndDateTimeAsToday();
		myItem->setItemType("task");
	}
	else{
		myItem->setItemType("event");
	}


			
}

void Parser::detectTitleAndEmbed(Item* myItem, string &stringDetails){
	
	istringstream streamDetails(stringDetails);
	string title = "";
	string currentWord;
	string previousWord;
	string nextWord;
	//get the first word and store in title if not a keyword
	streamDetails >> previousWord;
	

	if(isKeyword(previousWord)){
		throw invalid_argument("no title was found!");
	}
	//account for one worded task
	else if(!(streamDetails >> currentWord)){
		title = previousWord;
	}
	//acccount for one worded event
	else if(isKeyword(currentWord)){
		title = previousWord;
	}
	else{

			title=previousWord;
			previousWord = currentWord;
			//get the next word;
			//account for two worded task
			if(!(streamDetails >> currentWord)){
				title += ' ' + previousWord;
			}
			else{

				//account for one worded events
				if(!isKeywordEndTime(currentWord)){
				//and loop the subsequent adding
					while((streamDetails >> nextWord) && !isKeyword(currentWord) && !isKeywordEndTime(nextWord)){
						title += ' ' + previousWord;
						previousWord = currentWord;
						currentWord = nextWord;

						/*streamDetails >> nextWord;*/

						//title += ' ' + currentWord;
						//previousWord = currentWord;
						//streamDetails >> currentWord;
					}
				//for currentWord isKeyword exit 
					if(isKeyword(currentWord) || isKeywordEndTime(nextWord)){
						title += ' ' + previousWord;
					}
					else{
						title += ' ' + previousWord + ' ' + currentWord;
					}
				}
			}
		
	}
	//cut out the title
	stringDetails.replace(stringDetails.find(title),title.length(),"");
	myItem->setTitle(title);


	//TODO:Exception if no title (first word is a keyword)
	return;
}
bool Parser::detectDeadlineKeywordAndTrim(string &stringDetails){
	size_t position;
	bool isFound = false;
	position = stringDetails.find("by");
	//if found
	if (position!=string::npos){
		stringDetails = stringDetails.substr(position);
		isFound = true;
	}
	return isFound;
}
bool Parser::detectTimeAndEmbedIsOk(Item* myItem, string stringDetails, bool isDeadline){
	istringstream streamDetails(stringDetails);
	string startTime="";
	string endTime="";
	int startHourToBeSet;
	int startMinToBeSet;
	int endHourToBeSet;
	int endMinToBeSet;
	bool startFound = false;
	bool endFound = false;
	while(streamDetails >> startTime && !isTime(startTime)){
	}
	while(streamDetails >> endTime && !isTime(endTime)){
	}
	//if start time exists
	if(isTime(startTime)){
		startHourToBeSet = convertStringToIntHour(startTime);
		startMinToBeSet = convertStringToIntMin(startTime);
		myItem->setStartTime(startHourToBeSet, startMinToBeSet);
		startFound = true;
		if(isDeadline){
			myItem->setEndTime(startHourToBeSet, startMinToBeSet);
		}
		else{
			//TODO:Assuming deadlines only have one time/date
			//start exists and end exists
			if(isTime(endTime)){
				endHourToBeSet = convertStringToIntHour(endTime);
				endMinToBeSet = convertStringToIntMin(endTime);
				myItem->setEndTime(endHourToBeSet, endMinToBeSet);
				endFound = true;
			}
			//start exists but end does not exist
			//default is an hour aft start
			else{
				endHourToBeSet = convertStringToIntHour(startTime);
				endHourToBeSet++;
				endMinToBeSet = convertStringToIntMin(startTime);
				myItem->setEndTime(endHourToBeSet, endMinToBeSet);
			}
		}
	}


	return startFound || endFound;
}
bool Parser::detectMonthDateAndEmbedIsOk(Item* myItem, string &stringDetails,  bool isDeadline){
	istringstream streamDetails(stringDetails);
	string currentWord="";
	string previousWord;
	string nextWord;
	string startMonthFound="";
	string startDateFound="";
	string startDayFound = "";
	string endMonthFound="";
	string endDateFound="";
	string endDayFound = "";
	int startDayInt;
	int startMonthInt;
	int endDayInt;
	int endMonthInt;
	bool endExists = false;
	
	streamDetails >> previousWord;
	while(streamDetails >> currentWord && !isMonth(currentWord)){
		previousWord = currentWord;
	}
	if(isMonth(currentWord)){
		//store the month name in date found
		startMonthFound = currentWord; 
		//if the previous word is a integer, it's the date
		if(isInteger(previousWord)){
			startDayFound = previousWord;
			startDateFound = startDayFound + ' ' + startMonthFound;
		}
		//if the next word is a integer, it's the date
		else if(streamDetails >> nextWord && isInteger(nextWord)){
			startDayFound = nextWord;
			startDateFound = startMonthFound + ' ' + startDayFound;
		}
		//TODO:: exception for only month found
		else{
			startDayFound = DEFAULT_MONTH_START;
			startDateFound = startMonthFound;
		}

		//cut out the date
		stringDetails.replace(stringDetails.find(startDateFound),startDateFound.length(),"");
		startDayInt = stoi(startDayFound);
		startMonthInt = convertStrToIntMonth(startMonthFound);
		
		//reset currentWord and search for second date
		currentWord="";
		while(streamDetails >> currentWord && !isMonth(currentWord)){
			previousWord = currentWord;
		}

		if(isMonth(currentWord)){
			//store the month name in date found
			endMonthFound = currentWord; 
			//if the previous word is a integer, it's the date
			if(isInteger(previousWord)){
				endDayFound = previousWord;
				endDateFound = endDayFound + ' ' + endMonthFound;
				endExists = true;
			}
			//if the next word is a integer, it's the date
			else if(streamDetails >> nextWord && isInteger(nextWord)){
				endDayFound = nextWord;
				endDateFound = endMonthFound + ' ' + endDayFound;
				endExists = true;
			}
			//TODO:: exception for only month found
			else{
			}
			//cut the date out
			stringDetails.replace(stringDetails.find(endDateFound),endDateFound.length(),"");
			endDayInt = stoi(endDayFound);
			endMonthInt = convertStrToIntMonth(endMonthFound);

		}

		if(isDeadline){
			myItem->setStartDate(startDayInt, startMonthInt); //for safety
			myItem->setEndDate(startDayInt, startMonthInt);
		}
		else{
			if(endExists){
			myItem->setStartDate(startDayInt, startMonthInt);
			myItem->setEndDate(endDayInt, endMonthInt);
			}
			else{
				myItem->setStartDate(startDayInt, startMonthInt);
				myItem->setEndDate(startDayInt, startMonthInt);
			}
		}
		return true;
	}
	else{
		return false;
	}
	//TODO: exception if first word is a month
	

}
bool Parser::detectDayOfWeekDateAndEmbedIsOk(Item* myItem, string &stringDetails,  bool isDeadline){
	
	
	string startDate="";
	string endDate="";
	int startDaysToAdd;
	int endDaysToAdd;
	bool startFound = false;
	bool endFound = false;
	bool isWordNextStart = false;
	bool isWordNextEnd = false;

	istringstream streamDetails(stringDetails);
	
	while(streamDetails >> startDate && !isDayOfWeek(startDate)){
	}
	while(streamDetails >> endDate && !isDayOfWeek(endDate)){
	}

	//if start time exists
	if(isDayOfWeek(startDate)){

		startFound = true;
		//cut the start day out
		//if "next" keyword is found
		if(stringDetails.find("next " + startDate)!=string::npos){
			isWordNextStart=true;
			stringDetails.replace(stringDetails.find("next " + startDate),startDate.length(),"");
		}
		else{
			stringDetails.replace(stringDetails.find(startDate),startDate.length(),"");
		}
		startDaysToAdd = convertDayOfWeekToIntDaysToAdd(startDate, isWordNextStart);
		myItem->addToStartDate(startDaysToAdd);
		if(isDeadline){
			myItem->addToEndDate(startDaysToAdd);
		}
		else{
			//TODO:Assuming deadlines only have one time/date
			//start exists and end exists
			if(isDayOfWeek(endDate)){
				
				endFound = true;
				//if "next" keyword is found
				if(stringDetails.find("next " + endDate)!=string::npos){
					isWordNextEnd=true;
					stringDetails.replace(stringDetails.find("next " + endDate),endDate.length(),"");
				}
				else{
					//cut the end day out
					stringDetails.replace(stringDetails.find(endDate),endDate.length(),"");
				}
				
			
				endDaysToAdd = convertDayOfWeekToIntDaysToAdd(endDate, isWordNextEnd);
				myItem->addToEndDate(endDaysToAdd);
			}
			//start exists but end does not exist
			//default end date is same as start date
			else{
				myItem->addToEndDate(startDaysToAdd);
			}
		}
	}


	return startFound || endFound;


}
bool Parser::isInteger(string query){
    unsigned int i;

    for(i = 0; i < query.length(); i++){
		if(isdigit(query[i]) == 0 || ispunct(query[i]) != 0) {
			break;
		}
	}

	if(i != query.length())
		return 0;
	else
		return 1;
}

bool Parser::isMonth(string query){
	if(convertStrToIntMonth(query)>=0)
		return true;
	else
		return false;
}
bool Parser::isTime(string query){
	//TODO: For more supported formats
	if(isdigit(query[0])>0)
		return true;
	else
		return false;
}
bool Parser::isDayOfWeek(string query){
	if(convertDayOfWeekToIntDaysToAdd(query, false)>=0)
		return true;
	else
		return false;
}
int Parser::convertStringToIntHour(string stringTime){
	
	convertStringToLowercase(stringTime);
	size_t positionFound;
	//set accountForPM to 12 if afternoon
	int accountForPM=0;

	if(isInteger(stringTime) && stringTime.length() == FORMAT_24H_SIZE){
		stringTime = stringTime.substr(0,2);
	}
	else{
		positionFound = stringTime.find("am");
		//if found, cut the am out
		if (positionFound!=string::npos){
			stringTime = stringTime.substr(0,positionFound);
		}

		positionFound = stringTime.find("pm");
		//if found, cut the pm out
		if (positionFound!=string::npos){
			stringTime = stringTime.substr(0,positionFound);
			accountForPM=12;
		}
	}
	//what remains is the digits (minutes are trimmed)
	int actualTime = stoi (stringTime) + accountForPM;
	
	return actualTime;
}
int Parser::convertStringToIntMin(string stringTime){
	
	size_t positionFound1;
	size_t positionFound2;

	if(isInteger(stringTime) && stringTime.length() == FORMAT_24H_SIZE){
		stringTime = stringTime.substr(2,4);
	}
	else{
		positionFound1 = stringTime.find(".");
		positionFound2 = stringTime.find(":");
		//if found, crop the 2 digits after that 
		if (positionFound1!=string::npos){
			stringTime = stringTime.substr(positionFound1+1,positionFound1+3);
		}
		else if (positionFound2!=string::npos){
			stringTime = stringTime.substr(positionFound2+1,positionFound2+3);
		}
		//default case: 0 minutes
		else {
			stringTime = "0";
		}
	}
	return stoi (stringTime);
}
int Parser::convertStrToIntMonth(string month){
	convertStringToLowercase(month);
	const string month3[] = {"jan", "feb", "mar", "apr", "may", "jun",
								"jul", "aug", "sep", "oct", "nov", "dec"};
	const string monthfull[] = {"january", "february", "march", "april", "may", "june",
								"july", "august", "september", "october", "november", "december"};
	int i;
	if(month.size()==3){
		for(i=0; i<MONTHS_IN_YEAR; i++){
			if(month==month3[i]){
				return i;
			}
		}
	}
	else{
		for(i=0; i<MONTHS_IN_YEAR; i++){
			if(month==monthfull[i]){
				return i;
			}
		}
	
	}
	return -1; 
	//TODO: Throw exeception for bad month
}

void Parser::convertStringToLowercase(string &myString){
	unsigned int i;
	for(i=0; i<myString.size(); i++){
		myString[i] = tolower(myString[i]);
	}
	return;
}
int Parser::convertDayOfWeekToIntDaysToAdd(string query, bool isNextWeek){
	
	const string dayOfWeek[] = {"sunday", "monday", "tuesday", "wednesday","thursday",
								"friday", "saturday"};
	convertStringToLowercase(query);
	int i;
	int daysAfterSunday=-1;
	bool dayOfWeekFound=false;
	for(i=0; i<7 && !dayOfWeekFound; i++){
			if(query==dayOfWeek[i]){
				daysAfterSunday=i;
				dayOfWeekFound = true;
			}
	}
	if(dayOfWeekFound){
		time_t nowTime;
		tm nowTimeTM;
		time(&nowTime);
		localtime_s (&nowTimeTM, &nowTime);
	
		int daysToAdd;
		daysToAdd = daysAfterSunday - nowTimeTM.tm_wday ;
		if(daysToAdd<0){
			daysToAdd += 7;
		}
		//checking for "next"
		int eventDay = nowTimeTM.tm_wday + daysToAdd;
		if(isNextWeek && eventDay<=6){
			daysToAdd += 7;
		}

		return daysToAdd;
	}
	else{
		return -1;
		//TODO: Throw exception for bad day
	}
	

}

CommandType Parser::determineCommandType(string userCommand, OutputControl::CurrentScreenType currentScreen) {
	//universal commands
	if (userCommand == "add") {
		return ADD;
	}
	if (userCommand == "search") {
		return SEARCH;
	}
	if (userCommand == "undo") {
		return UNDO;
	}
	if (userCommand == "home") {
		return HOME;
	}

	switch (currentScreen) {
	case OutputControl::HOME_SCREEN: {
		return determineCommandType_HomeScreen(userCommand);
		break;
			}
	case OutputControl::EDIT_SCREEN: {
		return determineCommandType_EditScreen(userCommand);
		break;

			}
	case OutputControl::DELETE_SCREEN: {
		return determineCommandType_DeleteScreen(userCommand);
		break;

			}
	case OutputControl::SEARCH_RESULTS_SCREEN: {
		return determineCommandType_SearchResultsScreen(userCommand);
		break;

			}
	case OutputControl::TO_DO_LIST_VIEW: {
		return determineCommandType_ToDoListView(userCommand);
		break;

			}
	case OutputControl::CALENDAR_VIEW: {
		return determineCommandType_CalendarView(userCommand);
		break;
			}
	case OutputControl::OVERDUE_TASKS_SCREEN: {
		return determineCommandType_OverdueTasksScreen(userCommand);
		break;

			 }
										 

	default: {
				break;
			 }
	}

	
	//DELETE THIS. PREVENT ERROR ONLY
	return ADD;

}

CommandType Parser::determineCommandType_HomeScreen(string userCommand){
	

	if (userCommand == "t") {
		return VIEW_TODOLIST;
	}
	else if (userCommand == "c") {
		return VIEW_CALENDAR;
	}
	else if (userCommand == "o") {
		return VIEW_OVERDUE;
	}
	else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_EditScreen(string userCommand){
	
	if (userCommand == "e") {
		return EDIT;
	}
	else if (userCommand == "o") {
		return HOME;
	}
	else if (userCommand == "c") {
		return CANCEL;
	}
	else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_DeleteScreen(string userCommand){
	if (userCommand == "u") {
		return UNDO;
	}
	else if (userCommand == "c") {
		return VIEW_CALENDAR;
	}
	else if (userCommand == "t") {
		return VIEW_TODOLIST;
	}
	else if (userCommand == "o") {
		return VIEW_OVERDUE;
	}
	else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
	//DELETE: FOR TEMP DEBUG ONLY

}
CommandType Parser::determineCommandType_SearchResultsScreen(string userCommand){
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_ToDoListView(string userCommand){
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_CalendarView(string userCommand){
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_OverdueTasksScreen(string userCommand){
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}

bool Parser::isKeyword(string myWord){
	return isKeywordTime(myWord) || isKeywordDate(myWord);
}
bool Parser::isKeywordTime(string myWord){
	return isKeywordStartTime(myWord) || isKeywordEndTime(myWord);
}

bool Parser::isKeywordStartTime(string myWord){
	return myWord=="at" || myWord == "from" || myWord == "between" || myWord == "next";
}
bool Parser::isKeywordEndTime(string myWord){
	return myWord=="to" || myWord == "-" || myWord == "by" || myWord == "and";
}
bool Parser::isKeywordDate(string myWord){
	return myWord=="on";
}