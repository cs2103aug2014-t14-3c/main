#pragma once

using namespace std;

enum PriorityLevel { LOW, MED, HIGH, INVALID };


class Item { 
private:
	static int _idCounter;

	int _id;
	string _title;
	//time_type _startDate; // TODO: Include boost library
	//time_type _endDate;
	string _venue;
	vector<string> _categories;
	PriorityLevel _priority;
	bool _isDone;

public:
	Item(void);
	~Item(void);

	string getTitle();
	//time_type getStartDate();
	//time_type getEndDate();
	string getVenue();
	vector<string> getCategories();
	PriorityLevel getPriority();
	bool getIsDone();

	void updateIdCounter(int lastIdUsed);
	void setTitle(string title);
	// void setStartDate(time_type startDate);
	// void setEndDate(time_type endDate);
	void setVenue(string venue);
	void setCategory(string category);
	void setPriority(PriorityLevel priority);
	void toggleDone();
};

