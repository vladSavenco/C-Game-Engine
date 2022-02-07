#pragma once
#include <irrlicht.h>

struct meshObj
{
public:
	int meshId;
	irr::scene::IAnimatedMeshSceneNode* mesh;
	bool isEmpty = true;

	meshObj(){}

	meshObj(irr::scene::IAnimatedMeshSceneNode* node)
	{
		mesh = node;

		isEmpty = false;
	}

	void setMeshPos(Vector3 pos)
	{
		mesh->setPosition(irr::core::vector3df(pos.x, pos.y, pos.z));
	}

	void setMeshRot(Vector3 rot)
	{
		mesh->setRotation(irr::core::vector3df(rot.x, rot.y, rot.z));
	}

	void setMeshScale(Vector3 scal)
	{
		mesh->setScale(irr::core::vector3df(scal.x, scal.y, scal.z));
	}
};