#pragma once
class Ray
{
public:
	Ray();
	Ray(const vec3& origin, const vec3& direction);

	const vec3& Origin() { return _origin; }
	const vec3& Direction() { return _direction; }

	vec3 At(float t);

private:
	vec3 _origin;
	vec3 _direction;
};

