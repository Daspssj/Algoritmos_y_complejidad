#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

int Generar_numero_aleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void Crear_dataset(int tamanio, string tipo_ordenamiento) {

    ofstream archivo("dataset_" + tipo_ordenamiento + "_" + to_string(tamanio) + ".txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    vector<int> numeros;

    if (tipo_ordenamiento == "Random") {
        for (int i = 0; i < tamanio; i++){
        numeros.push_back(Generar_numero_aleatorio(0,100));
        }
        random_shuffle(numeros.begin(), numeros.end());
    }
    else if (tipo_ordenamiento == "Parcialmente-ordenados") {
        for (int i = 0; i < tamanio; i++){ 
            numeros.push_back(Generar_numero_aleatorio(0,100));
        }
        
        sort(numeros.begin(), numeros.begin() + tamanio/2);
    }
    else if (tipo_ordenamiento == "Inversamente-ordenados") {
        for (int i = 0; i < tamanio; i++) {
            numeros.push_back(Generar_numero_aleatorio(0,100));
        }
        sort(numeros.begin(), numeros.end(), greater<int>());
    }
    else {
        cout << "Tipo de ordenamiento no valido" << endl;
        return;
    }

    for (int numero : numeros) {
        archivo << numero << endl;
    }

    archivo.close();
}

int main() {
    string tipo_ordenamiento;
    cout << "Ingerese el tipo de ordenamiento (Random, Parcialmente-ordenados, Inversamnete-ordenados): " << endl;
    cin >> tipo_ordenamiento;
    cout << "Se creara un dataset de 1000, 10000 y 100000 elementos" << endl;

    Crear_dataset(1000, tipo_ordenamiento);
    Crear_dataset(10000, tipo_ordenamiento);
    Crear_dataset(100000, tipo_ordenamiento);

    return 0;
}