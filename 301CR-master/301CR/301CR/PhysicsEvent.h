#pragma once
#include "Event.h"

enum pEvent { pSpawn, pEnemyMove, pPlayerMove,pDeleteEnemy};

class PhysicsEvent :
    public Event
{
public:
	//id stuff
    int objId;
	pEvent eSpec;

	//physx stuff
    bool isStatic;

    //player
    bool isPlayer=false;

    //enemy
    bool isEnemy=false;

	//possition stuff
    Vector3 ePos;
    Vector3 eRot;

    //collider stuff
    int length;
    int width;
    int height;
	eCollider eCol;

	//physx movement/force stuff
	Vector3 moveVec;

    PhysicsEvent();

    //spawn event
    PhysicsEvent(int id,bool stat,std::string typ,Vector3 pos, Vector3 rot,int len,int wid,int hei,pEvent spec,eCollider col, bool ply, bool enem);

	//move event
	PhysicsEvent(int id, std::string typ, pEvent spec, Vector3 moveV);

    //move player
	PhysicsEvent(std::string typ,pEvent spec, Vector3 moveV);

	//delete enemy
	PhysicsEvent(std::string typ, pEvent spec, int id);
};

