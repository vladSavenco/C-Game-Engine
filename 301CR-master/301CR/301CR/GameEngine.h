#pragma once
#include "Physics.h"
#include "Graphics.h"
#include "Sounds.h"
#include "FileInput.h"
#include "AssetLoader.h"
#include "UI.h"
#include "AiController.h"
#include "GameData.h"

#include "Event.h"

using namespace std;

class GameEngine
{
private:
	//main systems
	Physics physics;
	Graphics graphics;
	Sounds sounds;
	FileInput fileInput;
	AssetLoader assetLoader;
	UI ui;
	GameData gD;

	//gameplay
	AiController ai;

	void Awake();

	//event queue
	vector<Event*>EQueue;

public:
	bool isRunning = true;

	GameEngine();
	void Start();
	void Update();

	//void CreateMap();

	void ThrowEvent(Event* newE);

	void getUpdatedPhysPos();
	void setUpdateGraphPos();

	void getEventsFromSubsystem(Subsystem sub);

	void DistributeEvents();
};

