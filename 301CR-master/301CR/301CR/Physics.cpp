#include "Physics.h"

physx::PxShape* obj1;
physx::PxShape* obj2;

//dont knoiw what thhis is
std::vector<physx::PxVec3> gContactPositions;
std::vector<physx::PxVec3> gContactImpulses;

physx::PxFilterFlags contactReportFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
	physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = physx::PxPairFlag::eSOLVE_CONTACT | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
		| physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
		| physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;
	return physx::PxFilterFlag::eDEFAULT;
}


class ContactReportCallback : public physx::PxSimulationEventCallback
{
	void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count); }
	void onWake(physx::PxActor** actors, physx::PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onSleep(physx::PxActor** actors, physx::PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) { PX_UNUSED(pairs); PX_UNUSED(count); }
	void onAdvance(const physx::PxRigidBody* const*, const physx::PxTransform*, const physx::PxU32) {}
	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
	{
		PX_UNUSED((pairHeader));
		std::vector<physx::PxContactPairPoint> contactPoints;

		for (physx::PxU32 i = 0; i < nbPairs; i++)
		{
			physx::PxU32 contactCount = pairs[i].contactCount;
			if (contactCount)
			{
				contactPoints.resize(contactCount);
				pairs[i].extractContacts(&contactPoints[0], contactCount);

				for (physx::PxU32 j = 0; j < contactCount; j++)
				{
					gContactPositions.push_back(contactPoints[j].position);
					gContactImpulses.push_back(contactPoints[j].impulse);

					obj1 = pairs[i].shapes[0];
					obj2 = pairs[i].shapes[1];
				}
			}
		}
	}
};

ContactReportCallback gContactReportCallback;

//above this line there is a bunch of things needed for collision detection...... note: do not use physx



//Initialise physx
void Physics::InitialisePhysX()
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);

	if (!mFoundation)
	{
		throw("Foundation creation has failed");
	}

	mPvd = PxCreatePvd(*mFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
	mToleranceScale.length = 100;	//typical object length
	mToleranceScale.speed = 981;    //typical object speed, gravity*1s is a resonable choice
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);

	//setting up the scene
	//scene description is used to set up the scene settings
	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);		//allocating the number of threads we want to use
	sceneDesc.cpuDispatcher = mDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	//initialising the scene using the scene description
	mScene = mPhysics->createScene(sceneDesc);

	//setting up the pvd scene client
	physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
}

//mainly create the objects/physx actors
void Physics::InitialiseSimulation()
{
	mMaterial = mPhysics->createMaterial(10.0f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 1), *mMaterial);
	
	groundPlane->setName("physxObj");
	
	mScene->addActor(*groundPlane);
}

//events
//will check what specific type of graphic event we have
void Physics::CheckEvent(PhysicsEvent* ev)
{
	if (ev->eSpec == pSpawn)
	{
		resolveSpawnEvent(ev);
	}
	if (ev->eSpec == pEnemyMove)
	{
		resolveEnemyMoveEvent(ev);
	}
	if (ev->eSpec == pPlayerMove)
	{
		resolvePlayerMoveEvent(ev);
	}
}

//event resolvers
//spawnEvent
void Physics::resolveSpawnEvent(PhysicsEvent* ev)
{
	physx::PxVec3 pos = physx::PxVec3(ev->ePos.x, ev->ePos.y, ev->ePos.z);
	physx::PxVec3 rot;


	if (ev->eCol == box)
	{
		if (ev->isStatic == true)
		{
			addStaticPhysBox(pos, ev->length, ev->width, ev->height, ev->objId);
		}
		else
		{
			addDynamicPhysBox(pos, ev->length, ev->width, ev->height, ev->objId,ev->isPlayer,ev->isEnemy);
		}
	}
}

//basic movement resolver
void Physics::resolveEnemyMoveEvent(PhysicsEvent* ev)
{
	for (int i = 0; i < pEnemies.size(); i++)
	{
		if(ev->objId == pEnemies[i].physId)
		{
			physx::PxVec3 moveVec = physx::PxVec3(ev->moveVec.x, ev->moveVec.y, ev->moveVec.z);

			addVelocity(pEnemies[i].dShape, moveVec);
		}
	}
}

//resolve specific player movemet
void Physics::resolvePlayerMoveEvent(PhysicsEvent* ev)
{
	physx::PxVec3 moveVec = physx::PxVec3(ev->moveVec.x, ev->moveVec.y, ev->moveVec.z);

	addVelocity(pPlayer.dShape, moveVec);
}

//add velocity event
void Physics::addVelocity(physx::PxRigidDynamic* obj, physx::PxVec3 velocity)
{
	obj->setLinearVelocity(velocity);
}

//different colliders
void Physics::addStaticPhysBox(physx::PxVec3 pos,int len,int wid,int hei,int id)
{
	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxTransform p(physx::PxVec3(0));
	physx::PxTransform objPos(pos);

	physx::PxRigidStatic* cube = mPhysics->createRigidStatic(p.transform(objPos));
	physx::PxShape* box = mPhysics->createShape(physx::PxBoxGeometry(wid, hei, len), *mMaterial);

	box->setName("physxObj");

	cube->attachShape(*box);

	mScene->addActor(*cube);

	statPhysxObj.push_back(physObj(id,cube));

	box->release();
}

void Physics::addDynamicPhysBox(physx::PxVec3 pos, int len, int wid, int hei, int id, bool ply, bool enem)
{
	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxTransform p(physx::PxVec3(0));
	physx::PxTransform objPos(pos);

	physx::PxRigidDynamic* cube = mPhysics->createRigidDynamic(p.transform(objPos));
	physx::PxShape* box = mPhysics->createShape(physx::PxBoxGeometry(wid, hei, len), *mMaterial);

	if (ply == true)				//if it is player
	{
		box->setName("player");
	}
	else if (enem == true)			//if it is enemy
	{
		//std::stringstream ss;
		//ss << id;
		//std::string iD;
		//ss >> iD;

		box->setName("enemy");
	}
	else							//if it is normal obj
	{
		box->setName("physxObj");
	}

	cube->attachShape(*box);

	const physx::PxVec3* massCent = new physx::PxVec3(0,-5,0);

	physx::PxRigidBodyExt::updateMassAndInertia(*cube, 10.0f, massCent);

	mScene->addActor(*cube);

	delete(massCent);

	if (ply == true)				//if it is player
	{
		pPlayer = physObj(id, cube);
	}
	else if (enem == true)			//if it is enemy
	{
		pEnemies.push_back(physObj(id, cube,box));
	}
	else							//if it is normal obj
	{
		physxObj.push_back(physObj(id, cube));
	}

	box->release();
}

Physics::Physics()
{
	InitialisePhysX();
	InitialiseSimulation();
}

void Physics::Update()
{
	mScene->simulate(1.0f / 60.0f);
	mScene->fetchResults(true);

	//here we check is the 2 objects from the collision are the player an the enemy, if they are we will send an attack event from the enemy towards the player

	if (obj1 != 0 && obj2 != 0)
	{
		if (obj1->getName() == "enemy" && obj2->getName() == "player" || obj2->getName() == "enemy" && obj1->getName() == "player")
		{
			for (int i = 0; i < pEnemies.size(); i++)
			{
				if (pEnemies[i].box == obj1 || pEnemies[i].box == obj2)
				{
					Event* dat = new AiEvent("Aie", pEnemies[i].physId,aAttack);
					EQueue.push_back(dat);
				}
			}
		}
		obj1 = 0;
		obj2 = 0;
	}
}
