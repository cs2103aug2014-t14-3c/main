#pragma once

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
	vector<string> _categories;
	PriorityLevel _priority;
	bool _isDone;

public:
	Item(void);
	~Item(void);

	string getTitle();
	struct tm getStartDateTime();
	struct tm getEndDateTime();
	string getVenue();
	vector<string> getCategories();
	PriorityLevel getPriority();
	bool getIsDone();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	void setStartDate(int day, int month);
	void setStartTime(int hour);
	void setEndTime(int hour);
	// void setEndDate(time_type endDate);
	void setVenue(string venue);
	void setCategory(string category);
	void setPriority(PriorityLevel priority);
	void toggleDone();
};

