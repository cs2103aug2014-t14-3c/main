#include "stdafx.h"
#include "Item.h"

int Item::_id = 0;

Item::Item(string title) {
	_title = title;
	_id++;
	_isMarked = false;
}


Item::~Item()
{
}

string Item::getTitle() {
	return _title;
}

tm Item::getStartDate() {
	return _startDate;
}

tm Item::getEndDate() {
	return _endDate;
}

string Item::getVenue() {
	return _venue;
}

bool Item::getMarkedStatus() {
	return _isMarked;
}

string Item::getCategories() {
	return _category;
}

PRIORITY_LEVEL Item::getPriority() {
	return _priority;
}

void Item::setTitle(string title) {
	_title = title;
}
void Item::setStartDate(tm startDate) {
	_startDate = startDate;
}

void Item::setEndDate(tm endDate) {
	_endDate = endDate;
}

void Item::setVenue(string venue) {
	_venue = venue;
}

void Item::setCategory(string category) {
	_category = category;
}

void Item::setPriority(PRIORITY_LEVEL priority) {
	_priority = priority;
}

void Item::changeMarkedStatus() {
	if (_isMarked == false) {
		_isMarked = true;
	}
	else {
		_isMarked = false;
	}
}