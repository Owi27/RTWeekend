#pragma once
#include "Hittable.h"
	
class HittableList : public Hittable
{
public:
	std::vector<shared_ptr<Hittable>> _objects;

	HittableList();
	HittableList(shared_ptr<Hittable> object);
	
	void Add(shared_ptr<Hittable> object);

	void Clear();

	bool Hit(Ray& r, Interval interval, HitRecord& rec) const override;
};

