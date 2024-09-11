#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int Generar_numero_aleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

vector<vector<int>> Matriz_Cuadrada(int tamanio) {
    vector<vector<int>> matriz (tamanio, vector<int>(tamanio));
    for (int i = 0; i < tamanio; i++) {
        for (int j = 0; j < tamanio; j++) {
            matriz[i][j] = Generar_numero_aleatorio(0, 1000);
        }
    }
    return matriz;
}

void Crear_dataMatriz(vector<vector<int>> matriz1, vector<vector<int>> matriz2, string nombre_archivo) {
    ofstream archivo(nombre_archivo);
    
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    };

    for (auto& fila : matriz1) {
        for (int elemento : fila) {
            archivo << elemento << " ";
        }
        archivo << endl;
    }

    archivo << endl;

    for (auto& fila : matriz2) {
        for (int elemento : fila) {
            archivo << elemento << " ";
        }
        archivo << endl;
    }

    archivo.close();
}

int main() {
    
    for (int tamanio1 = 2; tamanio1 <= pow(2, 10); tamanio1 *= 2){
        vector<vector<int>> matriz_1 = Matriz_Cuadrada(tamanio1);
        vector<vector<int>> matriz_2 = Matriz_Cuadrada(tamanio1);
        Crear_dataMatriz(matriz_1, matriz_2, "matriz_misma_dimension" + to_string(tamanio1) + ".txt");
        cout << "Se crearon dos matrices de tamanio " << tamanio1 << endl;
    }
    
    return 0;
}