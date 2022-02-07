#pragma once
#include "Subsystem.h"

struct LoadableAsset
{
public:
	std::string assetName;
	int assetId;

	LoadableAsset(std::string name, int id)
	{
		assetName = name;
		assetId = id;
	}
};
