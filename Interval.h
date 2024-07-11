#pragma once
class Interval
{
public:
	float _min, _max;

	Interval();
	Interval(float min, float max);

	float Size() const;
	bool Contains(float x) const;
	bool Surrounds(float x) const;
	float Clamp(float x) const;

	static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+INFINITY, -INFINITY);
const Interval Interval::universe = Interval(-INFINITY, +INFINITY);