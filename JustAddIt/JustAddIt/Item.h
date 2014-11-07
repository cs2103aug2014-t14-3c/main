#pragma once
#include "stdafx.h"

#define MAX_SIZE 100

using namespace std;

class Item { 
public:
	enum PriorityLevel { LOW, MED, HIGH, INVALID };	
	enum ItemType { EVENT, DEADLINE, TASK };

	static const string STRING_EMPTY;
	static const string STRING_INVALID;

	static const string ITEM_TYPE_EVENT;
	static const string ITEM_TYPE_DEADLINE;
	static const string ITEM_TYPE_TASK;

	static const string PRIORITY_LOW;
	static const string PRIORITY_MED;
	static const string PRIORITY_HIGH;

	static const string IS_DONE;

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

public:
	Item(void);
	~Item(void);

	int getId();
	string getTitle();
	string getDescription();
	struct tm getStartDateTime();
	string getStartDateInString();
	struct tm getEndDateTime();
	string getEndDateInString();
	string getVenue();
	string getCategory();
	PriorityLevel getPriority();
	string getPriorityInString();
	bool isDone();
	string getItemTypeInString();

	bool isEvent();
	bool isDeadline();
	bool isTask();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	void setDescription(string description);
	
	void setStartDateTime(struct tm startDateTime);
	void setEndDateTime(struct tm endDateTime);
	void setStartDate(int day, int month);
	void setEndDate(int day, int month);
	void setStartEndDateTimeAsNull();
	void setStartDateAsToday();
	void setEndDateAsToday();
	void setStartTime(int hour, int min);
	void setEndTime(int hour, int min);
	void addToStartDate(int daysToAdd);
	void addToEndDate(int daysToAdd);
	
	void setVenue(string venue);
	
	void setCategory(string category);
	
	void setPriority(PriorityLevel priority);
	
	void toggleDone();
	
	void setItemType(string itemType);
	void setItemTypeDeadline();
	void setItemTypeEvent();
	void setItemTypeTask();
};

