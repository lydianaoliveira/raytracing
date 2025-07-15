#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct HitRecord {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif