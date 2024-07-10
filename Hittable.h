#pragma once
class HitRecord {
public:
    vec3 point;
    vec3 normal;
    float t;
    bool frontFace;

    void SetFaceNormal(Ray& r, const vec3& outwardNormal)
    {
        float d;
        pVec2D::Dot3F(r.Direction(), outwardNormal, d);
        frontFace = (d < 0);
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Ray;

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(Ray& r, float rayMin, float rayMax, HitRecord& rec) const = 0;
};

