#include "AiEvent.h"

AiEvent::AiEvent()
{
}

AiEvent::AiEvent(std::string myType,int id, aEvent spec)
{
	type = myType;
	iD = id;
	eSpec = spec;
}
