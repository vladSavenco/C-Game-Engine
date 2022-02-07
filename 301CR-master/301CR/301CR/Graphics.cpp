#include "Graphics.h"

//start the graphics engine
void Graphics::Start()
{
    cout << "started Graphics system"<<endl;

    StartIrrlicht();

    ConfigureWindow();
}

void Graphics::Update()
{
    DrawScene();

    updateCameraPos();
}

void Graphics::StartIrrlicht()
{
    //configure the irrlicht device we declared in the header
    device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1280, 720), 16,
        false, false, false, 0);

    //check if the device was created
    if (!device)
    {
        cout << "Irrlicht device was not created" << endl;
    }
    else
    {
        cout << "created Irrlicht device" << endl;
    }

    //set window caption
    device->setWindowCaption(L"TheDodgey Engine");

    //configure the pointers we declared in the header
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
}

//will run the device in a loop so everything updates
void Graphics::DrawScene()
{
    if (device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(255, 100, 101, 140));

            smgr->drawAll();

            configureText();

            guienv->drawAll();

            driver->endScene();
        }
        else
        {
            device->yield();
        }
    }
}

//function to add game object to scene at the preset position
void Graphics::SpawnMesh(std::string meshFile, std::string textureFile, vector3df position, vector3df rotation, vector3df scale,int id,bool ply,bool enem)
{
    IAnimatedMesh* mesh = smgr->getMesh(meshFile.c_str());
    if (!mesh)
    {
        device->drop();
        cout << "no mesh was found" << endl;
    }
    else
    {
        cout << "mesh was added" << endl;

		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh, 0, NULL);

		node->setPosition(position);
		node->setRotation(rotation);
		node->setScale(scale);
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0, driver->getTexture(textureFile.c_str()));

        if (ply == true)                    //if it is player
        {
            gPlayer = meshObj(id, node);
        }
        else if (enem == true)              //if it is enemy
        {
            gEnemies.push_back(meshObj(id, node));
        }
        else                                //if it is neither
        {
            grphObj.push_back(meshObj(id, node));
        }
    }
}

//will check what specific type of graphic event we have
void Graphics::CheckEvent(GraphicsEvent* ev)
{
    if (ev->eSpec == spawn)
    {
        resolveSpawnEvent(ev);
    }
	if (ev->eSpec == deleteObj)
	{
		deleteEnemy(ev);
	}
}

//events
//spawn event
void Graphics::resolveSpawnEvent(GraphicsEvent* ev)
{
    vector3df pos;
    vector3df rot;
    vector3df scale;

    vladVector.Vec3ToVec3df(ev->ePos, pos);
    vladVector.Vec3ToVec3df(ev->eRot, rot);
    vladVector.Vec3ToVec3df(ev->eScale, scale);

    SpawnMesh(ev->eMeshPath, ev->eTexPath, pos, rot, scale,ev->objId,ev->isPlayer,ev->isEnemy);
}

void Graphics::deleteEnemy(GraphicsEvent* ev)
{
	for (int i = 0; i < gEnemies.size(); i++)
	{
		if (gEnemies[i].meshId == ev->objId)
		{
			smgr->addToDeletionQueue(gEnemies[i].mesh);

			gEnemies.erase(gEnemies.begin() + i);
		}
	}
}

//updates the camera position
void Graphics::updateCameraPos()
{
    camera->setPosition(vector3df(gPlayer.mesh->getAbsolutePosition().X, 0, gPlayer.mesh->getAbsolutePosition().Z)+cameraOffset);

    camera->setTarget(gPlayer.mesh->getAbsolutePosition());
}

//creates the window
void Graphics::ConfigureWindow()
{
    //adds static text
    dogeyText = guienv->addStaticText(L"Dogey Engine is powered by questionable Technologies", rect<s32>(10, 10, 260, 22), false);
    fpsText = guienv->addStaticText(L"d", rect<s32>(1000, 10, 1260, 22), false);
    HealthText = guienv->addStaticText(L"d", rect<s32>(10, 22, 260, 34), false);
    potionText = guienv->addStaticText(L"d", rect<s32>(10, 34, 260, 46), false);
    scoreText = guienv->addStaticText(L"d", rect<s32>(10, 46, 260, 58), false);

    //adding a camera
    camera = smgr->addCameraSceneNode();

    //camera settings
    irr::f32 farPlane = 10000000;
    irr::f32 nearPlane = 10;
    camera->setFarValue(farPlane);
    camera->setNearValue(nearPlane);
}

//to update text
void Graphics::configureText()
{
    core::stringw hlt = L"Health: ";
    hlt += pD->playerHealth;

    core::stringw pot = L"Potions: ";
    pot += pD->healthPotions;

    core::stringw scr = L"Score: ";
    scr += pD->playerScore;

    core::stringw fps = L"FPS: ";
    fps += driver->getFPS();

    HealthText->setText(hlt.c_str());
    potionText->setText(pot.c_str());
    scoreText->setText(scr.c_str());

    fpsText->setText(fps.c_str());
}


