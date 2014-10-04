#include "stdafx.h"
#include "Item.h"

int Item::_idCounter = 1;

Item::Item(void)
{
	_id = _idCounter++;
}


Item::~Item(void)
{
}

string Item::getTitle() {
	return _title;
}

//time_type Item::getStartDate() {}

//time_type Item::getEndDate() {}

string Item::getVenue() {
	return _venue;
}

vector<string> Item::getCategories() {
	return _categories;
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

// void Item::setStartDate(time_type startDate) {}

// void Item::setEndDate(time_type endDate) {}

void Item::setVenue(string venue) {
	_venue = venue;
}

void Item::setCategory(string category) { // TODO: remove category function
	_categories.push_back(category);
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