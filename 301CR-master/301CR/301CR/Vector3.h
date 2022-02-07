#pragma once

#include <irrlicht.h>

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float a, float b, float c);

	void Vec3ToVec3df(Vector3 vec3, irr::core::vector3df& vec3df);

	float Distance(Vector3 vec3a, Vector3 vec3b);

	void direction(Vector3 vec3a, Vector3 vec3b, Vector3& vec3c);
};

