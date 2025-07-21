#ifndef MATERIALH
#define MATERIALH
#include "ray.h"
#include "vec3.h"

struct HitRecord; // Forward declaration

class material {
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
};

#endif