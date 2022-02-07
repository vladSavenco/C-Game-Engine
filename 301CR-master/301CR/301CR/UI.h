#pragma once
#include "Subsystem.h"

class UI :
	public Subsystem
{
public:
	std::string* stepSound;

	Vector3 moveVec = Vector3(0.0, 0.0, 0.0);

	virtual void Update();
};

