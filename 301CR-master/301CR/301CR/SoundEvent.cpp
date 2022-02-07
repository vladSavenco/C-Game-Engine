#include "SoundEvent.h"

SoundEvent::SoundEvent()
{
}

SoundEvent::SoundEvent(std::string myType,std::string name, bool iLoop, sEvent spec)
{
	sName = name;
	isLoop = iLoop;
	eSpec = spec;
	type = myType;
}
