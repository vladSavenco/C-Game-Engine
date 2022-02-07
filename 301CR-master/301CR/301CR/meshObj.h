#pragma once
#include <irrlicht.h>

struct meshObj
{
public:
	int meshId;
	irr::scene::IAnimatedMeshSceneNode* mesh;

	meshObj(){}

	meshObj(int id, irr::scene::IAnimatedMeshSceneNode* node)
	{
		meshId = id;
		mesh = node;
	}

	void setMeshPos(Vector3 pos)
	{
		mesh->setPosition(irr::core::vector3df(pos.x, pos.y, pos.z));
	}

	void setMeshRotation(Vector3 rot)
	{
		mesh->setRotation(irr::core::vector3df(rot.x, rot.y, rot.z));
	}
};