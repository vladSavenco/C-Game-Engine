#pragma once
#include "Subsystem.h"

#include <fstream>

#include <windows.h>

//define
//this basically takes the size of a character array and defines it based on the input from the input text box, i think
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

class Graphics :
	public Subsystem
{
public:

	//data to spawn the object
	   //file name
	std::string objNam;
	//texture name
	std::string textureNam;

	//create an irrlicht device
	IrrlichtDevice* device=NULL;

	//vector of spawned meshes
	std::vector<meshObj> grphObj;

	meshObj selectedObj;

	//IRRLICHT WITH IRRIMGUI STUFF

	//IrrIrrlicht pointers
	scene::ISceneManager* pSceneManager;
	video::IVideoDriver* pDriver;


	//irrlicht device
	IrrlichtDevice* pDevice;
	//event reciever
	CIMGUIEventReceiver EventReceiver;

	//gui
	//import editor
	IIMGUIHandle* UserInterface;

	//levelObjArray
	//stuff that needs to be outputed to the file
	std::vector<GameObject> levelObj;

	//FUNCTIONS
	Graphics();

	void Start();
	
	void Update();
	
	void SpawnMesh(std::string meshFile,std::string textureFile, vector3df position, vector3df rotation, vector3df scale);

	//gui
	void createGuiElements();
	void drawGuiElements();

	//gui elements
	void guiSpawnMesh();
	void guiTransform();

	//misc
	std::string convertToString(char* a);
};