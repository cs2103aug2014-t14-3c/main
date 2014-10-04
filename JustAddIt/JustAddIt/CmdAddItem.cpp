#include "stdafx.h"
#include "CmdAddItem.h"


CmdAddItem::CmdAddItem(Item item) {
	_itemAddr = &item;
}


CmdAddItem::~CmdAddItem(void)
{
}

void CmdAddItem::execute() {
	ItemBank::addToBank(*_itemAddr);
}