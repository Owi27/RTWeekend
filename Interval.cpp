#include "pch.h"
#include "Interval.h"

Interval::Interval()
{
	_min = +INFINITY;
	_max = -INFINITY;
}

Interval::Interval(float min, float max)
{
	_min = min;
	_max = max;
}

float Interval::Size() const
{
	return _max - _min;
}

bool Interval::Contains(float x) const
{
	return _min <= x && x <= _max;
}

bool Interval::Surrounds(float x) const
{
	return _min < x && x < _max;
}

float Interval::Clamp(float x) const
{
	if (x < _min) return _min;
	if (x > _max) return _max;

	return x;
}
