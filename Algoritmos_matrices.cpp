#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

void escribir_matriz(const vector<vector<int>>& matriz, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo);
    
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            archivo << elemento << " ";
        }
        archivo << endl;
    }

    archivo.close();
}

vector<vector<int>> Multiplicacion_matrices(const vector<vector<int>>& matriz_1, const vector<vector<int>>& matriz_2) {
    size_t dimension = matriz_1.size();
    vector<vector<int>> matriz_resultante(dimension, vector<int>(dimension, 0));

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            for (size_t k = 0; k < dimension; ++k) {
                matriz_resultante[i][j] += matriz_1[i][k] * matriz_2[k][j];
            }
        }
    }

    return matriz_resultante;
}

vector<vector<int>> Matriz_transpuesta(const vector<vector<int>>& matriz) {
    size_t dimension = matriz.size();
    vector<vector<int>> matriz_transpuesta(dimension, vector<int>(dimension));

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            matriz_transpuesta[i][j] = matriz[j][i];
        }
    }

    return matriz_transpuesta;
}

vector<vector<int>> Multiplicacion_matriz_transpuesta(const vector<vector<int>>& matriz_1, const vector<vector<int>>& matriz_2) {
    size_t dimension = matriz_1.size();
    vector<vector<int>> matriz_3 = Matriz_transpuesta(matriz_2);
    vector<vector<int>> matriz_resultante(dimension, vector<int>(dimension, 0));

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            for (size_t k = 0; k < dimension; ++k) {
                matriz_resultante[i][j] += matriz_1[i][k] * matriz_3[j][k];
            }
        }
    }

    return matriz_resultante;
}

vector<vector<int>> Sumar_matrices(vector<vector<int>>& matriz_1, vector<vector<int>>& matriz_2) {
    size_t dimension = matriz_1.size();
    vector<vector<int>> matriz_resultante(dimension, vector<int>(dimension));

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            matriz_resultante[i][j] = matriz_1[i][j] + matriz_2[i][j];
        }
    }

    return matriz_resultante;
}

vector<vector<int>> Restar_matrices(vector<vector<int>>& matriz_1, vector<vector<int>>& matriz_2) {
    size_t dimension = matriz_1.size();
    vector<vector<int>> matriz_resultante(dimension, vector<int>(dimension));

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            matriz_resultante[i][j] = matriz_1[i][j] - matriz_2[i][j];
        }
    }

    return matriz_resultante;
}

vector<vector<int>> Strassen(vector<vector<int>>& matriz_1, vector<vector<int>>& matriz_2) {
    size_t dimension = matriz_1.size();
    vector<vector<int>> matriz_resultante(dimension, vector<int>(dimension));

    if (dimension == 1) {
        matriz_resultante[0][0] = matriz_1[0][0] * matriz_2[0][0];
        return matriz_resultante;
    }

    size_t mitad = dimension / 2;

    vector<vector<int>> A11(mitad, vector<int>(mitad));
    vector<vector<int>> A12(mitad, vector<int>(mitad));
    vector<vector<int>> A21(mitad, vector<int>(mitad));
    vector<vector<int>> A22(mitad, vector<int>(mitad));

    vector<vector<int>> B11(mitad, vector<int>(mitad));
    vector<vector<int>> B12(mitad, vector<int>(mitad));
    vector<vector<int>> B21(mitad, vector<int>(mitad));
    vector<vector<int>> B22(mitad, vector<int>(mitad));

    vector<vector<int>> C11(mitad, vector<int>(mitad));
    vector<vector<int>> C12(mitad, vector<int>(mitad));
    vector<vector<int>> C21(mitad, vector<int>(mitad));
    vector<vector<int>> C22(mitad, vector<int>(mitad));

    vector<vector<int>> M1(mitad, vector<int>(mitad));
    vector<vector<int>> M2(mitad, vector<int>(mitad));
    vector<vector<int>> M3(mitad, vector<int>(mitad));
    vector<vector<int>> M4(mitad, vector<int>(mitad));
    vector<vector<int>> M5(mitad, vector<int>(mitad));
    vector<vector<int>> M6(mitad, vector<int>(mitad));
    vector<vector<int>> M7(mitad, vector<int>(mitad));

    vector<vector<int>> A_resultante(mitad, vector<int>(mitad));
    vector<vector<int>> B_resultante(mitad, vector<int>(mitad));

    for (size_t i = 0; i < mitad; ++i) {
        for (size_t j = 0; j < mitad; ++j) {
            A11[i][j] = matriz_1[i][j];
            A12[i][j] = matriz_1[i][j + mitad];
            A21[i][j] = matriz_1[i + mitad][j];
            A22[i][j] = matriz_1[i + mitad][j + mitad];

            B11[i][j] = matriz_2[i][j];
            B12[i][j] = matriz_2[i][j + mitad];
            B21[i][j] = matriz_2[i + mitad][j];
            B22[i][j] = matriz_2[i + mitad][j + mitad];
        }
    }

    A_resultante = Sumar_matrices(A11, A22);
    B_resultante = Sumar_matrices(B11, B22);
    M1 = Strassen(A_resultante, B_resultante);

    A_resultante = Sumar_matrices(A21, A22);
    M2 = Strassen(A_resultante, B11);

    B_resultante = Restar_matrices(B12, B22);
    M3 = Strassen(A11, B_resultante);

    B_resultante = Restar_matrices(B21, B11);
    M4 = Strassen(A22, B_resultante);

    A_resultante = Sumar_matrices(A11, A12);
    M5 = Strassen(A_resultante, B22);

    A_resultante = Restar_matrices(A21, A11);
    B_resultante = Sumar_matrices(B11, B12);
    M6 = Strassen(A_resultante, B_resultante);

    A_resultante = Restar_matrices(A12, A22);
    B_resultante = Sumar_matrices(B21, B22);
    M7 = Strassen(A_resultante, B_resultante);

    C12 = Sumar_matrices(M3, M5);
    C21 = Sumar_matrices(M2, M4);

    A_resultante = Sumar_matrices(M1, M4);
    B_resultante = Sumar_matrices(A_resultante, M7);

    C11 = Restar_matrices(B_resultante, M5);
    C22 = Restar_matrices(B_resultante, M3);

    for (size_t i = 0; i < mitad; ++i) {
        for (size_t j = 0; j < mitad; ++j) {
            matriz_resultante[i][j] = C11[i][j];
            matriz_resultante[i][j + mitad] = C12[i][j];
            matriz_resultante[i + mitad][j] = C21[i][j];
            matriz_resultante[i + mitad][j + mitad] = C22[i][j];
        }
    }

    return matriz_resultante;
}    

