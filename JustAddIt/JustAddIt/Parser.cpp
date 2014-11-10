//@author A0110770U
#include "stdafx.h"
#include "Parser.h"
#define MONTHS_IN_YEAR 12
#define DEFAULT_MONTH_START "1"
#define FORMAT_24H_SIZE 4
#define START_TIME_FIELD_INDEX 3
#define END_TIME_FIELD_INDEX 4
#define PRIORITY_FIELD_INDEX 5
#define DEFAULT_FIRST_INDEX "1"
#define CATEGORY_MARKER "#"
#define PRIORITY_MARKER "!"
#define PRIORITY_MARKER_SIZE 1
#define NUM_OF_FIELDS 6
#define DESCRIP_MARKER_FRONT "("
#define DESCRIP_MARKER_BACK ")"
#define TODAY_MARKER "today"
#define TOMORROW_MARKER "tomorrow"
#define NEXT_MARKER "next "
#define EMPTY_STRING ""

const string Parser::ERROR_INVALID_ITEM_NO = "Invalid item number! Please enter a valid number from the menu.";
const string Parser::ERROR_INVALID_FIELD_NO = "Invalid field number! Please enter a field number 1 - 6.";
const string Parser::ERROR_INVALID_COMMAND = "Invalid command! Please enter a valid command from the menu.";
const string Parser::ERROR_MISSING_TITLE =	"No title detected! Try something like \"add event title at 2pm\"";
const string Parser::ERROR_MISSING_CATEGORY = "No category detected! Please try e.g. \"add homework #school\"";
const string Parser::ERROR_INVALID_BRACKETS = "Invalid brackets! Try something like \"add event at 7pm (description)\"";
const string Parser::ERROR_INVALID_PRIORITY = "Wrong priority format entered. Please type \"high\", \"med\" or \"low\"";
const string Parser::ERROR_LOGIC_START_END = "You can't go back in time! End time should be later than start time.";

Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}
//This function inteprets a string user command input and
//returns the corresponding Command subclass object with
//required information embedded inside.
Command* Parser::stringToCommand(string userCommand) {
	

	
	//convert into a stream and get the first word
	istringstream commandStream(userCommand);
	string userAction;
	commandStream >> userAction;
	
	//translate the first word into a CommandType
	ParserForCmds* myParserCmd = new ParserForCmds();
	CommandType commandAction = myParserCmd->determineCommandType(userAction, OutputControl::getCurrentScreen());
	
	switch (commandAction) {
		case ADD: {
					
			Item* myItem = new Item;
			//Pass remaining stream as details
			string stringDetails;
			getline(commandStream, stringDetails);
			embedDetailsInItem(myItem, stringDetails);

			CmdAddItem* myAdd = new CmdAddItem(myItem);
			return myAdd;

			break;
				  }

		case SEARCH: {
			string keyword;
			getline(commandStream, keyword);
			//inform outputcontrol of keyword
			OutputControl::setCurrentKeywordSearched(keyword);
			CmdSearch* mySearch = new CmdSearch(keyword);
			return mySearch;
			break;
		}
		case VIEW_LAST_SEARCH: {
			CmdSearch* mySearch = new CmdSearch(OutputControl::getCurrentKeywordSearched());
			return mySearch;
			break;
		}
		case EDIT_ITEM: {
			int itemNum;
			commandStream >> itemNum;
			if(itemNum <= 0 || itemNum > OutputControl::getNumberOfDisplayedItems()){
				throw invalid_argument(ERROR_INVALID_ITEM_NO);
			}
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList()+itemNum-1);
			return myEdit;
			break;
		}

		case EDIT_FIELD: {
			string newFieldInfo=EMPTY_STRING;
			string buffer;
			int fieldNum;
			commandStream >> fieldNum;
			if(fieldNum==0 || fieldNum > NUM_OF_FIELDS){
				throw invalid_argument(ERROR_INVALID_FIELD_NO);
			}	
			commandStream >> newFieldInfo;
			getline(commandStream, buffer);
			newFieldInfo += buffer;
			return constructRespectiveCmdEdit(fieldNum, newFieldInfo);
			break;
						 }

		case DELETE: {
			vector<Item*> collatedList;
			string itemNumsStr;
			getline(commandStream, itemNumsStr);
			CmdDeleteItem* myDelete = new CmdDeleteItem(convertItemNumsToItemPtrs(itemNumsStr));
			return myDelete;
			break;
					 }

		case MARK: {
			vector<Item*> collatedList;
			string itemNumsStr;
			getline(commandStream, itemNumsStr);
			CmdMarkItemDone* myMark = new CmdMarkItemDone(convertItemNumsToItemPtrs(itemNumsStr));
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
		case VIEW_TODOLIST : {
			CmdGoToListView* myList = new CmdGoToListView();
			return myList;
			break;
					}
		case VIEW_OVERDUE : {
			CmdShowOverdueDeadlines* myOverdue = new CmdShowOverdueDeadlines();
			return myOverdue;
			break;
					}
		case HOME : {
			CmdHome* myHome = new CmdHome();
			return myHome;
			break;
					}
		case CLEAR_ALL_DONE : {
			CmdClearAllDone* myDone = new CmdClearAllDone();
			return myDone;
			break;
							  }
							  
		case CLEAR_ALL_OVERDUE : {
			CmdClearAllOverdue* myOverdue = new CmdClearAllOverdue();
			return myOverdue;
			break;
								 }
		case EXPORT : {
			CmdExport* myExport = new CmdExport();
			return myExport;
			break;
					  }
		default: {
			throw invalid_argument(ERROR_INVALID_COMMAND);
			break;
				 }

	}

}

