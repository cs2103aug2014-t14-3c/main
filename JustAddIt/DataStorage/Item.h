#pragma once

using namespace std;

enum PriorityLevel { LOW, MED, HIGH };

class Item {
private:
	
	static int _id;
	string _title;
	tm _startDate;
	tm _endDate;
	string _venue;
	vector<string> _categories;
	PriorityLevel _priority;
	bool _isMarked;

public:

	Item(string title);
	~Item();

	string getTitle();
	tm getStartDate();
	tm getEndDate();
	string getVenue();
	vector<string> getCategories();
	PriorityLevel getPriority();
	bool Item::getMarkedStatus();

	void setTitle(string title);
	void setStartDate(tm startDate);
	void setEndDate(tm endDate);
	void setVenue(string venue);
	void setCategories(vector<string> categories);
	void setPriority(PriorityLevel priority);

	void changeMarkedStatus();

};

