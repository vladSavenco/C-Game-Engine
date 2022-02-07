#include "GameEngine.h"

//runs when the engine awakes
void GameEngine::Awake()
{
	cout << "Game engine awake" << endl;
}

//function builder
GameEngine::GameEngine()
{
	Awake();
}

//the start function where we call and start all the other engines
void GameEngine::Start()
{
	//PHYSICS STARTUP
	//--------------
	physics.name = "Physics System";	  
	physics.Start();

	//GRAPHICS STARTUP
	//---------------
	graphics.name = "Graphics System";	   
	graphics.Start();	
	graphics.pD = &assetLoader.plyData;

	//SOUND STARTUP
	//------------
	sounds.name = "Sound System";
	sounds.Start();

	//UI STARTUP
	//----------
	ui.name = "UI System";	
	ui.Start();		
	ui.stepSound = &assetLoader.stepSound;

	//AI STARRTUP
	//-----------
	ai.name = "Ai System";
	ai.Start();

	//sending player data
	ai.player = &assetLoader.player;
	//sending ai data
	ai.enemies = &assetLoader.enemies;
	//sending wenemy behaviour data
	ai.eBehav = assetLoader.eBehav;

	//GAME DATA STARTUP
	//-----------------
	gD.name = "Game Data";
	gD.pD = &assetLoader.plyData;

	for (int i = 0; i < 5; i++)
	{
		gD.score[i] = assetLoader.score[i];
	}

	gD.Start();
}

//function that add an event to the event queue
void GameEngine::ThrowEvent(Event* newE)
{
	EQueue.push_back(newE);
}

//functions to update the graphic pos of the objects based on the physics simulation
//we will always want to update those vectors (reason why they are not events)
void GameEngine::getUpdatedPhysPos()
{
	//updating non ai/player obj
	for (int i = 0; i < assetLoader.levelObj.size(); i++)
	{
		for (int j = 0; j < physics.physxObj.size(); j++)
		{
			if (assetLoader.levelObj[i].objId == physics.physxObj[j].physId)
			{
				assetLoader.levelObj[i].objPosition = physics.physxObj[j].returnDynVec3();

				assetLoader.levelObj[i].objRotation = physics.physxObj[j].returnDynQuateernionVec3();
			}
		}
	}

	//updating player
	assetLoader.player.objPosition = physics.pPlayer.returnDynVec3();
	assetLoader.player.objRotation = physics.pPlayer.returnDynQuateernionVec3();

	//updating enemies
	for (int i = 0; i < assetLoader.enemies.size(); i++)
	{
		for (int j = 0; j < physics.pEnemies.size(); j++)
		{
			if (assetLoader.enemies[i].objId == physics.pEnemies[j].physId)
			{
				assetLoader.enemies[i].objPosition = physics.pEnemies[j].returnDynVec3();

				assetLoader.enemies[i].objRotation = physics.pEnemies[j].returnDynQuateernionVec3();
			}
		}
	}
}

void GameEngine::setUpdateGraphPos()
{
	//updating non ai/player obj
	for (int i = 0; i < assetLoader.levelObj.size(); i++)
	{
		for (int j = 0; j < graphics.grphObj.size(); j++)
		{
			if (assetLoader.levelObj[i].objId == graphics.grphObj[j].meshId)
			{
				graphics.grphObj[j].setMeshPos(assetLoader.levelObj[i].objPosition);

				graphics.grphObj[j].setMeshRotation(assetLoader.levelObj[i].objRotation);
			}
		}
	}

	//updating player
	graphics.gPlayer.setMeshPos(assetLoader.player.objPosition);
	graphics.gPlayer.setMeshRotation(assetLoader.player.objRotation);

	//updating enemies
	for (int i = 0; i < assetLoader.enemies.size(); i++)
	{
		for (int j = 0; j < graphics.gEnemies.size(); j++)
		{
			if (assetLoader.enemies[i].objId == graphics.gEnemies[j].meshId)
			{
				graphics.gEnemies[j].setMeshPos(assetLoader.enemies[i].objPosition);

				graphics.gEnemies[j].setMeshRotation(assetLoader.enemies[i].objRotation);
			}
		}
	}
}

//checks the events that a subsystem is asking for and asigning them to the main event queue
void GameEngine::getEventsFromSubsystem(Subsystem sub)
{
	for (int i = 0; i < sub.EQueue.size(); i++)
	{
		ThrowEvent(sub.EQueue[i]);
	}

	sub.EQueue.clear();
}

//distributes events between the diffferent systems
void GameEngine::DistributeEvents()
{
	for (int i = 0; i < EQueue.size(); i++)
	{
		if ((*EQueue[i]).type == "Gfx")
		{
			//cout << "Its a graphics event!" << endl;
			graphics.CheckEvent((GraphicsEvent*)(EQueue[i]));

			delete(EQueue[i]);
		}

		if ((*EQueue[i]).type == "Phx")
		{
			//cout << "Its a physics event!" << endl;
			physics.CheckEvent((PhysicsEvent*)(EQueue[i]));

			delete(EQueue[i]);
		}

		if ((*EQueue[i]).type == "Snd")
		{
			sounds.CheckEvent((SoundEvent*)(EQueue[i]));

			delete(EQueue[i]);
		}

		if ((*EQueue[i]).type == "Dat")
		{
			gD.CheckEvent((DataEvent*)(EQueue[i]));

			delete(EQueue[i]);
		}

		if ((*EQueue[i]).type == "Aie")
		{
			ai.CheckEvent((AiEvent*)(EQueue[i]));

			delete(EQueue[i]);
		}

		if ((*EQueue[i]).type == "Stp")
		{
			isRunning = false;
		}
	}
	EQueue.clear();
}  

//the update function of the game engine
void GameEngine::Update()
{
	getEventsFromSubsystem(gD);

	//assetloader
	getEventsFromSubsystem(assetLoader);

	if (EQueue.empty() == false)
	{
		DistributeEvents();
	}

	//game data stuff
	gD.Update();

	//ui
	ui.Update();
	getEventsFromSubsystem(ui);

	//phisics
	physics.Update();
	getEventsFromSubsystem(physics);

	//after we do the physics checks for the update we will transfer all the new pos of the dynamic obj to the graphics
	getUpdatedPhysPos();
	setUpdateGraphPos();

	//graphics
	graphics.Update();

	//ai 
	ai.Update();
	getEventsFromSubsystem(ai);
}