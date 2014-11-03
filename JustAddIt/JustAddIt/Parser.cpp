#include "stdafx.h"
#include "Parser.h"
#define MONTHS_IN_YEAR 12
#define DEFAULT_MONTH_START "1"
#define FORMAT_24H_SIZE 4
#define START_TIME_FIELD_INDEX 3
#define END_TIME_FIELD_INDEX 4
#define DEFAULT_FIRST_INDEX "1"
#define CATEGORY_MARKER "#"
#define PRIORITY_MARKER "!"
#define PRIORITY_MARKER_SIZE 1
#define NUM_OF_FIELDS 6
#define DESCRIP_MARKER_FRONT "("
#define DESCRIP_MARKER_BACK ")"
#define TODAY_MARKER "today"
#define TOMORROW_MARKER "tomorrow"

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
	ParserForCmds* myParserCmd = new ParserForCmds();
	CommandType commandAction = myParserCmd->determineCommandType(userAction, OutputControl::getCurrentScreen());
	
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
				throw invalid_argument("Invalid item number! Please enter a valid number.");
			}
			CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList()+itemNum-1);
			return myEdit;
			break;
		}

		case EDIT_FIELD: {
			string newFieldInfo="";
			string buffer;
			int fieldNum;
			commandStream >> fieldNum;
			if(fieldNum==0 || fieldNum > NUM_OF_FIELDS){
				throw invalid_argument("Invalid field number! Please enter a field number 1 - 6."); 
			}	
			commandStream >> newFieldInfo;
			getline(commandStream, buffer);
			newFieldInfo += buffer;
			
			if(fieldNum == START_TIME_FIELD_INDEX){
				//check for all the possible types of time input
				Item myNewItem = **(OutputControl::getCurrentDisplayedItemList());
				detectMonthDateAndEmbedIsOk(&myNewItem, newFieldInfo, false);
				detectDayOfWeekDateAndEmbedIsOk(&myNewItem, newFieldInfo, false);
				detectTimeAndEmbedIsOk(&myNewItem, newFieldInfo, false);
				CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, myNewItem.getStartDateTime());
				return myEdit;
			}
			else if(fieldNum == END_TIME_FIELD_INDEX){
				//check for all the possible types of time input
				Item myNewItem = **(OutputControl::getCurrentDisplayedItemList());
				detectMonthDateAndEmbedIsOk(&myNewItem, newFieldInfo, true);
				detectDayOfWeekDateAndEmbedIsOk(&myNewItem, newFieldInfo, true);
				detectTimeAndEmbedIsOk(&myNewItem, newFieldInfo, true);
				CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, myNewItem.getEndDateTime());
				return myEdit;
			
			}
			else{
				CmdEditItem* myEdit = new CmdEditItem(OutputControl::getCurrentDisplayedItemList(), fieldNum, newFieldInfo);
				return myEdit;
			}
			break;
				   }

		case DELETE: {
			vector<Item*> collatedList;
			string itemNumsStr;
			getline(commandStream, itemNumsStr);
			collatedList = convertItemNumsToItemPtrs(itemNumsStr);
			CmdDeleteItem* myDelete = new CmdDeleteItem(collatedList);
			return myDelete;
			break;
					 }

		case MARK: {
			vector<Item*> collatedList;
			string itemNumsStr;
			getline(commandStream, itemNumsStr);
			collatedList = convertItemNumsToItemPtrs(itemNumsStr);
			CmdMarkItemDone* myMark = new CmdMarkItemDone(collatedList);
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
			throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
			break;
				 }

	}

}

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
		time_t nowTime;
		tm nowTimeTM;
		time(&nowTime);
		localtime_s (&nowTimeTM, &nowTime);
		myItem->setStartDate(nowTimeTM.tm_mday, nowTimeTM.tm_mon);
		myItem->setEndDate(nowTimeTM.tm_mday, nowTimeTM.tm_mon);
	}
	
	if(isDeadline){
		myItem->setItemType("deadline");
	}
	//if no date or no time, it is a task
	else if(!foundDate && !foundTime){
		myItem->setStartEndDateTimeAsNull();
		myItem->setItemType("task");
	}
	else{
		myItem->setItemType("event");
	}


			
}



