#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

//events
#include "GraphicsEvent.h"
#include "PhysicsEvent.h"
#include "SoundEvent.h"
#include "DataEvent.h"
#include "AiEvent.h"
#include "HighScore.h"

//structs
#include "LoadableAsset.h"
#include "GameObject.h"
#include "meshObj.h"
#include "physObj.h"
#include "EnemyBehaviour.h"
#include "playerData.h"

//misc
#include "Vector3.h"

//SFML
//input
#include <SFML/Window/Keyboard.hpp>

//Klang 
//audio
#include <irrKlang.h>


//Irrlicht
#include <irrlicht.h>
//Irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//PhysX
#include <PxPhysicsAPI.h>

class Subsystem
{
public:
	Vector3 vladVector;

	vector<Event*>EQueue;

	std::string name;

	Subsystem();
	virtual void Start();
	virtual void Update();
};

