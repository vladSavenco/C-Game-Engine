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

//get the distance between 2 vector 3
float Vector3::Distance(Vector3 vec3a, Vector3 vec3b)
{
	float dist;

	dist = sqrt(pow(vec3b.x - vec3a.x, 2) + pow(vec3b.y - vec3a.y, 2) + pow(vec3b.z - vec3a.z, 2) * 1.0);

	return dist;
}

//get the direction between 2 vector3
void Vector3::direction(Vector3 vec3a, Vector3 vec3b, Vector3& vec3c)
{
	irr::core::vector3df vec = irr::core::vector3df(vec3a.x - vec3b.x, vec3a.y - vec3b.y, vec3a.z - vec3b.z);

	vec.normalize();

	vec3c.x = vec.X;
	vec3c.y = vec.Y;
	vec3c.z = vec.Z;
}
