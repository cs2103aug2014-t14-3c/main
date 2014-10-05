#include "stdafx.h"
#include "Item.h"
#include <time.h>

int Item::_idCounter = 1;
//default start time/date is current time
//default end time/date is current time + 1h
Item::Item(void){

	time_t myTempTime;
	time(&myTempTime);	//set current time to myTempTime
	localtime_s (&_startDateTime, &myTempTime); //assign time_t var (myTempTime) to tm variable (_startDateTime)
	localtime_s (&_endDateTime, &myTempTime);
	_endDateTime.tm_hour++;		//add one more hour


	_id = _idCounter++;
}


Item::~Item(void)
{
}

string Item::getTitle() {
	return _title;
}

struct tm Item::getStartDateTime() {
	return _startDateTime;
}

struct tm Item::getEndDateTime() {
	return _endDateTime;
}

string Item::getVenue() {
	return _venue;
}

string Item::getCategory() {
	return _category;
}

PriorityLevel Item::getPriority() {
	return _priority;
}

bool Item::getIsDone() { 
	return _isDone;
}

void Item::updateIdCounter(int lastIdUsed) {
	_idCounter = lastIdUsed + 1;
}

void Item::setTitle(string title) {
	_title = title;
}

void Item::setStartDate(int day, int month) {
	_startDateTime.tm_mday = day;
	_startDateTime.tm_mon = month;
}
void Item::setStartTime(int hour){
	_startDateTime.tm_hour = hour;
}
void Item::setEndTime(int hour){
	_endDateTime.tm_hour = hour;
}
// void Item::setEndDate(time_type endDate) {}

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