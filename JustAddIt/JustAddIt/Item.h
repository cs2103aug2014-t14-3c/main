#pragma once
#include "stdafx.h"
using namespace std;

enum PriorityLevel { LOW, MED, HIGH, INVALID };


class Item { 
private:
	static int _idCounter;

	int _id;
	string _title;
	struct tm _startDateTime;
	struct tm _endDateTime;
	string _venue;
	string _category;
	PriorityLevel _priority;
	bool _isDone;

public:
	Item(void);
	~Item(void);

	string getTitle();
	struct tm getStartDateTime();
	struct tm getEndDateTime();
	string getVenue();
	string getCategory();
	PriorityLevel getPriority();
	bool getIsDone();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	void setStartDate(int day, int month);
	void setEndDate(int day, int month);
	void setStartTime(int hour, int min);
	void setEndTime(int hour, int min);
	// void setEndDate(time_type endDate);
	void setVenue(string venue);
	void setCategory(string category);
	void setPriority(PriorityLevel priority);
	void toggleDone();
};

