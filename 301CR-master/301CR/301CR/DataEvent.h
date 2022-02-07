#pragma once
#include "Event.h"

enum dEvent { dHealth, dPotion, dScore, dEnd };

class DataEvent :
	public Event
{
public:
	dEvent eSpec;

	int ammount;

	DataEvent();

	DataEvent(std::string myType, int amnt, dEvent spec);
};

