#include "stdafx.h"
#include "CmdEditItem.h"

//general constructor
CmdEditItem::CmdEditItem(vector<Item*>::iterator bankPtr, int fieldNum, string newFieldInfo) {
	_itemAddr = *bankPtr;
	_bankPtr = bankPtr;
	_editFieldNumber = fieldNum;
	_newFieldInfo = newFieldInfo;
	_isEditField=true;
}
//constructor for editing time
CmdEditItem::CmdEditItem(vector<Item*>::iterator bankPtr, int fieldNum, tm newTimeInfo) {
	_itemAddr = *bankPtr;
	_bankPtr = bankPtr;
	_editFieldNumber = fieldNum;
	_newTimeInfo = newTimeInfo;
	_isEditField=true;
}
//constructor for selecting item
CmdEditItem::CmdEditItem(vector<Item*>::iterator bankPtr) {
	_itemAddr = *bankPtr;
	_bankPtr = bankPtr;
	//_editFieldNumber = fieldNum;
	//_newFieldInfo = newFieldInfo;
	_isEditField=false;
}
CmdEditItem::~CmdEditItem(void)
{
}

vector<string> CmdEditItem::execute() {
	if(_isEditField){
		switch (_editFieldNumber) {
		case 1: {
			ItemBank::editItemTitleInBank(_bankPtr, _newFieldInfo);
			break;
				}
		case 2: {
			ItemBank::editItemDescriptionInBank(_bankPtr, _newFieldInfo);
			break;

				}
		case 3: {

			ItemBank::editItemStartDateTimeInBank(_bankPtr, _newTimeInfo);
			break;

				}
		case 4: {

			ItemBank::editItemEndDateTimeInBank(_bankPtr, _newTimeInfo);
			break;

				}
				//case 5: {
				//	ItemBank::editItemVenueInBank(_itemPtr, _newFieldInfo);
				//	break;

				//		}
		case 5: {
			ItemBank::editItemPriorityInBank(_bankPtr, _newFieldInfo);
			break;
				}
		case 6: {
			ItemBank::editItemCategoryInBank(_bankPtr, _newFieldInfo);
			break;
				}
		default: {
			outputMessageStorage.push_back("An error has occcurred!");
				 }
		}
	}
	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructEditScreen(_itemAddr);
	//show success only when field is edited
	if(_isEditField){
		outputMessageStorage.push_back("Item successfully edited!\n");
	}
	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddr); 

	return outputMessageStorage;
}
