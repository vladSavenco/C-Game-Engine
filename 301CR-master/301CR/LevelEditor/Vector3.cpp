#include "Vector3.h"

Vector3::Vector3()
{

}

Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

//transforms a vlad vector3 to an irrlicht vector3df
void Vector3::Vec3ToVec3df(Vector3 vec3, irr::core::vector3df& vec3df)
{
	vec3df.X = vec3.x;
	vec3df.Y = vec3.y;
	vec3df.Z = vec3.z;
}

Vector3 Vector3::addVec3(Vector3 vec1, Vector3 vec2)
{
	return Vector3(vec1.x+vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}


