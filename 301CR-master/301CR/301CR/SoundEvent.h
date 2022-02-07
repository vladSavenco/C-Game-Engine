#pragma once
#include "Event.h"

enum sEvent{sPlay};

class SoundEvent :
    public Event
{
public:
    std::string sName;
    bool isLoop = false;
    sEvent eSpec;

    SoundEvent();

    SoundEvent(std::string myType,std::string name, bool iLoop, sEvent spec);
};

