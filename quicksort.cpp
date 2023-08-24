#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <ctime>

#define FILE_RANDOM "numeros_aleatorios.csv"
#define FILE_SORTED "numeros_ordenados.csv"

using namespace std;

int compare(const int *a, const int *b) {
    return (*(int*)a - *(int*)b);
}

void par_qsort(int *data, int lo, int hi) {
    if(lo > hi) return;

    int l = lo;
    int h = hi;
    int p = data[(hi + lo)/2];

    while(l <= h) {
        while((data[l] - p) < 0) l++;
        while((data[h] - p) > 0) h--;
        
        if(l <= h) {
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++; 
            h--;
        }
    }
    
    par_qsort(data, lo, h);
    par_qsort(data, l, hi);
}

int main(int argc, char *argv[]) {
    srand(time(0)); // Para obtener números aleatorios diferentes en cada ejecución.

    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <Numero de elementos aleatorios>" << endl;
        return EXIT_FAILURE;
    }

    int N = atoi(argv[1]);
    int* Array = new int[N]; // Usamos memoria del heap para el arreglo.

    ofstream file_random(FILE_RANDOM);
    if(!file_random.is_open()) {
        cerr << "Error al abrir/crear el archivo " << FILE_RANDOM << endl;
        return EXIT_FAILURE;
    }

    cout << "Generando " << N << " números aleatorios." << endl;
    for (int i = 0; i < N; i++) {
        Array[i] = rand();
        file_random << Array[i];
        if (i != N - 1) file_random << ","; // No agregamos una coma después del último número.
    }
    file_random.close();

    cout << "Clasificando los números." << endl;
    par_qsort(Array, 0, N - 1);

    ofstream file_sorted(FILE_SORTED);
    if(!file_sorted.is_open()) {
        cerr << "Error al abrir/crear el archivo " << FILE_SORTED << endl;
        delete[] Array; // Liberamos memoria antes de salir.
        return EXIT_FAILURE;
    }

    cout << "Escribiendo números clasificados al archivo." << endl;
    for (int i = 0; i < N; i++) {
        file_sorted << Array[i];
        if (i != N - 1) file_sorted << ",";
    }
    file_sorted.close();

    delete[] Array; // Limpiamos la memoria del heap.
    cout << "Proceso completado." << endl;

    return 0;
}
