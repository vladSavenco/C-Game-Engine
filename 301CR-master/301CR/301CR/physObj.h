#pragma once
#include <PxPhysicsAPI.h>
#include <irrlicht.h>

struct physObj
{
public:
	int physId;
	physx::PxRigidDynamic* dShape=NULL;
	physx::PxRigidStatic* sShape=NULL;

	physx::PxShape* box;

	physObj(){}

	physObj(int id, physx::PxRigidDynamic* obj)
	{
		physId = id;
		dShape = obj;
	}

	physObj(int id, physx::PxRigidDynamic* obj, physx::PxShape* bo)
	{
		physId = id;
		dShape = obj;
		box = bo;
	}

	physObj(int id, physx::PxRigidStatic* obj)
	{
		physId = id;
		sShape = obj;
	}

	//return vec3 of the position
	Vector3 returnDynVec3()
	{
		return Vector3(dShape->getGlobalPose().p.x, dShape->getGlobalPose().p.y, dShape->getGlobalPose().p.z);
	}

	//returns the vec3 of the orientation
	//this thing needs the include irrlicht to function and i did want to put it somewhere else but i really did not know where to put it
	Vector3 returnDynQuateernionVec3()
	{
		irr::core::quaternion objRot = irr::core::quaternion(dShape->getGlobalPose().q.x, dShape->getGlobalPose().q.y, dShape->getGlobalPose().q.z, dShape->getGlobalPose().q.w);
		
		objRot.normalize();

		irr::core::vector3df newEulerVec;

		objRot.toEuler(newEulerVec);

		newEulerVec = newEulerVec * irr::core::RADTODEG;

		return Vector3(newEulerVec.X, newEulerVec.Y, newEulerVec.Z);
	}
};