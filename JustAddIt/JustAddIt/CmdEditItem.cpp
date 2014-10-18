#include "stdafx.h"
#include "CmdEditItem.h"


CmdEditItem::CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, string newFieldInfo) {
	_itemAddr = *itemPtr;
	_itemPtr = itemPtr;
	_editFieldNumber = fieldNum;
	_newFieldInfo = newFieldInfo;
}

CmdEditItem::~CmdEditItem(void)
{
}

vector<string> CmdEditItem::execute() {

	switch (_editFieldNumber) {
	case 1: {
		ItemBank::editItemTitleInBank(_itemPtr, _newFieldInfo);
		break;
			}
	case 2: {
		ItemBank::editItemDescriptionInBank(_itemPtr, _newFieldInfo);
		break;

			}
	case 3: {
		//TODO: convert field info to date/time
		//ItemBank::editItemStartDateTimeInBank(_itemPtr, _newStartDateTime);
		//break;

			}
	case 4: {
		//TODO: convert field info to date/time
		//ItemBank::editItemEndDateTimeInBank(_itemPtr, _newEndDateTime);
		//break;

			}
	case 5: {
		ItemBank::editItemVenueInBank(_itemPtr, _newFieldInfo);
		break;

			}
	case 6: {
		ItemBank::editItemCategoryInBank(_itemPtr, _newFieldInfo);
		break;

			}
	case 7: {
		//ItemBank::editItemPriorityInBank(_itemPtr, _newPriority);
		//break;
			}
	default: {
		outputMessageStorage.push_back("An error has occcurred!");
			 }
	}

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructEditScreen(_itemAddr);
	outputMessageStorage.push_back("Item successfully edited!\n");

	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddr); 

	return outputMessageStorage;
}
