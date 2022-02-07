#include "AssetLoader.h"

AssetLoader::AssetLoader()
{
	loadDirectories();

	loadLevelData(levelPath);

	loadScore(scorePath);

	initialiseAssets();
}

//load the directories path and the level path
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

	LuaRef scoreP = t["score"];

	LuaRef levelP = t["level"];

	meshPath = meshP.cast<std::string>();
	texturePath = textureP.cast<std::string>();
	soundsPath = soundsP.cast<std::string>();
	musicPath = musicP.cast<std::string>();

	scorePath = scoreP.cast<std::string>();

	levelPath = levelP.cast<std::string>();
}

//read all the level data from file
void AssetLoader::loadLevelData(std::string path)
{
	//creating vectors
	std::vector<std::string> elementList;

	std:vector<std::string> aiList;

	lua_State* M = luaL_newstate();
	luaL_dofile(M, path.c_str());
	luaL_openlibs(M);
	lua_pcall(M, 0, 0, 0);

	//LOADING THE LEVEL AND TERRAIN ASSETS, PLAYER AND ENEMIES
	
	elementList = getElements("assetList", M);

	LuaRef elementsRef = getGlobal(M, "assetList");
	
	//values to create a loadable mesh and its collider
		int objId;
		bool isStatic;

		bool isPlayer;

		bool isEnemy;
		int enemyTyp;

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

		isPlayer = obj["isPlayer"].cast<bool>();
		isEnemy = obj["isEnemy"].cast<bool>();
		enemyTyp = obj["enemyTyp"].cast<int>();

		objName = meshPath + obj["objMesh"].cast<std::string>();
		objTexture = texturePath + obj["objTex"].cast<std::string>();

		x = Pos["X"].cast<float>();
		y = Pos["Y"].cast<float>();
		z = Pos["Z"].cast<float>();
		objPos = Vector3(x, y, z);

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

		//checking if the obj is a player and adding it
		if (isPlayer == true)
		{
			player = GameObject(objPos, objScale, objRot, objId, objName, objTexture, collider, radius, length, width, height);
		}
		//checking if the obj is an enemy and adding it
		else if (isEnemy == true)
		{
			enemies.push_back(GameObject(objPos, objScale, objRot, objId, objName, objTexture, collider, radius, length, width, height, enemyTyp));
		}
		//adding the obj as a normal map obj
		else
		{
			levelObj.push_back(GameObject(objPos, objScale, objRot, objId, isStatic, objName, objTexture, collider, radius, length, width, height));
		}
	}

	//load the plane
	std::string planeMesh;
	std::string planeTex;

	LuaRef pl = getGlobal(M, "plane");

	planeMesh = pl["objMesh"].cast<std::string>();
	planeTex = pl["objTex"].cast<std::string>();

	Plane = GameObject(Vector3(0, 0, 0), Vector3(10, 10, 10), Vector3(0, 0, 0), 99, true, meshPath+planeMesh, texturePath+planeTex, box, 0, 0, 0, 0);

	//doing the samefor the ai behaviours
	aiList = getElements("aiList", M);
	LuaRef aiRef = getGlobal(M, "aiList");
	
	//values to create an enemyBehaviour
	int id;
	float dRange;
	int dammage;
	
	for (int i = 0; i < aiList.size(); i++)
	{
		LuaRef ai = aiRef[aiList[i]];
	
		id = ai["id"].cast<int>();
		dRange = ai["detectR"].cast<float>();
		dammage = ai["dammage"].cast<int>();
	
		eBehav.push_back(EnemyBehaviour(id, dRange, dammage));
	}

	//loading the player data
	int helt;
	int pot;
	int potEff;
	
	LuaRef ply = getGlobal(M, "playerData");
	helt = ply["health"].cast<int>();
	pot = ply["potions"].cast<int>();
	potEff = ply["potionEff"].cast<int>();

	plyData = playerData(helt, pot, potEff, 0);

	LuaRef thm = getGlobal(M, "mainTheme");
	mainTheme = thm["mus"].cast<std::string>();

	LuaRef stp = getGlobal(M, "stepSound");
	stepSound = stp["stp"].cast<std::string>();
}

void AssetLoader::loadScore(std::string path)
{
	std::vector<std::string> scoreList;
	
	lua_State* M = luaL_newstate();
	luaL_dofile(M, path.c_str());
	luaL_openlibs(M);
	lua_pcall(M, 0, 0, 0);
	
	scoreList = getElements("score", M);
	
	LuaRef scoreRef = getGlobal(M, "score");

	//values to load score
	int sc;
	std::string nm;

	for (int i = 0; i < scoreList.size(); i++)
	{
		LuaRef S = scoreRef[scoreList[i]];

		sc = S["sc"].cast<int>();
		nm = S["name"].cast<std::string>();

		score[i]=HighScore(sc, nm);
	}

	for (int i = 1; i < 5; i++)
	{
		HighScore key = score[i];
		int j = i - 1;

		while (key.score < score[j].score && j >= 0)
		{
			score[j + 1] = score[j];

			j--;
		}
		score[j + 1] = key;
	}
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

void AssetLoader::initialiseAssets()
{
	//spawn non ai/player map assets
	for (int i = 0; i <levelObj.size(); i++)
	{
		Event* grph = new GraphicsEvent(levelObj[i].objId, "Gfx", spawn,levelObj[i].objPosition, levelObj[i].objRotation, levelObj[i].objScale,levelObj[i].objMesh,levelObj[i].objTexture, false, false);
		EQueue.push_back(grph);

		Event* phys = new PhysicsEvent(levelObj[i].objId, levelObj[i].isStatic, "Phx", levelObj[i].objPosition, levelObj[i].objRotation, levelObj[i].length, levelObj[i].width, levelObj[i].height, pSpawn, levelObj[i].collider, false, false);
		EQueue.push_back(phys);
	}

	//spawn the player
	Event* grph = new GraphicsEvent(player.objId, "Gfx", spawn, player.objPosition, player.objRotation, player.objScale, player.objMesh, player.objTexture, true, false);
	EQueue.push_back(grph);

	Event* phys = new PhysicsEvent(player.objId, false, "Phx", player.objPosition, player.objRotation, player.length, player.width, player.height, pSpawn, player.collider, true, false);
	EQueue.push_back(phys);

	//spawn the plane with irrlicht
	Event* pln = new GraphicsEvent(Plane.objId, "Gfx", spawn, Plane.objPosition, Plane.objRotation, Plane.objScale, Plane.objMesh, Plane.objTexture, false, false);
	EQueue.push_back(pln);

	//spawn the enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		Event* grph = new GraphicsEvent(enemies[i].objId, "Gfx", spawn, enemies[i].objPosition, enemies[i].objRotation, enemies[i].objScale, enemies[i].objMesh, enemies[i].objTexture, false, true);
		EQueue.push_back(grph);

		Event* phys = new PhysicsEvent(enemies[i].objId, enemies[i].isStatic, "Phx", enemies[i].objPosition, enemies[i].objRotation, enemies[i].length, enemies[i].width, enemies[i].height, pSpawn, enemies[i].collider, false, true);
		EQueue.push_back(phys);
	}

	//send event to play the main theme
	Event* snd = new SoundEvent("Snd",mainTheme, true, sPlay);
	EQueue.push_back(snd);
}
