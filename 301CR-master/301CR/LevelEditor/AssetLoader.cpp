#include "AssetLoader.h"

AssetLoader::AssetLoader()
{
	loadDirectories();

	levelObj = loadLevelData(levelPath);

	//testing the data read
	/*for (int i = 0; i < levelObj.size(); i++)
	{
		cout << levelObj[i].objId << endl;
		cout << levelObj[i].isStatic << endl;

		cout << levelObj[i].objMesh << endl;
		cout << levelObj[i].objTexture << endl;

		cout << levelObj[i].objPosition.x << "," << levelObj[i].objPosition.y << "," << levelObj[i].objPosition.z << endl;
		cout << levelObj[i].objRotation.x << "," << levelObj[i].objRotation.y << "," << levelObj[i].objRotation.z << endl;
		cout << levelObj[i].objScale.x << "," << levelObj[i].objScale.y << "," << levelObj[i].objScale.z << endl;

		cout << levelObj[i].collider << endl;
		cout << levelObj[i].radius << endl;
		cout << levelObj[i].length << endl;
		cout << levelObj[i].width << endl;
		cout << levelObj[i].height << endl;
	}*/
}

void AssetLoader::loadDirectories()
{
	lua_State* D = luaL_newstate();
	luaL_dofile(D, "Data/directories.lua");
	luaL_openlibs(D);
	lua_pcall(D, 0, 0, 0);

	LuaRef t = getGlobal(D, "directories");
	LuaRef meshP = t["mesh"];
	LuaRef textureP = t["texture"];
	LuaRef soundsP = t["sounds"];
	LuaRef musicP = t["music"];

	LuaRef levelP = t["level"];

	meshPath = meshP.cast<std::string>();
	texturePath = textureP.cast<std::string>();
	soundsPath = soundsP.cast<std::string>();
	musicPath = musicP.cast<std::string>();

	levelPath = levelP.cast<std::string>();
}

std::vector<GameObject> AssetLoader::loadLevelData(std::string path)
{
	//creating vectors
	std::vector<GameObject>objVec;
	std::vector<std::string> elementList;

	lua_State* M = luaL_newstate();
	luaL_dofile(M, path.c_str());
	luaL_openlibs(M);
	lua_pcall(M, 0, 0, 0);

	elementList = getElements("assetList", M);

	LuaRef elementsRef = getGlobal(M, "assetList");

	//values to create a loadable mesh and its collider
	int objId;
	bool isStatic;

	std::string objName;
	std::string objTexture;

	float x;
	float y;
	float z;

	Vector3 objPos;
	Vector3 objRot;
	Vector3 objScale;

	eCollider collider;
	int radius;
	int length;
	int width;
	int height;

	for (int i = 0; i < elementList.size(); i++)
	{
		LuaRef obj = elementsRef[elementList[i]];
		LuaRef Pos = obj["objPos"];
		LuaRef Rot = obj["objRot"];
		LuaRef Scale = obj["objScale"];
		LuaRef Col = obj["objCollider"];

		objId = obj["objId"].cast<int>();
		objName = meshPath+obj["objMesh"].cast<std::string>();
		objTexture = texturePath+obj["objTex"].cast<std::string>();

		x = Pos["X"].cast<float>();
		y = Pos["Y"].cast<float>();
		z = Pos["Z"].cast<float>();
		objPos = Vector3(x,y,z);

		x = Rot["X"].cast<float>();
		y = Rot["Y"].cast<float>();
		z = Rot["Z"].cast<float>();
		objRot = Vector3(x, y, z);

		x = Scale["X"].cast<float>();
		y = Scale["Y"].cast<float>();
		z = Scale["Z"].cast<float>();
		objScale = Vector3(x, y, z);

		

		//getting the collider type
		std::string coltype;
		if ((coltype = Col["type"].cast<std::string>()) == "box")
		{
			collider = box;
		}
		if ((coltype = Col["type"].cast<std::string>()) == "sphere")
		{
			collider = sphere;
		}
		if ((coltype = Col["type"].cast<std::string>()) == "plane")
		{
			collider = plane;
		}

		radius = Col["rad"].cast<int>();
		length = Col["len"].cast<int>();
		width = Col["wid"].cast<int>();
		height = Col["hei"].cast<int>();
		isStatic = Col["isStatic"].cast<bool>();

		objVec.push_back(GameObject(objPos, objScale, objRot, objId, isStatic, objName, objTexture, collider, radius, length, width, height));
	}

	return objVec;
}

//function provided by Elias Daler.
std::vector<std::string> AssetLoader::getElements(const std::string& tab, lua_State* L)
{
	std::string source =
		"function getElements(tab) "
		"s = \"\""
		"for k, v in pairs(_G[tab]) do "
		"    s = s..k..\"|\" "
		"    end "
		"return s "
		"end";

	luaL_loadstring(L, source.c_str());
	lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "getElements");
	lua_pushstring(L, tab.c_str());
	lua_pcall(L, 1, 1, 0);

	//going through the element string and separating the elements
	std::string ans = lua_tostring(L, -1);

	std::vector<std::string> elements;
	std::string temp = "";

	for (unsigned int i = 0; i < ans.size(); i++)
	{
		if (ans[i] != '|')
		{
			temp = temp + ans[i];
		}
		else
		{
			elements.push_back(temp);

			temp = "";
		}
	}

	//cleaning up
	int n = lua_gettop(L);
	lua_pop(L, 1);

	//return the element list
	return elements;
}
