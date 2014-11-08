#include "stdafx.h"
#include "Item.h"
#include <time.h>

int Item::_idCounter = 1;

const string Item::MESSAGE_INVALID_ARGUMENT = "invalid argument entered";

const string Item::STRING_EMPTY = "";
const string Item::STRING_INVALID = "Invalid";

const string Item::ITEM_TYPE_EVENT = "event";
const string Item::ITEM_TYPE_DEADLINE = "deadline";
const string Item::ITEM_TYPE_TASK = "task";

const string Item::PRIORITY_LOW = "Low";
const string Item::PRIORITY_MED = "Medium";
const string Item::PRIORITY_HIGH = "High";

const string Item::IS_DONE = "0";

Item::Item(void){
	_title = "-";
	_description = "-";
	//default start/end time/date is null
	time_t myTempTime = 0;
	//time(&myTempTime);	//set current time to myTempTime
	localtime_s (&_startDateTime, &myTempTime); //assign time_t var (myTempTime) to tm variable (_startDateTime)
	localtime_s (&_endDateTime, &myTempTime);
	_venue = "-";
	_category = "-";
	_priority = MED;
	toggleDone();
	_id = _idCounter++;
}

Item::~Item(void)
{
}

vector<string>::iterator Item::strToItem(vector<string>::iterator iter) {
	setTitle(*iter++);
	setDescription(*iter++);
	setStartDateTime(*iter++);
	setEndDateTime(*iter++);
	setVenue(*iter++);
	setPriority(*iter++);
	setCategory(*iter++);
	toggleDone(*iter++);
	setItemType(*iter++);

	return iter;
}

bool Item::isEvent() {
	return _itemType == EVENT;
}

bool Item::isDeadline() {
	return _itemType == DEADLINE;
}

bool Item::isTask() {
	return _itemType == TASK;
}

string Item::getTitle() {
	return _title;
}

string Item::getDescription() {
	return _description;
}

struct tm Item::getStartDateTime() {
	return _startDateTime;
}

time_t Item::getStartDateTime_T() {
	return mktime(&_startDateTime);
}

string Item::getStartDateInString() {
	char tempArray[MAX_SIZE];
	if(&_startDateTime==NULL){
		return "";
	} else if (_startDateTime.tm_hour == -1) {
		return "-1";
	} else {
	strftime(tempArray, MAX_SIZE, "%A %d %b %Y %I:%M%p", &_startDateTime);

	string str(tempArray);

	return str;
	}
}

struct tm Item::getEndDateTime() {
	return _endDateTime;
}

time_t Item::getEndDateTime_T() {
	return mktime(&_endDateTime);
}

string Item::getEndDateInString() {
	char tempArray[MAX_SIZE];
	if(&_endDateTime==NULL){
		return "";
	} else if (_endDateTime.tm_hour == -1) {
		return "-1";
	} else {
		strftime(tempArray, MAX_SIZE, "%A %d %b %Y %I:%M%p", &_endDateTime);

		string str(tempArray);

		return str;
	}
}

string Item::getVenue() {
	return _venue;
}

string Item::getCategory() {
	return _category;
}

Item::PriorityLevel Item::getPriority() {
	return _priority;
}

string Item::getPriorityInString() {
	switch(_priority) {
		case LOW: {
			return PRIORITY_LOW;
		}
		case MED: {
			return PRIORITY_MED;
		}
		case HIGH: {
			return PRIORITY_HIGH;
		}
		case INVALID: {
			return STRING_INVALID;
		}
		default: {
			return STRING_EMPTY;
		}
	}
}

bool Item::isDone() { 
	return _isDone;
}

string Item::getItemTypeInString(){

	switch (_itemType) {
		case EVENT: {
			return ITEM_TYPE_EVENT;
		}
		case DEADLINE: {
			return ITEM_TYPE_DEADLINE;
		}
		case TASK: {
			return ITEM_TYPE_TASK;
		}
		default: {
			return STRING_EMPTY;
		}
	}
}

int Item::getId() {
	return _id;
}

void Item::updateIdCounter(int lastIdUsed) {
	_idCounter = lastIdUsed + 1;
}

void Item::setTitle(string title) {
	_title = title;
}

void Item::setDescription(string description) {
	_description = description;
}

void Item::setStartDateTime(string startDateTimeStr) {
	struct tm startDateTime;
	time_t startDateTimeT = stoi(startDateTimeStr);

	localtime_s(&startDateTime, &startDateTimeT);
	setStartDateTime(startDateTime);
}

void Item::setStartDateTime(struct tm startDateTime) {
	_startDateTime = startDateTime;
	mktime(&_startDateTime);
}

void Item::setEndDateTime(string endDateTimeStr) {
	struct tm endDateTime;
	time_t endDateTimeT = stoi(endDateTimeStr);

	localtime_s(&endDateTime, &endDateTimeT);
	setEndDateTime(endDateTime);
}

void Item::setEndDateTime(struct tm endDateTime) {
	_endDateTime = endDateTime;
	mktime(&_endDateTime);
}

