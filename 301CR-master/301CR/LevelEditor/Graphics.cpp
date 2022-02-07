#include "Graphics.h"

//start the graphics engine
void Graphics::Start()
{
    cout << "started Graphics system"<<endl;
}

void Graphics::Update()
{
    // Start main loop
    if (pDevice->run())
    {
        pDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        //call gui
        guiSpawnMesh();
        guiTransform();

        // render your scene
        pSceneManager->drawAll();

        // render the GUI
        drawGuiElements();

        //end scene
        pDriver->endScene();
    }
}

//function to add game object to scene at the preset position
void Graphics::SpawnMesh(std::string meshFile, std::string textureFile, vector3df position, vector3df rotation, vector3df scale)
{
    IAnimatedMesh* mesh = pSceneManager->getMesh(meshFile.c_str());
    if (!mesh)
    {
        pDevice->drop();
        cout << "no mesh was found" << endl;
    }
    else
    {
        cout << "mesh was added" << endl;

		IAnimatedMeshSceneNode* node = pSceneManager->addAnimatedMeshSceneNode(mesh, 0, NULL);

		node->setPosition(position);
		node->setRotation(rotation);
		node->setScale(scale);
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0, pDriver->getTexture(textureFile.c_str()));

        selectedObj = meshObj(node);
    }
}

//assign our gui ellements
void Graphics::createGuiElements()
{
    UserInterface = createIMGUI(pDevice, &EventReceiver);
}

//we draw the gui elements
void Graphics::drawGuiElements()
{
    UserInterface->drawAll();
}

//gui elements
//spawn mesh
void Graphics::guiSpawnMesh()
{
    //data to spawn the object
    //file name
    static char objName[128];
    //texture name
    static char textureName[128];

    //position in scene
    vector3df position;
    static float posX;
    static float posY;
    static float posZ;
    //rotation in scene
    vector3df rotation;
    static float rotX;
    static float rotY;
    static float rotZ;
    //scale in scene
    vector3df scale;
    static float scalX=1;
    static float scalY=1;
    static float scalZ=1;

    UserInterface->startGUI();

    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::Begin("Summon object");

    ImGui::InputText("Input object name", objName, IM_ARRAYSIZE(objName));
    ImGui::InputText("Input texture name", textureName, IM_ARRAYSIZE(textureName));
    //position
    ImGui::Text("Object Position");
    ImGui::InputFloat("Input posX", &posX, 1.0f, 1.0f);
    ImGui::InputFloat("Input posY", &posY, 1.0f, 1.0f);
    ImGui::InputFloat("Input posZ", &posZ, 1.0f, 1.0f);
    //rotation
    ImGui::Text("Object Rotation");
    ImGui::InputFloat("Input rotX", &rotX, 1.0f, 1.0f);
    ImGui::InputFloat("Input rotY", &rotY, 1.0f, 1.0f);
    ImGui::InputFloat("Input rotZ", &rotZ, 1.0f, 1.0f);
    //scale
    ImGui::Text("Object Scale");
    ImGui::InputFloat("Input scaleX", &scalX, 1.0f, 1.0f);
    ImGui::InputFloat("Input scaleY", &scalY, 1.0f, 1.0f);
    ImGui::InputFloat("Input scaleZ", &scalZ, 1.0f, 1.0f);


    if (ImGui::Button("Spawn", ImVec2(40, 20)))
    {
        if (selectedObj.isEmpty==true)
        {
            objNam = convertToString(objName);
            textureNam = convertToString(textureName);

            SpawnMesh("Data/Meshes/" + convertToString(objName), "Data/Textures/" + convertToString(textureName), vector3df(posX, posY, posZ), vector3df(rotX, rotY, rotZ), vector3df(scalX, scalY, scalZ));
        }
    }

    ImGui::End();
}

