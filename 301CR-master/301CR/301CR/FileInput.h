#pragma once
#include "Subsystem.h"
#include <fstream>

class FileInput :
	public Subsystem
{
private:

public:

	vector<char> fileVec;

	void WriteData();
	void ReadData();
};