void Parser::detectTitleAndEmbed(Item* myItem, string &stringDetails){
	

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
	//if found start keyword before end keyword
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
		//if month before endword and before time
		if(monthIter<endWordIter && monthIter < timeIter){
			titleStartIter= vectorOfStrings.begin();
			titleEndIter = monthIter;
		}

		//if time before endword and before month
		else if(timeIter<endWordIter && timeIter < monthIter){
			titleStartIter= vectorOfStrings.begin();
			titleEndIter = timeIter;
		}
		else{
			titleStartIter= vectorOfStrings.begin();
			titleEndIter = endWordIter;
		}
	}
	
	//for the leftovers
	stringDetails = convertVectorToString(titleEndIter, vectorOfStrings.end());
	titleToSet = convertVectorToString(titleStartIter, titleEndIter);
	myItem->setTitle(titleToSet);
	//TODO:Exception if no title (first word is a keyword)
	return;
}
bool Parser::detectDeadlineKeywordAndTrim(string &stringDetails){
	vector<string> vectorOfStrings;
	vector<string>::iterator deadlineWordIter;
	bool isFound = false;
	
	vectorOfStrings = convertStringToVector(stringDetails);
	deadlineWordIter = find_if(vectorOfStrings.begin(), vectorOfStrings.end(), isKeywordDeadline);
	
	//if found
	if (deadlineWordIter!=vectorOfStrings.end()){
		vectorOfStrings.erase(deadlineWordIter);
		isFound = true;
	}
	stringDetails = convertVectorToString(vectorOfStrings.begin(), vectorOfStrings.end());
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
	if(isMonth(previousWord)){
		startMonthFound = previousWord; 
	}
	if(isMonth(currentWord)){
		//store the month name in date found
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
				endDayFound = DEFAULT_MONTH_START;
				endDateFound = endMonthFound;
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
void Parser::detectCategoryAndEmbed(Item* myItem, string &stringDetails){

	string::iterator myIter;
	string categoryToSet="";
	size_t pos;
	pos = stringDetails.find(CATEGORY_MARKER);
	 
	//if found
	if(pos!=string::npos){
		myIter = stringDetails.begin() + pos;
		myIter++;
		while(myIter!=stringDetails.end() && *myIter!=' '){
			categoryToSet += *myIter;
			myIter++;
		}
		myItem->setCategory(categoryToSet);
		string categoryFound = CATEGORY_MARKER + categoryToSet;
		stringDetails.replace(stringDetails.find(categoryFound),categoryFound.length(),"");	
	}

	return;
}
void Parser::detectPriorityAndEmbed(Item* myItem, string &stringDetails){
	size_t position;
	int count = 0;
	
	
	while(true){
		position = stringDetails.find(PRIORITY_MARKER);
		//if found, count and trim "!"
		if(position!=string::npos){
			count++;
			stringDetails.replace(stringDetails.find(PRIORITY_MARKER),PRIORITY_MARKER_SIZE,"");
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
void Parser::detectDescriptionAndEmbed(Item* myItem, string &stringDetails){
	size_t positionFront;
	size_t positionBack;
	string descripToSet;
	positionFront = stringDetails.find(DESCRIP_MARKER_FRONT);
		//if found the front
		if(positionFront!=string::npos){
			positionBack = stringDetails.find(DESCRIP_MARKER_BACK);
			//if found the back
			if(positionBack<positionFront){
				throw invalid_argument("Invalid brackets! Please follow e.g. add event at 7pm (description)");
			}
			if(positionBack!=string::npos && positionBack!=0){
				descripToSet = stringDetails.substr(positionFront, positionBack-positionFront+1);
				stringDetails.replace(stringDetails.find(descripToSet),descripToSet.length(),"");
				
				descripToSet = descripToSet.substr(1, descripToSet.length()-2);
				myItem->setDescription(descripToSet);
			}
		}

	return ;
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
		//TODO: Throw exception for bad day
	}
	

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

vector <Item*> Parser::convertItemNumsToItemPtrs(string itemNumsStr){
	vector<Item*> itemPtrs;
	int itemNum;
	istringstream itemStream(itemNumsStr);
	//if empty, return the first item*
	if(itemNumsStr==""){
		itemPtrs.push_back(OutputControl::getItemAddr(1));
	}
	else{
		while(itemStream >> itemNum){
			if(itemNum <= 0 || itemNum > OutputControl::getNumberOfDisplayedItems()){
				throw invalid_argument("Invalid item number! Please enter a valid number.");
			}
			itemPtrs.push_back(OutputControl::getItemAddr(itemNum));
		}
	}
	return itemPtrs;
}

vector<string> Parser::convertStringToVector(string inputString){

	istringstream inputStream(inputString);
	string currentWord;
	vector<string> vectorOfStrings;

	while(inputStream >> currentWord){
		vectorOfStrings.push_back(currentWord);
	}

	return vectorOfStrings;
}

string Parser::convertVectorToString(vector<string>::iterator start, vector<string>::iterator end){
	string finalString="";
	//if start and end are same point, return nothing
	if(start==end){
		return finalString;
	}
	else{
		//if first word exists
		if(*start!=""){
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



