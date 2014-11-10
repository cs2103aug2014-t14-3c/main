//@author A0116781A
//@author A0128461H
#pragma once
#include "stdafx.h"

#define MAX_SIZE 100

#define STRING_EMPTY ""
#define STRING_INVALID "Invalid"

#define ITEM_TYPE_EVENT "event"
#define ITEM_TYPE_DEADLINE "deadline"
#define ITEM_TYPE_TASK "task"

#define PRIORITY_LOW "Low"
#define PRIORITY_MED "Medium"
#define PRIORITY_HIGH "High"

#define IS_DONE "0"

using namespace std;

class Item { 
public:
	
	enum PriorityLevel { LOW, MED, HIGH, INVALID };	
	enum ItemType { EVENT, DEADLINE, TASK };

	static const string MESSAGE_INVALID_ARGUMENT;
	static const string STRING_NULL;
	static const string STRING_NEGATIVE_ONE;

private:
	static int _idCounter;

	int _id;
	string _title;
	string _description;
	struct tm _startDateTime;
	struct tm _endDateTime;
	string _venue;
	string _category;
	PriorityLevel _priority;
	bool _isDone;
	ItemType _itemType;

	void setTime(int hour, int min, tm &date);
	void setDate(int day, int month, tm &date);
	void setDate(tm input, tm &output);
	

public:
	Item(void);
	~Item(void);

	vector<string>::iterator strToItem(vector<string>::iterator iter);
	
	void setStartDateTime(string startDateTimeStr);
	void setEndDateTime(string endDateTimeStr);
	void addToStartDate(int daysToAdd);
	void addToEndDate(int daysToAdd);

	void setStartDateTime(struct tm startDateTime);
	void setEndDateTime(struct tm endDateTime);
	void setStartDate(int day, int month);
	void setEndDate(int day, int month);
	void setStartTime(int hour, int min);
	void setEndTime(int hour, int min);
	void setStartEndDateTimeAsNull();
	void setStartDate();
	void setEndDate();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	void setDescription(string description);
	void setVenue(string venue);	
	void setCategory(string category);
	void setPriority(PriorityLevel priority);
	void setPriority(string priority);

	void setItemType(string itemType);
	void setItemTypeDeadline();
	void setItemTypeEvent();
	void setItemTypeTask();

	void toggleDone(string done);
	void toggleDone();

	int getId();
	string getTitle();
	string getDescription();
	struct tm getStartDateTime();
	time_t getStartDateTime_T();
	string getStartDateInString();
	struct tm getEndDateTime();
	time_t getEndDateTime_T();
	string getEndDateInString();
	string getVenue();
	string getCategory();
	PriorityLevel getPriority();
	string getPriorityInString();
	ItemType getItemType();
	string getItemTypeInString();

	bool isDone();
	bool isEvent();
	bool isDeadline();
	bool isTask();
};

