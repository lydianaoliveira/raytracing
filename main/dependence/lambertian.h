#include "material.h"
#include "vec3.h"
#include "ray.h"


class lambertian : public material {
public:
    lambertian(const vec3& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};
