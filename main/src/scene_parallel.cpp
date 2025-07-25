#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include "dependence/ray.h"
#include "dependence/sphere.h"
#include "dependence/hitable_list.h"
#include "float.h"
#include "dependence/camera.h"
#include "dependence/lambertian.h"
#include "dependence/metal.h"
#include "dependence/vec3.h"
#include <omp.h>
#include <chrono>


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

    auto start = std::chrono::high_resolution_clock::now();

    int nx = 700;
    int ny = 400;
    int ns = 100; // Number of samples per pixel

    std::ofstream out("output/scene_parallel.ppm"); // Salva na pasta output
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


    std::vector<std::vector<vec3>> image(ny, std::vector<vec3>(nx));

    omp_set_num_threads(4);
    #pragma omp parallel for schedule(dynamic)
    for (int j = 0; j < ny; j++) {
        // Gerador de números aleatórios por thread
        std::mt19937 rng(omp_get_thread_num() + 42); 
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + dist(rng)) / float(nx);
                float v = float((ny - 1 - j) + dist(rng)) / float(ny); // j invertido para manter topo para baixo
                Ray r = cam.getRay(u, v);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            image[j][i] = col;
        }
    }

    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            int ir = int(255.99 * image[j][i][0]);
            int ig = int(255.99 * image[j][i][1]);
            int ib = int(255.99 * image[j][i][2]);
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close(); // Fecha o arquivo
    std::cout << "Arquivo PPM gerado com sucesso: output/scene_parallel.ppm\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tempo de execucao: " << elapsed.count() << " segundos\n";

    return 0;
}


