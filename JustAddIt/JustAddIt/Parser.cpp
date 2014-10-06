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
	CommandType commandAction = determineCommandType(userAction);
	//translateStringToDetails(currentLogic, );
	
	switch (commandAction) {
		case ADD: {
			//Pass remaining stream as details
			
			Item* item1 = new Item;
			string stringDetails;
			getline(commandStream, stringDetails);
			embedDetailsInItem(item1, stringDetails);
			CmdAddItem* myAdd = new CmdAddItem(*item1);
			return myAdd;
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

	//loop and stop till it gets the first time keyword
	streamDetails >> currentWord;
	while(!isKeywordTime(currentWord)){
		previousWord = currentWord;
		streamDetails >> currentWord;
	}
	if(isKeywordStartTime(currentWord)){
		//get the next string and treat it as start time
		streamDetails >> startTime;
		previousWord = startTime;
		//move on to the next word after start time word
		streamDetails >> currentWord;
	}
	
	if(isKeywordEndTime(currentWord)){
		//previous string is start time
		//next string is end time
		startTime=previousWord;
		streamDetails >> endTime;
	}
	

	int startHourToBeSet = convertStringToIntHour(startTime);
	int endHourToBeSet = convertStringToIntHour(endTime);
	int startMinToBeSet = convertStringToIntMin(startTime);
	int endMinToBeSet = convertStringToIntMin(endTime);	

	myItem->setStartTime(startHourToBeSet, startMinToBeSet);
	myItem->setEndTime(endHourToBeSet, endMinToBeSet);

	return;
	
}
void Parser::detectDateAndEmbed(Item* myItem, string stringDetails){

	istringstream streamDetails(stringDetails);

	string currentWord;
	
	//loop and stop when it finds the first date keyword
	while(!isKeywordDate(currentWord)){
		streamDetails >> currentWord;
	}
	int day;
	string month;
	streamDetails >> day;
	streamDetails >> month;

	int monthNumber = convertStrToIntMonth(month);
	myItem->setStartDate(day, monthNumber);
	myItem->setEndDate(day, monthNumber);
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
	const string month3[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
								"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	const string monthfull[] = {"January", "February", "March", "April", "May", "June",
								"July", "August", "September", "October", "November", "December"};
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

CommandType Parser::determineCommandType(string userCommand) {
	if (userCommand == "add") {
		return ADD;
	}

	//DELETE THIS. PREVENT ERROR ONLY
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