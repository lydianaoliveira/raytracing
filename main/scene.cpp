#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

vec3 color(const Ray& r, hitable *world) {
    HitRecord rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * color(Ray(rec.p, target - rec.p), world);
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0); // Gradient background
    }
}


int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100; // Number of samples per pixel

    std::ofstream out("scene.ppm"); // Abre o arquivo para escrita
    if (!out) {
        std::cerr << "Erro ao abrir o arquivo para escrita!\n";
        return 1;
    }

    out << "P3\n" << nx << " " << ny << "\n255\n"; // Abre o arquivo para escrita

    hitable *list[2];
    list[0] = new Sphere(vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new HitableList(list, 2);

    camera cam;

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + ((float) rand() / RAND_MAX)) / float(nx);
                float v = float(j + ((float) rand() / RAND_MAX)) / float(ny);
                Ray r = cam.getRay(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            col /= float(ns); // Average color for the pixel
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); // Gamma correction
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close(); // Fecha o arquivo
    std::cout << "Arquivo PPM gerado com sucesso: scene.ppm\n";

    return 0;
}


