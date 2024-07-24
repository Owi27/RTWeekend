#ifndef UTILITY_H
#define UTILITY_H

static float RandomFloat() //Returns a random real in [0,1).
{
	return rand() / (RAND_MAX + 1.0);
}

static float RandomFloat(float min, float max) // Returns a random real in [min,max).
{
	return min + (max - min) * RandomFloat();
}

static vec3 Random()
{
	return vec3{ RandomFloat(), RandomFloat(), RandomFloat() };
}

static vec3 Random(float min, float max)
{
	return vec3{ RandomFloat(min, max), RandomFloat(min, max) , RandomFloat(min, max) };
}

static vec3 RandomInUnitSphere()
{
	while (true)
	{
		vec3 p = Random(-1, 1);
		float f;
		pVec2D::Magnitude3F(p, f);

		if (f < 1)
		{
			return p;
		}
	}
}

static vec3 RandomNormalize()
{
	vec3 out;
	pVec2D::Normalize3F(RandomInUnitSphere(), out);
	return out;
}

static vec3 RandomOnHemisphere(const vec3& normal)
{
	vec3 onUnitSphere = RandomNormalize();

	float f;
	pVec2D::Dot3F(onUnitSphere, normal, f);

	if (f > 0.0)
	{
		return onUnitSphere;
	}
	else
	{
		return vec3{ -onUnitSphere.x, -onUnitSphere.y, -onUnitSphere.z };
	}
}
#endif UTILITY_H