#include <iostream>
#include <fstream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"


vec3 color(const Ray& r, hitable *world) {
    HitRecord rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)) {
        return 0.5 * vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1); // Recursive ray tracing
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

    std::ofstream out("scene.ppm"); // Abre o arquivo para escrita
    if (!out) {
        std::cerr << "Erro ao abrir o arquivo para escrita!\n";
        return 1;
    }

    out << "P3\n" << nx << " " << ny << "\n255\n"; // Abre o arquivo para escrita

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *list[2];
    list[0] = new Sphere(vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new HitableList(list, 2);

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r, world);
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



