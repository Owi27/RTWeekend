#include "pch.h"
#include "Hittable.h"
#include "Ray.h"

void HitRecord::SetFaceNormal(Ray& r, const vec3& outwardNormal)
{
	float d;
	pVec2D::Dot3F(r.Direction(), outwardNormal, d);
	frontFace = d < 0;
	normal = frontFace ? outwardNormal : vec3{ -outwardNormal.x, -outwardNormal.y, -outwardNormal.z };
}