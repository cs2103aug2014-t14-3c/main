#pragma once
#include "stdafx.h"
#include "ItemBank.h"

class Command
{
public:
	Command(void);
	~Command(void);

	virtual void execute();
};

