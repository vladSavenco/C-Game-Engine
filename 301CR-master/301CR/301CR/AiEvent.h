#pragma once
#include "Event.h"

enum aEvent { aAttack, aDie, aOff, aOn };

class AiEvent :
	public Event
{
public:
	int iD;
	aEvent eSpec;

	AiEvent();

	AiEvent(std::string myType,int id, aEvent spec);
};

