#include "PhysicsEvent.h"

PhysicsEvent::PhysicsEvent()
{

}

PhysicsEvent::PhysicsEvent(int id, bool stat, std::string typ, Vector3 pos, Vector3 rot, int len, int wid, int hei, pEvent spec, eCollider col, bool ply, bool enem)
{
	objId = id;

	isPlayer = ply;
	isEnemy = enem;

	isStatic = stat;
	type = typ;

	ePos = pos;
	eRot = rot;

	length = len;
	width = wid;
	height = hei;

	eSpec = spec;
	eCol = col;
}

PhysicsEvent::PhysicsEvent(int id, std::string typ, pEvent spec, Vector3 moveV)
{
	objId = id;

	type = typ;
	eSpec = spec;

	moveVec = moveV;
}

PhysicsEvent::PhysicsEvent(std::string typ, pEvent spec, Vector3 moveV)
{
	type = typ;
	eSpec = spec;

	moveVec = moveV;
}

PhysicsEvent::PhysicsEvent(std::string typ, pEvent spec, int id)
{
	type = typ;
	eSpec = spec;
	objId = id;
}

