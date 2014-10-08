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
	detectDateAndEmbed(myItem, stringDetails);
	detectTimeAndEmbed(myItem, stringDetails);	
		

	
}

void Parser::detectTitleAndEmbed(Item* myItem, string stringDetails){
	
	istringstream streamDetails(stringDetails);
	string title = "";
	string currentWord;
	//get the first word and store in title if not a keyword
	streamDetails >> currentWord;
	if(!isKeyword(currentWord)){
		title = currentWord;
	}
	//get the second word
	streamDetails >> currentWord;
	//and loop the subsequent adding
	while(!isKeyword(currentWord)){
		title += ' ' + currentWord;
		streamDetails >> currentWord;
	}
	myItem->setTitle(title);
	return;
}
void Parser::detectTimeAndEmbed(Item* myItem, string stringDetails){
	
	istringstream streamDetails(stringDetails);
	string previousWord="";
	string currentWord;
	string endTime;
	string startTime;
	bool startTimeExists=false;
	bool endTimeExists=false;
	bool keywordTimeFound=false;
	int startHourToBeSet;
	int startMinToBeSet;
	int endHourToBeSet;
	int endMinToBeSet;

	
	
	streamDetails >> currentWord;
	//for safety (if the first word is a keywordtime)
	if(isKeywordTime(currentWord)){
		keywordTimeFound=true;
	}
	previousWord = currentWord;
	//loop and stop if keywordtime is found
	while(!keywordTimeFound && streamDetails >> currentWord){
		if(isKeywordTime(currentWord)){
			keywordTimeFound=true;
		}
		previousWord = currentWord;
	}


	if(isKeywordStartTime(currentWord)){
		//get the next string and treat it as start time
		startTimeExists=true;
		streamDetails >> startTime;
		previousWord = startTime;
		//move on to the next word after start time word
		streamDetails >> currentWord;
	}
	
	if(isKeywordEndTime(currentWord)){
		//previous string is start time
		//next string is end time
		startTimeExists=true;//TODO: assumption that once got end keyword, start time exists
		endTimeExists=true;
		startTime=previousWord;
		streamDetails >> endTime;
	}
	
	if(startTimeExists){
		startHourToBeSet = convertStringToIntHour(startTime);
		startMinToBeSet = convertStringToIntMin(startTime);
		myItem->setStartTime(startHourToBeSet, startMinToBeSet);
	}
	if(endTimeExists){
		endHourToBeSet = convertStringToIntHour(endTime);
		endMinToBeSet = convertStringToIntMin(endTime);	
		myItem->setEndTime(endHourToBeSet, endMinToBeSet);
	}
	//tasks
	if(!startTimeExists && !endTimeExists){

		//TODO: MAGIC NUMBERS
		myItem->setStartTime(0, 0);
		myItem->setEndTime(23, 59);
	}

	
	

	return;
	
}
void Parser::detectDateAndEmbed(Item* myItem, string stringDetails){

	istringstream streamDetails(stringDetails);

	string currentWord;
	bool keywordDateFound=false;
	//loop and stop when it finds the first date keyword
	//
	while(!keywordDateFound && streamDetails >> currentWord){
		if(isKeywordDate(currentWord)){
			keywordDateFound=true;
		}
	}
	if(keywordDateFound){
		int day;
		string month;
		streamDetails >> day;
		streamDetails >> month;

		int monthNumber = convertStrToIntMonth(month);
		myItem->setStartDate(day, monthNumber);
		myItem->setEndDate(day, monthNumber);
	}
	else{
		return;
	}
	return;
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
	return 0; 
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