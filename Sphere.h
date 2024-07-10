#pragma once
#include "Hittable.h"
class Sphere : public Hittable
{
public:
	Sphere(const vec3& center, float radius);

	bool Hit(Ray& r, float rayMin, float rayMax, HitRecord& rec) const override;

private:
	vec3 _center;
	float _radius;
};

