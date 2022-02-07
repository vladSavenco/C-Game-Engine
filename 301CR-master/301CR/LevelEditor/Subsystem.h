#pragma once
#include <iostream>
#include <string>
#include <vector>

//structs
#include "LoadableAsset.h"
#include "GameObject.h"
#include "meshObj.h"

//misc
#include "Vector3.h"

//SFML
//input
#include <SFML/Window/Keyboard.hpp>
//audio
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

//Irrlicht
#include <irrlicht.h>
#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

//Irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//IMGUI namespace
using namespace IrrIMGUI;

//other namespaces
using namespace std;


//Struct and enum for the ui
//data for the event reciever
struct SAppContext
{
	IrrlichtDevice* device;
	s32             counter;
	IGUIListBox* listbox;
};

//Gui Controls
enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class Subsystem
{
public:
	Vector3 vladVector;

	std::string name;

	Subsystem();
	virtual void Start();
	virtual void Update();
};

