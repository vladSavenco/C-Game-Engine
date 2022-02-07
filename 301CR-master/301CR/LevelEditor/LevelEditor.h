#pragma once

#include "Graphics.h"
#include "AssetLoader.h"

using namespace std;

class LevelEditor
{
private:

	Graphics graphics;
	AssetLoader assetLoader;

	void Awake();

public:
	LevelEditor();

	void Start();
	void Update();

	void CreateMap();

};
