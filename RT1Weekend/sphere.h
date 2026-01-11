#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

using namespace std;

class sphere : public hittable {
public:
	sphere(const point3& center, double radius) : center(center), radius(fmax(0, radius)) {}

	bool hit(const ray& r, double ray_min, double ray_max, hit_record& rec) const override {
		vec3 oc = center - r.origin();
		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), oc);
		auto c = oc.length_squared() - radius * radius;
		auto discriminant = h * h - a * c;

		if (discriminant < 0)
			return false;

		// Find closest root
		auto sqrtd = sqrt(discriminant);
		auto root = (h - sqrtd) / a;
		if (root <= ray_min || root >= ray_max) {
			root = (h + sqrtd) / a;
			if (root <= ray_min || root >= ray_max) {
				return false;
			}
		}

		rec.t = root;
		rec.p = r.at(root);
		auto outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		
		return true;
	}

private:
	point3 center;
	double radius;
};

#endif // !SPHERE_H
