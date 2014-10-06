#include "stdafx.h"
#include "CmdEditItem.h"


CmdEditItem::CmdEditItem(vector<Item>::iterator itemPtr) {
	_itemPtr = itemPtr;
	int _editFieldNumber = NULL;
	string _newTitle = NULL;
	//struct tm _newStartDateTime = NULL;
	//struct tm _newEndDateTime = NULL;
	string _newVenue = NULL;
	string _newCategory = NULL;
	//PriorityLevel _newPriority = NULL;
}


CmdEditItem::~CmdEditItem(void)
{
}

vector<string> CmdEditItem::execute() {
	outputMessageStorage.clear();

	switch (_editFieldNumber) {
	case 1: {
		ItemBank::editItemTitleInBank(_itemPtr, _newTitle);
		break;
			}
	case 2: {
		//ItemBank::editItemStartDateTimeInBank(_itemPtr, _newStartDateTime);
		break;
			}
	case 3: {
		//ItemBank::editItemEndDateTimeInBank(_itemPtr, _newEndDateTime);
		break;
			}
	case 4: {
		ItemBank::editItemVenueInBank(_itemPtr, _newVenue);
		break;
			}
	case 5: {
		ItemBank::editItemCategoryInBank(_itemPtr, _newCategory);
		break;
			}
	case 6: {
		//ItemBank::editItemPriorityInBank(_itemPtr, _newPriority);
		break;
			}
	default: {
		outputMessageStorage.push_back("An error has occcurred!");
			 }
	}

	return outputMessageStorage;
}