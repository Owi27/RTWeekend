#include "pch.h"
#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(const vec3& origin, const vec3& direction)
{
	_origin = origin;
	_direction = direction;
}

vec3 Ray::At(float t)
{
    vec3 out;
    pVec2D::Scale3F(_direction, t, out);
    pVec2D::Add3F(_origin, out, out);
   
    return out;
}
