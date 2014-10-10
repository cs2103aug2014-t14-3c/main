#include "stdafx.h"
#include "Parser.h"
#define MONTHS_IN_YEAR 12

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
		case SAVE : {

			break;
					}
		case UNDO : {
			CmdUndo* myUndo = new CmdUndo();
			return myUndo;
			break;
					}
		case CANCEL : {
			CmdDeleteItem* myDelete = new CmdDeleteItem(OutputControl::getCurrentDisplayedItemList());
			return myDelete;
			break;
					}
		case VIEW_CALENDAR : {

			break;
					}
		case VIEW_TODOLIST : {

			break;
					}
		case VIEW_OVERDUE : {

			break;
					}

	
		//TODO: INVALID CASE AND DEFAULT CASE
	}
	return NULL;
}

void Parser::embedDetailsInItem(Item* myItem, string stringDetails)
{
	detectTitleAndEmbed(myItem, stringDetails);
	bool isDeadline = detectDeadlineKeywordAndTrim(stringDetails);
	bool foundDate = detectDateAndEmbedIsOk(myItem, stringDetails, isDeadline);
	bool foundTime = detectTimeAndEmbedIsOk(myItem, stringDetails, isDeadline);	

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
	streamDetails >> currentWord;
	if(isKeyword(currentWord)){
		title = previousWord;
	}
	else{
		title=previousWord;
		previousWord = currentWord;
		//get the next word;
		streamDetails >> currentWord;
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
bool Parser::detectDateAndEmbedIsOk(Item* myItem, string &stringDetails,  bool isDeadline){
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
			}
			//if the next word is a integer, it's the date
			else if(streamDetails >> nextWord && isInteger(nextWord)){
				endDayFound = nextWord;
				endDateFound = endMonthFound + ' ' + endDayFound;
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
			myItem->setStartDate(startDayInt, startMonthInt);
			myItem->setEndDate(endDayInt, endMonthInt);
		}
		return true;
	}
	else{
		return false;
	}
	//TODO: exception if first word is a month
	

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
int Parser::convertStringToIntHour(string stringTime){
	
	convertStringToLowercase(stringTime);
	size_t positionFound;
	//set accountForPM to 12 if afternoon
	int accountForPM=0;
	
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
	//what remains is the digits
	int actualTime = stoi (stringTime) + accountForPM;
	
	return actualTime;
}
int Parser::convertStringToIntMin(string stringTime){
	
	size_t positionFound1;
	size_t positionFound2;
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

CommandType Parser::determineCommandType(string userCommand, OutputControl::CurrentScreenType currentScreen) {
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
	
	if (userCommand == "add") {
		return ADD;
	}
	if (userCommand == "search") {
		return SEARCH;
	}
	if (userCommand == "e") {
		return EDIT;
	}
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_EditScreen(string userCommand){
	if (userCommand == "e") {
		return EDIT;
	}
	if (userCommand == "s") {
		return SAVE;
	}
	if (userCommand == "c") {
		return CANCEL;
	}
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
}
CommandType Parser::determineCommandType_DeleteScreen(string userCommand){
	if (userCommand == "u") {
		return UNDO;
	}
	if (userCommand == "c") {
		return VIEW_CALENDAR;
	}
	if (userCommand == "t") {
		return VIEW_TODOLIST;
	}
	if (userCommand == "o") {
		return VIEW_OVERDUE;
	}
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
	//DELETE: FOR TEMP DEBUG ONLY
	return ADD;
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
	return myWord=="at" || myWord == "from" || myWord == "between";
}
bool Parser::isKeywordEndTime(string myWord){
	return myWord=="to" || myWord == "-" || myWord == "by" || myWord == "and";
}
bool Parser::isKeywordDate(string myWord){
	return myWord=="on";
}