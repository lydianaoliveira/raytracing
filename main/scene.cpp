#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "vec3.h"


vec3 color(const Ray& r, hitable *world, int depth) {
    HitRecord rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {
        Ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        else {
            return vec3(0, 0, 0); // Background color if no scatter
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0); // Gradient background
    }
}


int main() {
    int nx = 700;
    int ny = 400;
    int ns = 100; // Number of samples per pixel

    std::ofstream out("scene.ppm"); // Abre o arquivo para escrita
    if (!out) {
        std::cerr << "Erro ao abrir o arquivo para escrita!\n";
        return 1;
    }

    out << "P3\n" << nx << " " << ny << "\n255\n"; // Abre o arquivo para escrita

    hitable *list[4];
    list[0] = new Sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(vec3(1.2, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 1.0));
    list[3] = new Sphere(vec3(-1.2, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.3));
    hitable *world = new HitableList(list, 4);

    // camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90.0, float(nx) / float(ny));
    camera cam(vec3(0, 1, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90.0, float(nx) / float(ny));

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + ((float) rand() / RAND_MAX)) / float(nx);
                float v = float(j + ((float) rand() / RAND_MAX)) / float(ny);
                Ray r = cam.getRay(u, v);
                // vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
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


