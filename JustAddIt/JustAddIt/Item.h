#pragma once

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

public:
	Item(void);
	~Item(void);

	string getTitle();
	string getDescription();
	struct tm getStartDateTime();
	struct tm getEndDateTime();
	string getVenue();
	string getCategory();
	PriorityLevel getPriority();
	bool getIsDone();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	void setDescription(string description);
	void setStartDate(int day, int month);
	void setStartTime(int hour);
	void setEndTime(int hour);
	// void setEndDate(time_type endDate);
	void setVenue(string venue);
	void setCategory(string category);
	void setPriority(PriorityLevel priority);
	void toggleDone();
};

