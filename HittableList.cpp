#include "pch.h"
#include "HittableList.h"

HittableList::HittableList()
{
}

HittableList::HittableList(shared_ptr<Hittable> object)
{
	Add(object);
}

void HittableList::Add(shared_ptr<Hittable> object)
{
	_objects.push_back(object);
}

void HittableList::Clear()
{
	_objects.clear();
}

bool HittableList::Hit(Ray& r, Interval interval, HitRecord& rec) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	float closestSoFar = interval._max;

	for (const auto& object : _objects)
	{
		if (object->Hit(r, Interval(interval._min, closestSoFar), tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	
	return hitAnything;
}