#pragma once
#include "Vector3.h"

enum eCollider {box,sphere,plane};

struct GameObject
{
public:
	//id
	int objId = 0;
	bool isStatic;

	//for player
	bool isPlayer;

	//for enemy
	bool isEnemy;
	int aiId;

	//path data
	std::string objMesh;
	std::string objTexture;

	//transform data
	Vector3 objPosition = Vector3(0, 0, 0);
	Vector3 objScale = Vector3(0, 0, 0);
	Vector3 objRotation = Vector3(0, 0, 0);

	//collider data
	eCollider collider;
	float radius;
	float length;
	float width;
	float height;

	//default constructor
	GameObject(){}

	//normal non player/ai game object
	GameObject(Vector3 pos, Vector3 scl, Vector3 rot, int id, bool stat, std::string mesh, std::string texture,eCollider col,float rad,float len,float wid,float hei)
	{
		//obj id
		objId = id;
		isStatic = stat;

		//mesh and texture path data
		objMesh = mesh;
		objTexture = texture;

		//obj transform data
		objPosition = pos;
		objScale = scl;
		objRotation = rot;

		//collider data
		collider = col;
		radius = rad;
		length = len;
		width = wid;
		height = hei;
	}
	
	//player game object
	GameObject(Vector3 pos, Vector3 scl, Vector3 rot, int id,std::string mesh, std::string texture, eCollider col, float rad, float len, float wid, float hei)
	{
		//obj id
		objId = id;
		isPlayer = true;

		//mesh and texture path data
		objMesh = mesh;
		objTexture = texture;

		//obj transform data
		objPosition = pos;
		objScale = scl;
		objRotation = rot;

		//collider data
		collider = col;
		radius = rad;
		length = len;
		width = wid;
		height = hei;
	}

	//enemy game object
	GameObject(Vector3 pos, Vector3 scl, Vector3 rot, int id, std::string mesh, std::string texture, eCollider col, float rad, float len, float wid, float hei, int aid)
	{
		//obj id
		objId = id;
		isEnemy = true;
		aiId = aid;

		//mesh and texture path data
		objMesh = mesh;
		objTexture = texture;

		//obj transform data
		objPosition = pos;
		objScale = scl;
		objRotation = rot;

		//collider data
		collider = col;
		radius = rad;
		length = len;
		width = wid;
		height = hei;
	}
};
