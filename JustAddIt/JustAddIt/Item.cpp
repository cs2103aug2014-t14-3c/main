#include "stdafx.h"
#include "Item.h"
#include <time.h>

int Item::_idCounter = 1;

Item::Item(void){
	//default start time/date is current time
	//default end time/date is current time + 1h
	time_t myTempTime;
	time(&myTempTime);	//set current time to myTempTime
	localtime_s (&_startDateTime, &myTempTime); //assign time_t var (myTempTime) to tm variable (_startDateTime)
	localtime_s (&_endDateTime, &myTempTime);
	//_endDateTime.tm_hour++;		//add one more hour


	_id = _idCounter++;
}


Item::~Item(void)
{
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

string Item::getStartDateInString() {
	char tempArray[MAX_SIZE];
	if(&_startDateTime==NULL){
		return "";
	}
	else{
	strftime(tempArray, MAX_SIZE, "%A %d %b %I:%M%p", &_startDateTime);

	string str(tempArray);

	return str;
	}
}

struct tm Item::getEndDateTime() {
	return _endDateTime;
}

string Item::getEndDateInString() {
	char tempArray[MAX_SIZE];
	if(&_endDateTime==NULL){
		return "";
	}
	else{
		strftime(tempArray, MAX_SIZE, "%A %d %b %I:%M%p", &_endDateTime);

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
		case Item::PriorityLevel::LOW:
			return "Low";
		case Item::PriorityLevel::MED:
			return "Medium";
		case Item::PriorityLevel::HIGH:
			return "High";
		case Item::PriorityLevel::INVALID:
			return "Invalid";
		default:
			return "";
	}
}

bool Item::getIsDone() { 
	return _isDone;
}
string Item::getItemType(){
	return _itemType;
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

void Item::setStartDate(int day, int month) {
	_startDateTime.tm_mday = day;
	_startDateTime.tm_mon = month;
	mktime(&_startDateTime); 
}

void Item::setEndDate(int day, int month) {
	_endDateTime.tm_mday = day;
	_endDateTime.tm_mon = month;
	mktime(&_endDateTime);
}
void Item::setStartEndDateTimeAsToday(){
	time_t nowTime;
	time(&nowTime);
	localtime_s (&_startDateTime, &nowTime);
	localtime_s (&_endDateTime, &nowTime);
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
	_startDateTime.tm_mday += daysToAdd;
}
void Item::addToEndDate(int daysToAdd){
	_endDateTime.tm_mday += daysToAdd;
}
void Item::setVenue(string venue) {
	_venue = venue;
}

void Item::setCategory(string category) {
	_category = category;
}

void Item::setPriority(PriorityLevel priority) {
	_priority = priority;
}

void Item::toggleDone() {
	if(_isDone) {
		_isDone = false;
	} else {
		_isDone = true;
	}
}

void Item::setItemType(string itemType){
	_itemType = itemType;
}