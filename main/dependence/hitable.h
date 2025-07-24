#ifndef HITABLEH
#define HITABLEH
#include "ray.h"

class material;

struct HitRecord {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr; // Pointer to the material of the hit object
};

class hitable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif