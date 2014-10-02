#pragma once

using namespace std;

enum PRIORITY_LEVEL { LOW, MED, HIGH };

class Item {
private:
	
	static int _id;
	static string _title;
	static tm _startDate;
	static tm _endDate;
	static string _venue;
	static string _category;
	static PRIORITY_LEVEL _priority;
	static bool _isMarked;

public:

	Item(string title);
	~Item();

	static string getTitle();
	static tm getStartDate();
	static tm getEndDate();
	static string getVenue();
	static string getCategory();
	static PRIORITY_LEVEL getPriority();
	static bool Item::getMarkedStatus();

	static void setTitle(string title);
	static void setStartDate(tm startDate);
	static void setEndDate(tm endDate);
	static void setVenue(string venue);
	static void setCategory(string category);
	static void setPriority(PRIORITY_LEVEL priority);
	void changeMarkedStatus();

};