#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(const vec3& center, float radius)
{
	_center = center;
	_radius = radius;
}

bool Sphere::Hit(Ray& r, Interval interval, HitRecord& rec) const
{
	vec3 oc;
	float a, h, c;
	pVec2D::Subtract3F(_center, r.Origin(), oc);
	pVec2D::Magnitude3F(r.Direction(), a);
	pVec2D::Dot3F(r.Direction(), oc, h);
	pVec2D::Magnitude3F(oc, c);
	c -= _radius * _radius;

	float discriminant = h * h - a * c;

	if (discriminant < 0) return false;

	float sqrtD = sqrt(discriminant);

	//find nearest root that lies in acceptable range
	float root = (h - sqrtD) / a;

	if (!interval.Surrounds(root))
	{
		root = (h + sqrtD) / a;
		
		if (!interval.Surrounds(root))
		{
			return false;
		}
	}

	rec.t = root;
	rec.point = r.At(rec.t);

	vec3 outNormal;
	{
		vec3 v;
		pVec2D::Subtract3F(rec.point, _center, v);
		pVec2D::Scale3F(v, 1.f / _radius, outNormal);
	}
	rec.SetFaceNormal(r, outNormal);

	return true;
}
