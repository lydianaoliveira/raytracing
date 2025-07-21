#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
        vec3 u, v, w;
        
        float theta = vfov * M_PI / 180.0; // Convert degrees to radians
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;

        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0);
        lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
        horizontal = 2 * halfWidth * u;
        vertical = 2 * halfHeight * v;
    }
    Ray getRay(float s, float t) {return Ray(origin, lowerLeftCorner + s * horizontal + t * vertical - origin);};

    vec3 origin;
    vec3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
};

#endif // CAMERA_H