#include "GraphicsEvent.h"

GraphicsEvent::GraphicsEvent()
{
}

GraphicsEvent::GraphicsEvent(int id, std::string etype, gEvent spec, Vector3 pos, Vector3 rot, Vector3 scale, std::string meshPath, std::string texPath, bool ply, bool enem)
{
	objId = id;

	isPlayer = ply;

	isEnemy = enem;

	type = etype;
	eSpec = spec;

	ePos = pos;
	eRot = rot;
	eScale = scale;

	eMeshPath = meshPath;
	eTexPath = texPath;

}

GraphicsEvent::GraphicsEvent(std::string typ, gEvent spec, int id)
{
	type = typ;
	eSpec = spec;
	objId = id;
}
