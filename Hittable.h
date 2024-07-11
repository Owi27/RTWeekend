#pragma once
class HitRecord {
public:
	vec3 point;
	vec3 normal;
	float t;
	bool frontFace;

	void SetFaceNormal(Ray& r, const vec3& outwardNormal);
};

class Ray;

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(Ray& r, Interval interval, HitRecord& rec) const = 0;
};

