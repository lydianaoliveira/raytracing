#include <iostream>
#include <omp.h>

int main() {
    // #pragma omp parallel
    // {
    //     int id = omp_get_thread_num();
    //     std::cout << "Thread " << id << " ativa\n";
    // }
    int num_threads = omp_get_max_threads();
    std::cout << "Threads utilizadas: " << num_threads << "\n";

    return 0;
}
