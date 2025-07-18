#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
    camera() {
        lowerLeftCorner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    Ray getRay(float u, float v) {return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical);};

    vec3 origin;
    vec3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
};

#endif // CAMERA_H