#pragma once
#include "Vector3.h"

enum eCollider {box,sphere,plane};

struct GameObject
{
public:
	//id
	int objId = 0;
	bool isStatic;

	bool isPlayer;
	bool isEnemy;

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

	GameObject(){}

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
};
