#include "vec3.h"
#include <iostream>
#include <fstream>

int main() {
    int nx = 200;
    int ny = 100;

    std::ofstream out("output.ppm"); // Abre o arquivo para escrita
    if (!out) {
        std::cerr << "Erro ao abrir o arquivo para escrita!\n";
        return 1;
    }

    out << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close(); // Fecha o arquivo
    std::cout << "Arquivo PPM gerado com sucesso: output.ppm\n";

    return 0;
}