//This function detects all possible details in the input string
//such as title, date, time, category, priority, description.
//It sets these values into the input Item*.
void Parser::embedDetailsInItem(Item* myItem, string stringDetails){

	vector<string> vectorOfStrings;
	vectorOfStrings = convertStringToVector(stringDetails);
	detectCategoryAndEmbed(myItem, stringDetails);
	detectPriorityAndEmbed(myItem, stringDetails);
	detectDescriptionAndEmbed(myItem, stringDetails);
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
		myItem->setStartDate();
		myItem->setEndDate();
	}
	if(myItem->getEndDateTime_T()<myItem->getStartDateTime_T()){
		throw logic_error(ERROR_LOGIC_START_END);
	}
	if(isDeadline){
		myItem->setItemTypeDeadline();
	}
	//if no date or no time, it is a task
	else if(!foundDate && !foundTime){
		myItem->setStartEndDateTimeAsNull();
		myItem->setItemTypeTask();
	}
	else{
		myItem->setItemTypeEvent();
	}


			
}


//This function detects the title in the input string
//and sets its value into the input Item*.
//The title found is then removed from the input string.
void Parser::detectTitleAndEmbed(Item* myItem, string &stringDetails){
	assert(myItem != nullptr);

	vector<string> vectorOfStrings;
	vector<string>::iterator titleStartIter;
	vector<string>::iterator titleEndIter;
	vector<string>::iterator startWordIter;
	vector<string>::iterator endWordIter;
	vector<string>::iterator prevWordIter;
	string titleToSet;
	string leftoverString;

	vectorOfStrings = convertStringToVector(stringDetails);

	startWordIter = find_if(vectorOfStrings.begin(), vectorOfStrings.end(), isKeywordEndOfTitle);
	endWordIter = find_if(vectorOfStrings.begin(), vectorOfStrings.end(), isKeywordEndTime);
	//if didn't find any keywords
	if(startWordIter==vectorOfStrings.end() && endWordIter==vectorOfStrings.end()){
		titleStartIter = vectorOfStrings.begin();
		titleEndIter = vectorOfStrings.end();
	}
	//if found start keyword before end keyword, cut title till start keyword
	else if(startWordIter<endWordIter){
		titleStartIter= vectorOfStrings.begin();
		titleEndIter = startWordIter;
	}
	//if found end keyword before start keyword
	else if(endWordIter<startWordIter){
		vector<string>::iterator timeIter;
		vector<string>::iterator monthIter;
		timeIter = find_if(vectorOfStrings.begin(), vectorOfStrings.end(), isTime);
		monthIter = find_if(vectorOfStrings.begin(), vectorOfStrings.end(), isMonth);
		//if month before endkeyword and before time, cut title till month
		if(monthIter<endWordIter && monthIter < timeIter){
			titleStartIter= vectorOfStrings.begin();
			titleEndIter = monthIter;
		}

		//if time before endkeyword and before month, cut title till time
		else if(timeIter<endWordIter && timeIter < monthIter){
			titleStartIter= vectorOfStrings.begin();
			titleEndIter = timeIter;
		}
		//else, cut title till endkeyword
		else{
			titleStartIter= vectorOfStrings.begin();
			titleEndIter = endWordIter;
		}
	}
	
	//update the remaining string
	stringDetails = convertVectorToString(titleEndIter, vectorOfStrings.end());
	
	titleToSet = convertVectorToString(titleStartIter, titleEndIter);
	if(titleToSet==EMPTY_STRING){
		throw invalid_argument(ERROR_MISSING_TITLE);
	}
	myItem->setTitle(titleToSet);
	
	return;
}