//edit element transform
void Graphics::guiTransform()
{
    if (selectedObj.isEmpty == false)
    {
        static int id;
        static int enemyId;
        //position in scene
        vector3df position;
        static float posX = selectedObj.mesh->getPosition().X;
        static float posY = selectedObj.mesh->getPosition().Y;
        static float posZ = selectedObj.mesh->getPosition().Z;
        //rotation in scene
        vector3df rotation;
        static float rotX = selectedObj.mesh->getRotation().X;
        static float rotY = selectedObj.mesh->getRotation().Y;
        static float rotZ = selectedObj.mesh->getRotation().Z;
        //scale in scene
        vector3df scale;
        static float scalX = selectedObj.mesh->getScale().X;
        static float scalY = selectedObj.mesh->getScale().Y;
        static float scalZ = selectedObj.mesh->getScale().Z;
        //obj data
        static bool isPlayer;
        static bool isEnemy;
        static bool isStatic;
        //texture
        static char textureName[128];

        ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(1200, 0));

        ImGui::Begin("Object Transform");

        //position
        ImGui::Text("Object Position");
        ImGui::InputFloat("Input posX", &posX, 1.0f, 1.0f);
        ImGui::InputFloat("Input posY", &posY, 1.0f, 1.0f);
        ImGui::InputFloat("Input posZ", &posZ, 1.0f, 1.0f);

        selectedObj.setMeshPos(Vector3(posX, posY, posZ));

        //rotation
        ImGui::Text("Object Rotation");
        ImGui::InputFloat("Input rotX", &rotX, 1.0f, 1.0f);
        ImGui::InputFloat("Input rotY", &rotY, 1.0f, 1.0f);
        ImGui::InputFloat("Input rotZ", &rotZ, 1.0f, 1.0f);

        selectedObj.setMeshRot(Vector3(rotX, rotY, rotZ));

        //scale
        ImGui::Text("Object Rotation");
        ImGui::InputFloat("Input scalX", &scalX, 1.0f, 1.0f);
        ImGui::InputFloat("Input scalY", &scalY, 1.0f, 1.0f);
        ImGui::InputFloat("Input scalZ", &scalZ, 1.0f, 1.0f);

        selectedObj.setMeshScale(Vector3(scalX, scalY, scalZ));

        //data
        ImGui::Checkbox("Player", &isPlayer);
        ImGui::Checkbox("Enemy", &isEnemy);
        ImGui::Checkbox("Static", &isStatic);

        ImGui::InputInt("Id", &id);
        ImGui::InputInt("Enemy Id", &enemyId);

        ImGui::InputText("Input texture name", textureName, IM_ARRAYSIZE(textureName));

        if (ImGui::Button("Set texture", ImVec2(80, 20)))
        {
            selectedObj.mesh->setMaterialTexture(0, pDriver->getTexture(("Data/Textures/" + convertToString(textureName)).c_str()));
        }

        if (ImGui::Button("Get Lua Data", ImVec2(80, 20)))
        {
            system("CLS");

            cout << "gameObj"<<id<<" = {" << endl;
            cout << "objId ="<<id<<", " << endl;

            cout << "isPlayer=" << isPlayer << "," << endl;
            cout << "isEnemy=" << isEnemy << "," << endl;
            cout << "enemyTyp=" << enemyId << "," << endl;

            cout << "ojMesh=" << "\"" << objNam << "\"," << endl;
            cout << "ojTex=" << "\"" << textureNam << "\"," << endl;

            cout << "objPos={" << endl;
            cout << "X=" << selectedObj.mesh->getAbsolutePosition().X << "," << endl;
            cout << "Y=" << selectedObj.mesh->getAbsolutePosition().Y << "," << endl;
            cout << "Z=" << selectedObj.mesh->getAbsolutePosition().Z << endl;
            cout << "}," << endl;

            cout << "objRot={" << endl;
            cout << "X=" << selectedObj.mesh->getRotation().X << "," << endl;
            cout << "Y=" << selectedObj.mesh->getRotation().Y << "," << endl;
            cout << "Z=" << selectedObj.mesh->getRotation().Z << endl;
            cout << "}," << endl;

            cout << "objScale={" << endl;
            cout << "X=" << selectedObj.mesh->getScale().X << "," << endl;
            cout << "Y=" << selectedObj.mesh->getScale().Y << "," << endl;
            cout << "Z=" << selectedObj.mesh->getScale().Z << endl;
            cout << "}," << endl;

            cout << "objCollider={" << endl;
            cout << "type=\"box\"," << endl;
            cout << "isStatic=" << isStatic<<"," << endl;
            cout << "rad=0," << endl;
            cout << "len=10," << endl;
            cout << "wid=5," << endl;
            cout << "hei=7" << endl;
            cout << "}" << endl;
            cout << "}" << endl;
        }

        ImGui::End();
    }
}

Graphics::Graphics()
{
    // Irrlicht OpenGL Settings
    SIrrlichtCreationParameters IrrlichtParams;
    IrrlichtParams.DriverType = video::EDT_OPENGL;
    IrrlichtParams.WindowSize = core::dimension2d<u32>(1920, 1080);
    IrrlichtParams.Bits = 32;
    IrrlichtParams.Fullscreen = false;
    IrrlichtParams.Stencilbuffer = true;
    IrrlichtParams.AntiAlias = 16;
    IrrlichtParams.Vsync = false;

    // Create standard event receiver for the IrrIMGUI
    IrrlichtParams.EventReceiver = &EventReceiver;

    // Create Irrlicht device
    pDevice = createDeviceEx(IrrlichtParams);

    pSceneManager = pDevice->getSceneManager();
    pDriver = pDevice->getVideoDriver();

    //SpawnMesh("./Data/Meshes/doge.obj", "./Data/Textures/doge.jpg", vector3df(0.0, 0.0, 0.0), vector3df(0.0, 180.0, 0.0), vector3df(1.0, 1.0, 1.0), 0);

    // add camera to the scene
    pSceneManager->addCameraSceneNode(0, core::vector3df(0, 0, 0), core::vector3df(0, 0, 5));

    createGuiElements();
}

std::string Graphics::convertToString(char* a)
{
    int size = sizeof(a) / sizeof(char);

    std::string s = "";

    for (int i = 0; i < size; i++) 
    {
        s = s + a[i];
    }
    return s;
}

