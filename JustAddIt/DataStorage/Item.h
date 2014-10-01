#pragma once

using namespace std;

enum PriorityLevel { LOW, MED, HIGH };

class Item {
private:
	
	static int _id;
	static string _title;
	static tm _startDate;
	static tm _endDate;
	static string _venue;
	static string _category;
	static PriorityLevel _priority;
	static bool _isMarked;

public:

	Item(string title);
	~Item();

	static string getTitle();
	static tm getStartDate();
	static tm getEndDate();
	static string getVenue();
	static string getCategory();
	static PriorityLevel getPriority();
	static bool Item::getMarkedStatus();

	static void setTitle(string title);
	static void setStartDate(tm startDate);
	static void setEndDate(tm endDate);
	static void setVenue(string venue);
	static void setCategory(string category);
	static void setPriority(PriorityLevel priority);
	void changeMarkedStatus();

};