//This function detects the presence of the deadline keyword 
//in the input string. It returns 'true' if found and 'false' otherwise.
//If the keyword is found, it is removed from the input string.
bool Parser::detectDeadlineKeywordAndTrim(string &stringDetails){
	vector<string> vectorOfStrings;
	vector<string>::iterator deadlineWordIter;
	bool isFound = false;
	
	vectorOfStrings = convertStringToVector(stringDetails);
	deadlineWordIter = find_if(vectorOfStrings.begin(), vectorOfStrings.end(), isKeywordDeadline);
	
	//if deadline keyword found
	if (deadlineWordIter!=vectorOfStrings.end()){
		vectorOfStrings.erase(deadlineWordIter);
		isFound = true;
	}
	stringDetails = convertVectorToString(vectorOfStrings.begin(), vectorOfStrings.end());
	return isFound;
}

//This function detects the time in the input string
//and sets its value into the input Item*.
//If time is detected, this function returns 'true'.
//Otherwise, it returns false.
bool Parser::detectTimeAndEmbedIsOk(Item* myItem, string stringDetails, bool isDeadline){
	assert(myItem != nullptr);

	istringstream streamDetails(stringDetails);
	string startTime=EMPTY_STRING;
	string endTime=EMPTY_STRING;
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
//This function detects the month date in the input string
//and sets its value into the input Item*.
//The month date found is then removed from the input string.
//If a month date is detected, this function returns 'true'.
//Otherwise, it returns false.
bool Parser::detectMonthDateAndEmbedIsOk(Item* myItem, string &stringDetails,  bool isDeadline){
	assert(myItem != nullptr);

	istringstream streamDetails(stringDetails);
	string currentWord=EMPTY_STRING;
	string previousWord;
	string nextWord;
	string startMonthFound=EMPTY_STRING;
	string startDateFound=EMPTY_STRING;
	string startDayFound = EMPTY_STRING;
	string endMonthFound=EMPTY_STRING;
	string endDateFound=EMPTY_STRING;
	string endDayFound = EMPTY_STRING;
	int startDayInt;
	int startMonthInt;
	int endDayInt;
	int endMonthInt;
	bool endExists = false;
	
	streamDetails >> previousWord;
	while(streamDetails >> currentWord && !isMonth(currentWord)){
		previousWord = currentWord;
	}
	if(isMonth(previousWord)){
		startMonthFound = previousWord; 
	}
	if(isMonth(currentWord)){
		startMonthFound = currentWord; 
	}
	if(isMonth(previousWord) || isMonth(currentWord)){	
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
		//if only month is found, set a default day
		else{
			startDayFound = DEFAULT_MONTH_START;
			startDateFound = startMonthFound;
		}

		//remove date from input string
		trimWordFromString(stringDetails, startDateFound);
		startDayInt = stoi(startDayFound);
		startMonthInt = convertStrToIntMonth(startMonthFound);
		
		//reset currentWord and search for second date
		currentWord=EMPTY_STRING;
		while(streamDetails >> currentWord && !isMonth(currentWord)){
			previousWord = currentWord;
		}

		if(isMonth(currentWord)){
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
			//if only month is found, set a default day
			else{
				endDayFound = DEFAULT_MONTH_START;
				endDateFound = endMonthFound;
			}
			//remove date from input string
			trimWordFromString(stringDetails, endDateFound);
			endDayInt = stoi(endDayFound);
			endMonthInt = convertStrToIntMonth(endMonthFound);

		}

		if(isDeadline){
			myItem->setStartDate(startDayInt, startMonthInt);
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
	
	

}

//This function detects the day of the week in the input string
//and sets its value into the input Item*.
//The day of the week found is then removed from the input string.
//If a day of the week is detected, this function returns 'true'.
//Otherwise, it returns false.
bool Parser::detectDayOfWeekDateAndEmbedIsOk(Item* myItem, string &stringDetails,  bool isDeadline){
	assert(myItem != nullptr);

	string startDate=EMPTY_STRING;
	string endDate=EMPTY_STRING;
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
		//remove day from input string
		if(stringDetails.find(NEXT_MARKER + startDate)!=string::npos){
			isWordNextStart=true;
			trimWordFromString(stringDetails, NEXT_MARKER + startDate);
		}
		else{
			trimWordFromString(stringDetails, startDate);
		}
		
		startDaysToAdd = convertDayOfWeekToIntDaysToAdd(startDate, isWordNextStart);
		myItem->addToStartDate(startDaysToAdd);
		if(isDeadline){
			myItem->addToEndDate(startDaysToAdd);
		}
		else{
			//start exists and end exists
			if(isDayOfWeek(endDate)){
				
				endFound = true;
				//remove the end day from input string
				if(stringDetails.find(NEXT_MARKER + endDate)!=string::npos){
					isWordNextEnd=true;
					trimWordFromString(stringDetails, NEXT_MARKER + endDate);
				}
				else{
					trimWordFromString(stringDetails, endDate);
				}
				
			
				endDaysToAdd = convertDayOfWeekToIntDaysToAdd(endDate, isWordNextEnd);
				myItem->addToEndDate(endDaysToAdd);
			}
			else{
			//start exists but end does not exist
			//default end date is same as start date
				myItem->addToEndDate(startDaysToAdd);
			}
		}
	}


	return startFound || endFound;


}

//This function detects the category in the input string
//and sets its value into the input Item*.
//The cateogry found is then removed from the input string.
void Parser::detectCategoryAndEmbed(Item* myItem, string &stringDetails){
	assert(myItem != nullptr);

	string::iterator myIter;
	string categoryToSet=EMPTY_STRING;
	size_t position;
	position = stringDetails.find(CATEGORY_MARKER);
	 
	//if found, get the text after the marker
	if(position!=string::npos){
		myIter = stringDetails.begin() + position;
		myIter++;
		if(*myIter==' '){
			throw invalid_argument(ERROR_MISSING_CATEGORY);
		}
		while(myIter!=stringDetails.end() && *myIter!=' '){
			categoryToSet += *myIter;
			myIter++;
		}
		myItem->setCategory(categoryToSet);
		string categoryFound = CATEGORY_MARKER + categoryToSet;
		trimWordFromString(stringDetails, categoryFound);
	}

	return;
}

//This function detects the priority in the input string
//and sets its value into the input Item*.
//The priority found is then removed from the input string.
void Parser::detectPriorityAndEmbed(Item* myItem, string &stringDetails){
	assert(myItem != nullptr);

	size_t position;
	int count = 0;
	
	while(true){
		position = stringDetails.find(PRIORITY_MARKER);
		//if found, count and trim "!"
		if(position!=string::npos){
			count++;
			trimWordFromString(stringDetails, PRIORITY_MARKER);
		}
		else{
			break;
		}
	}
	if(count == 1){
		myItem->setPriority(static_cast<Item::PriorityLevel>(1));
	}
	else if(count >= 2){
		myItem->setPriority(static_cast<Item::PriorityLevel>(2));
	}
	else{
		myItem->setPriority(static_cast<Item::PriorityLevel>(0));
	}
	return ;
}

//This function detects the description in the input string
//and sets its value into the input Item*.
//The description found is then removed from the input string.
void Parser::detectDescriptionAndEmbed(Item* myItem, string &stringDetails){
	assert(myItem != nullptr);

	size_t positionFront;
	size_t positionBack;
	string descripToSet;
	positionFront = stringDetails.find(DESCRIP_MARKER_FRONT);
		//if found the front
		if(positionFront!=string::npos){
			positionBack = stringDetails.find(DESCRIP_MARKER_BACK);
			//if found the back
			if(positionBack<positionFront){
				throw invalid_argument(ERROR_INVALID_BRACKETS);
			}
			if(positionBack!=string::npos && positionBack!=0){
				descripToSet = stringDetails.substr(positionFront, positionBack-positionFront+1);
				trimWordFromString(stringDetails, descripToSet);
				descripToSet = descripToSet.substr(1, descripToSet.length()-2);
				myItem->setDescription(descripToSet);
			}
		}

	return;
}

//This function detects the different possible formats of date and time
//in the input string. It then sets its value into the input Item.
void Parser::detectTypesOfDatesAndEmbed(Item &myNewItem, string newFieldInfo, bool isDeadline){
	detectMonthDateAndEmbedIsOk(&myNewItem, newFieldInfo, isDeadline);
	detectDayOfWeekDateAndEmbedIsOk(&myNewItem, newFieldInfo, isDeadline);
	detectTimeAndEmbedIsOk(&myNewItem, newFieldInfo, isDeadline);

}

//This function accepts an input string and 
//returns true if the string consists of digits only.
//Otherwise, it returns false.
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

//This function accepts an input string and 
//returns true if the string is a month.
//Otherwise, it returns false.
bool Parser::isMonth(string query){
	if(convertStrToIntMonth(query)>=0)
		return true;
	else
		return false;
}

//This function accepts an input string and 
//returns true if the string is in a time format.
//Otherwise, it returns false.
bool Parser::isTime(string query){
	if(isdigit(query[0])>0)
		return true;
	else
		return false;
}

//This function accepts an input string and 
//returns true if the string is a day of the week. e.g. "Monday"
//Otherwise, it returns false.
bool Parser::isDayOfWeek(string query){
	if(convertDayOfWeekToIntDaysToAdd(query, false)>=0)
		return true;
	else
		return false;
}

//This function accepts an input string that represents time
//and returns the number of hours it indicates. 
int Parser::convertStringToIntHour(string stringTime){
	
	assert(isTime(stringTime)==true);
	convertStringToLowercase(stringTime);
	size_t positionFound;
	//set accountForPM to 12 if afternoon
	int accountForPM=0;

	//if 2359 format
	if(isInteger(stringTime) && stringTime.length() == FORMAT_24H_SIZE){
		stringTime = stringTime.substr(0,2);
		return stoi(stringTime);
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
	int actualTime = (stoi (stringTime)%12) + accountForPM;
	
	return actualTime;
}

//This function accepts an input string that represents time
//and returns the number of minutes it indicates. 
int Parser::convertStringToIntMin(string stringTime){
	assert(isTime(stringTime)==true);
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

//This function accepts an input string that represents month
//and returns the number of months since January. 
//It returns -1 if input string is not a month.
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

}

//This function converts the input string to lowercase.
void Parser::convertStringToLowercase(string &myString){
	unsigned int i;
	for(i=0; i<myString.size(); i++){
		myString[i] = tolower(myString[i]);
	}
	return;
}

//This function converts the input 'day of week' to the
//number of days between today and that input day.
int Parser::convertDayOfWeekToIntDaysToAdd(string query, bool isNextWeek){
	
	const string dayOfWeek[] = {"sunday", "monday", "tuesday", "wednesday","thursday",
								"friday", "saturday"};
	const string dayOfWeek3[] = {"sun", "mon", "tue", "wed","thu",
								"fri", "sat"};
	convertStringToLowercase(query);
	int i;
	int daysAfterSunday=-1;
	bool dayOfWeekFound=false;

	//account for "today"
	if(query==TODAY_MARKER){
		return 0;
	}
	//account for "tomorrow"
	else if(query==TOMORROW_MARKER){
		return 1;
	}
	//else, search for other days of the week
	else{

		for(i=0; i<7 && !dayOfWeekFound; i++){
				if(query==dayOfWeek[i] || query==dayOfWeek3[i]){
					daysAfterSunday=i;
					dayOfWeekFound = true;
				}
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
	}
	

}

//These functions determine if the input string
//match any of the supported keywords.
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
	return myWord=="to" || myWord == "-"  || myWord == "and";
}
bool Parser::isKeywordDeadline(string myWord){
	return myWord == "by" || myWord == "due";
}
bool Parser::isKeywordDate(string myWord){
	return myWord=="on";
}
bool Parser::isKeywordEndOfTitle(string myWord){
	return isKeywordDate(myWord) || isKeywordStartTime(myWord) || isKeywordDeadline(myWord) || isDayOfWeek(myWord);
}

//This function converts a string of item numbers
//into a vector of Item*, based on what is currently displayed.
//If the string is empty, a vector with the first Item* that is displayed is returned.
vector <Item*> Parser::convertItemNumsToItemPtrs(string itemNumsStr){
	vector<Item*> itemPtrs;
	int itemNum;
	istringstream itemStream(itemNumsStr);
	//if empty, return the first item*
	if(itemNumsStr==EMPTY_STRING){
		itemPtrs.push_back(OutputControl::getItemAddr(1));
	}
	else{
		while(itemStream >> itemNum){
			if(itemNum <= 0 || itemNum > OutputControl::getNumberOfDisplayedItems()){
				throw invalid_argument(ERROR_INVALID_ITEM_NO);
			}
			itemPtrs.push_back(OutputControl::getItemAddr(itemNum));
		}
	}
	return itemPtrs;
}
//This function converts an input string to a
//vector of strings, separating the input string by whitespaces.
vector<string> Parser::convertStringToVector(string inputString){

	istringstream inputStream(inputString);
	string currentWord;
	vector<string> vectorOfStrings;

	while(inputStream >> currentWord){
		vectorOfStrings.push_back(currentWord);
	}

	return vectorOfStrings;
}
//This function accepts two vector iterators and concatenates
//the vector items in between them to a string.
//The final concatenated string is returned.
string Parser::convertVectorToString(vector<string>::iterator start, vector<string>::iterator end){
	string finalString=EMPTY_STRING;
	//if start and end are same point, return nothing
	if(start==end){
		return finalString;
	}
	else{
		//if first word exists
		if(*start!=EMPTY_STRING){
			finalString=*start;
			start++;
		}
		while(start!=end){
			finalString += ' ' + *start;
			start++;
		}
	}
	return finalString;
	
}
//This function converts a priority string to 
//an enum Item::PriorityLevel type.
Item::PriorityLevel Parser::convertStrToPriorityLevel(string priority){
	if(isHighPriority(priority)){
		return Item::PriorityLevel::HIGH;
	}else if(isMedPriority(priority)){
		return Item::PriorityLevel::MED;
	}else if(isLowPriority(priority)){
		return Item::PriorityLevel::LOW;
	}else{
		throw invalid_argument(ERROR_INVALID_PRIORITY);
	}
}
bool Parser::isHighPriority(string priority){
	convertStringToLowercase(priority);
	return priority == "high" || priority == "h" || priority == "hi";
}

bool Parser::isMedPriority(string priority){
	convertStringToLowercase(priority);
	return priority == "medium" || priority == "med" || priority == "m";
}
bool Parser::isLowPriority(string priority){
	convertStringToLowercase(priority);
	return priority == "low" || priority == "l";
}

void Parser::trimWordFromString(string &originalString, string toTrim){
	originalString.replace(originalString.find(toTrim),toTrim.length(),EMPTY_STRING);	
}


//This function constructs and reutrns the respecitive CmdEditItem*
//subclass depending on the input field number.
CmdEditItem* Parser::constructRespectiveCmdEdit(int fieldNum, string newFieldInfo){
	switch (fieldNum) {
		case START_TIME_FIELD_INDEX: {
			//check for all the possible types of time input
			Item myNewItem = **(OutputControl::getCurrentDisplayedItemList());
			detectTypesOfDatesAndEmbed(myNewItem, newFieldInfo, false);		
			if(OutputControl::getItemAddr(1)->getEndDateTime_T() < myNewItem.getStartDateTime_T()){
				throw logic_error(ERROR_LOGIC_START_END);
			}
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, myNewItem.getStartDateTime());
			return myEdit;
									 }
		case END_TIME_FIELD_INDEX: {
			//check for all the possible types of time input
			Item myNewItem = **(OutputControl::getCurrentDisplayedItemList());;
			detectTypesOfDatesAndEmbed(myNewItem, newFieldInfo, true);
			if(myNewItem.getEndDateTime_T() < OutputControl::getItemAddr(1)->getStartDateTime_T()){
				throw logic_error(ERROR_LOGIC_START_END);
			}
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, myNewItem.getEndDateTime());
			return myEdit;
								   }
		case PRIORITY_FIELD_INDEX: {
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, convertStrToPriorityLevel(newFieldInfo));
			return myEdit;
								   }
		default :{
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, newFieldInfo);
			return myEdit;
				 }
	}
}