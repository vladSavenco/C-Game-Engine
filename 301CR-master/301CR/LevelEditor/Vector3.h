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

	Vector3 addVec3(Vector3 vec1, Vector3 vec2);
};

