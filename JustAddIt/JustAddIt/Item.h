#pragma once
#include "stdafx.h"

#define MAX_SIZE 100

using namespace std;

class Item { 
public:
	enum PriorityLevel { LOW, MED, HIGH, INVALID };	

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
	string _itemType;

public:
	Item(void);
	~Item(void);

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
	bool getIsDone();
	string getItemType();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	void setDescription(string description);
	void setStartDateTime(struct tm startDateTime);
	void setEndDateTime(struct tm endDateTime);
	void setStartDate(int day, int month);
	void setEndDate(int day, int month);
	void setStartEndDateTimeAsToday();
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
};

