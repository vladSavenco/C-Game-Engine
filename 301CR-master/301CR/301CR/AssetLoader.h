#pragma once
#include "Subsystem.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge.h>

using namespace luabridge;

class AssetLoader :
    public Subsystem
{
private:
    std::string meshPath;
    std::string texturePath;
    std::string soundsPath;
    std::string musicPath;

    std::string scorePath;

    std::string levelPath;

public:
    //lvl assets/player/enemies
    std::vector<GameObject> levelObj;
    GameObject player;
    GameObject Plane;
    std::vector<GameObject> enemies;

    //loading in old scores
    HighScore score[5];

    //enemy behaviour
    std::vector<EnemyBehaviour> eBehav;

    //hp,potion,score
    playerData plyData;

    //sounds
    std::string mainTheme;
    std::string stepSound;



    //constructor
    AssetLoader();

    //loading the directories locations
    void loadDirectories();

    //load resources
    void loadLevelData(std::string path);

    void loadScore(std::string path);

    //gets elements from a lua list
    std::vector<std::string> getElements(const std::string& tab, lua_State* L);

    //sends events to initialise the map, the player and the enemies
    void initialiseAssets();
};

