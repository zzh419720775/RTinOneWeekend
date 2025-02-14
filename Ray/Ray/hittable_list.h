#pragma once


#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) {
		add(object);
	}


	void clear() {
		objects.clear();
	}
	void add(shared_ptr<hittable> obj) {
		objects.push_back(obj);
	}
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

public:
	std::vector<shared_ptr<hittable>> objects;

};

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = ray_t.max;

	for (const auto& object : objects) {
		if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}