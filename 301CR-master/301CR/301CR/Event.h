#pragma once
#include <iostream>
#include <vector>

#include "Vector3.h"
#include "GameObject.h"

using namespace std;

class Event
{
public:
	std::string type = "undefined";

	Event();
	Event(std::string myType);
};

