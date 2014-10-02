#pragma once

using namespace std;

enum PRIORITY_LEVEL { LOW, MED, HIGH };

class Item {
private:
	
	static int _id;
	string _title;
	tm _startDate; // TODO: Change type to boost library date
	tm _endDate; // TODO: Change type to boost library date
	string _venue;
	string _category;
	PRIORITY_LEVEL _priority;
	bool _isMarked;

public:

	Item(string title);
	~Item();

	string getTitle();
	tm getStartDate();
	tm getEndDate();
	string getVenue();
	string getCategories();
	PRIORITY_LEVEL getPriority();
	bool getMarkedStatus();

	void setTitle(string title);
	void setStartDate(tm startDate);
	void setEndDate(tm endDate);
	void setVenue(string venue);
	void setCategory(string category);
	void setPriority(PRIORITY_LEVEL priority);
	void changeMarkedStatus();

};