void Item::setStartDate(int day, int month) {
	time_t nowTime;
	tm nowTimeTM;
	int currMonth;
	int currDay;
	int yearToSet;
	
	time(&nowTime);
	localtime_s (&nowTimeTM, &nowTime);

	currDay = nowTimeTM.tm_mday;
	currMonth=nowTimeTM.tm_mon;
	yearToSet=nowTimeTM.tm_year;
	//if input month is earlier in the year, assume it is for next year
	if(month < currMonth){
		yearToSet++;
	}
	//if day has passed, assume it is for next year.
	else if(month == currMonth){
		if(day < currDay){
			yearToSet++;
		}
	}


	_startDateTime.tm_mday = day;
	_startDateTime.tm_mon = month;
	_startDateTime.tm_year = yearToSet;
	mktime(&_startDateTime); 
}

void Item::setEndDate(int day, int month) {
	
	time_t nowTime;
	tm nowTimeTM;
	int currMonth;
	int currDay;
	int yearToSet;
	time(&nowTime);
	localtime_s (&nowTimeTM, &nowTime);


	currDay = nowTimeTM.tm_mday;
	currMonth=nowTimeTM.tm_mon;
	yearToSet=nowTimeTM.tm_year;
	//if input month is earlier in the year, assume it is for next year
	if(month < currMonth){
		yearToSet++;
	}
	//if day has passed, assume it is for next year.
	else if(month == currMonth){
		if(day < currDay){
			yearToSet++;
		}
	}

	_endDateTime.tm_mday = day;
	_endDateTime.tm_mon = month;
	_endDateTime.tm_year = yearToSet;
	mktime(&_endDateTime);
}

void Item::setStartEndDateTimeAsNull(){
	time_t nowTime=0;
	localtime_s (&_startDateTime, &nowTime);
	localtime_s (&_endDateTime, &nowTime);

}

void Item::setStartDateAsToday(){
	time_t nowTime;
	tm nowTimeTM;

	time(&nowTime);
	localtime_s (&nowTimeTM, &nowTime);
	_startDateTime.tm_mday=nowTimeTM.tm_mday;
	_startDateTime.tm_wday=nowTimeTM.tm_wday;
	_startDateTime.tm_mon=nowTimeTM.tm_mon;
	_startDateTime.tm_yday=nowTimeTM.tm_yday;
	_startDateTime.tm_year=nowTimeTM.tm_year;
	mktime(&_startDateTime);
}

void Item::setEndDateAsToday(){
	time_t nowTime;
	tm nowTimeTM;

	time(&nowTime);
	localtime_s (&nowTimeTM, &nowTime);
	_endDateTime.tm_mday=nowTimeTM.tm_mday;
	_endDateTime.tm_wday=nowTimeTM.tm_wday;
	_endDateTime.tm_mon=nowTimeTM.tm_mon;
	_endDateTime.tm_yday=nowTimeTM.tm_yday;
	_endDateTime.tm_year=nowTimeTM.tm_year;
	mktime(&_endDateTime);
}

void Item::setStartTime(int hour, int min){
	_startDateTime.tm_hour = hour;
	_startDateTime.tm_min = min;
	mktime(&_startDateTime);

}

void Item::setEndTime(int hour, int min){
	_endDateTime.tm_hour = hour;
	_endDateTime.tm_min = min;
	mktime(&_endDateTime);

}

void Item::addToStartDate(int daysToAdd){
	setStartDateAsToday();
	_startDateTime.tm_mday += daysToAdd;
	mktime(&_startDateTime);
}
void Item::addToEndDate(int daysToAdd){
	setEndDateAsToday();
	_endDateTime.tm_mday += daysToAdd;
	mktime(&_endDateTime);
}
void Item::setVenue(string venue) {
	_venue = venue;
}

void Item::setCategory(string category) {
	_category = category;
}

void Item::setPriority(string priority) {
	if(priority == PRIORITY_HIGH) {
		setPriority(HIGH);
	} else if (priority == PRIORITY_MED) {
		setPriority(MED);
	} else if (priority == PRIORITY_LOW) {
		setPriority(LOW);
	} else {
		throw invalid_argument(MESSAGE_INVALID_ARGUMENT);
	}
}

void Item::setPriority(PriorityLevel priority) {
	_priority = priority;
}

void Item::toggleDone(string done) {
	if(!stoi(done)) {
		toggleDone();
	}
}

void Item::toggleDone() {
	if(_isDone) {
		_isDone = false;
	} else {
		_isDone = true;
	}
}

void Item::setItemType(string itemType){

	assert(itemType == ITEM_TYPE_EVENT || itemType == ITEM_TYPE_DEADLINE || itemType == ITEM_TYPE_TASK);

	if(itemType == ITEM_TYPE_EVENT) {
		setItemTypeEvent();
	} else if(itemType == ITEM_TYPE_DEADLINE) {
		setItemTypeDeadline();
	} else if(itemType == ITEM_TYPE_TASK) {
		setItemTypeTask();
	}
}

void Item::setItemTypeDeadline() {
	_itemType = DEADLINE;
}

void Item::setItemTypeEvent() {
	_itemType = EVENT;
}

void Item::setItemTypeTask() {
	_itemType = TASK;
}
