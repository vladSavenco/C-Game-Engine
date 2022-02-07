#pragma once
#include "Subsystem.h"

class Graphics :
	public Subsystem
{
public:
	//event queue
	std::vector<Event> EQueue;
	std::vector<Event>* EngineEQueue;

	//player data pointer
	playerData* pD;

	//create an irrlicht device
	IrrlichtDevice* device=NULL;

	//vector of spawned meshes
	std::vector<meshObj> grphObj;
	//player
	meshObj gPlayer;
	//enemies
	std::vector<meshObj>gEnemies;

	//create pointers to the different parts of the device
	IVideoDriver* driver = NULL;
	ISceneManager* smgr = NULL;
	IGUIEnvironment* guienv = NULL;

	//camera
	ICameraSceneNode* camera;
	vector3df cameraOffset = vector3df(0, 100, -60);

	//text
	IGUIStaticText* dogeyText;
	IGUIStaticText* fpsText;
	IGUIStaticText* HealthText;
	IGUIStaticText* potionText;
	IGUIStaticText* scoreText;

	void Start();

	//update irrlicht
	void Update();

	//start irrlicht
	void StartIrrlicht();

	//configures the window/ camera
	void ConfigureWindow();

	//edit text
	void configureText();

	//draws the scene
	void DrawScene();

	//spawn meshes
	void SpawnMesh(std::string meshFile, std::string textureFile, vector3df position, vector3df rotation, vector3df scale, int id, bool ply, bool enem);

	//checking for event
	void CheckEvent(GraphicsEvent* ev);

	//span event
	void resolveSpawnEvent(GraphicsEvent* ev);

	//deleting enemy
	void deleteEnemy(GraphicsEvent* ev);

	//updating camera position
	void updateCameraPos();
};

