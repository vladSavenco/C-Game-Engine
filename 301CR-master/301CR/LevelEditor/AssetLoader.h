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

    std::string levelPath;

public:
    std::vector<LoadableAsset> loadMesh;
    std::vector<LoadableAsset> loadTexture;
    std::vector<LoadableAsset> loadSound;
    std::vector<LoadableAsset> loadMusic;

    std::vector<GameObject> levelObj;

    AssetLoader();
    void loadDirectories();

    //load resources
    std::vector<GameObject> loadLevelData(std::string path);

    std::vector<std::string> getElements(const std::string& tab, lua_State* L);
};