int main() {
    int tipo_algoritmo;
    int dimension;
    string nombre_archivo;

    cout << "Ingrese el nombre del archivo(sin .txt): ";
    cin >> nombre_archivo;
    cout << "Ingrese la dimension de una matriz: ";
    cin >> dimension;
    cout << "Ingrese el tipo de algoritmo que desea ejecutar:\n 1. Multiplicacion de matrices\n 2. Multiplicacion de matrices con matriz transpuesta\n 3. Algoritmo de Strassen\n";
    cin >> tipo_algoritmo;

    ifstream archivo(nombre_archivo + ".txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    vector<vector<int>> matriz_1(dimension, vector<int>(dimension));
    vector<vector<int>> matriz_2(dimension, vector<int>(dimension));

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            archivo >> matriz_1[i][j];
        }
    }
    string linea;
    getline(archivo, linea);
    getline(archivo, linea);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            archivo >> matriz_2[i][j];
        }
    }

    archivo.close();

    if (tipo_algoritmo == 1) {
        for(int i = 0; i < 10 ; i++){
            auto inicio = chrono::high_resolution_clock::now();
            vector<vector<int>> matriz_resultante = Multiplicacion_matrices(matriz_1, matriz_2);
            auto fin = chrono::high_resolution_clock::now();

            auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duracion.count() << " microsegundos" << endl;

            escribir_matriz(matriz_resultante, "matriz_resultante" + to_string(i) + ".txt");
        }
    }
    else if (tipo_algoritmo == 2) {
        for(int i = 0; i < 10 ; i++){
            auto inicio = chrono::high_resolution_clock::now();
            vector<vector<int>> matriz_resultante = Multiplicacion_matriz_transpuesta(matriz_1, matriz_2);
            auto fin = chrono::high_resolution_clock::now();

            auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duracion.count() << " microsegundos" << endl;

            escribir_matriz(matriz_resultante, "matriz_resultante" + to_string(i) + ".txt");
        }
    }
    else if (tipo_algoritmo == 3) {
        for(int i = 0; i < 10 ; i++){
            auto inicio = chrono::high_resolution_clock::now();
            vector<vector<int>> matriz_resultante = Strassen(matriz_1, matriz_2);
            auto fin = chrono::high_resolution_clock::now();

            auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duracion.count() << " microsegundos" << endl;

            escribir_matriz(matriz_resultante, "matriz_resultante" + to_string(i) + ".txt");
        }
    }
    else {
        cout << "Tipo de algoritmo no valido" << endl;
        return 1;
    }
    
    return 0;
}