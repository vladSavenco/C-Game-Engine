#pragma once
#include "Subsystem.h"

class Physics :
	public Subsystem
{
public:


	//vector that holds the dynamic physics objects
	std::vector<physObj>physxObj;
	//vector that holds the static physics objects
	std::vector<physObj>statPhysxObj;
	//player
	physObj pPlayer;
	//enemies
	std::vector<physObj>pEnemies;

	//variables
	physx::PxDefaultAllocator mDefaultAllocatorCallback;
	physx::PxDefaultErrorCallback mDefaultErrorCallback;
	physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
	physx::PxTolerancesScale mToleranceScale;
	//setings
	physx::PxFoundation* mFoundation = NULL;
	//core
	physx::PxPhysics* mPhysics = NULL;
	//scenes
	physx::PxScene* mScene = NULL;
	physx::PxMaterial* mMaterial = NULL;
	//physX visual debugger
	physx::PxPvd* mPvd = NULL;

	//initialise physX
	void InitialisePhysX();

	//create physX simulation
	void InitialiseSimulation();

	//events
	void CheckEvent(PhysicsEvent* ev);

	//spawn event
	void resolveSpawnEvent(PhysicsEvent* ev);

	//enemy move event
	void resolveEnemyMoveEvent(PhysicsEvent* ev);
	//player move event
	void resolvePlayerMoveEvent(PhysicsEvent* ev);

	//add velocity
	void addVelocity(physx::PxRigidDynamic* obj, physx::PxVec3 velocity);

	//function to initialise physx obj
	//box
	void addStaticPhysBox(physx::PxVec3 pos, int len, int wid, int hei, int id);
	void addDynamicPhysBox(physx::PxVec3 pos, int len, int wid, int hei, int id, bool ply, bool enem);

	//run simulation

	//constructor
	Physics();

	//update function
	void Update() override;
};

