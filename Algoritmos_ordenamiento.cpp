#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

void selectionSort(vector<int>& arr) {
    vector<int>::size_type n = arr.size();
    for (vector<int>::size_type i = 0; i < n - 1; i++) {
        vector<int>::size_type min_idx = i;
        for (vector<int>::size_type j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

void merge(vector<int> &array, int izq, int mid, int der) {
    int n1 = mid - izq + 1;
    int n2 = der - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = array[izq + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = array[mid + 1 + i];
    }

    int i = 0, j = 0, k = izq;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &array, int izq, int der) {
    if (izq < der) {
        int mid = izq + (der - izq) / 2;

        mergeSort(array, izq, mid);
        mergeSort(array, mid + 1, der);

        merge(array, izq, mid, der);
    }
}

int main() {
    string NombreArchivo;
    string tipo_ordenamiento;
    cout << "Ingrese el nombre exacto del archivo: (con extension): ";
    cin >> NombreArchivo;
    cout << "Ingrese el tipo de ordenamiento (selectionSort, mergeSort): ";
    cin >> tipo_ordenamiento;
    ifstream archivo(NombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }

    vector<int> array;

    int numeros;
    while (archivo >> numeros) {
        array.push_back(numeros);
    }

    if (tipo_ordenamiento == "mergeSort") {
        for (int i = 0; i < 5; i++) {         /////////// eliminar el for para que solo se ejecute una vez antes de entregar
            auto inicio = chrono::high_resolution_clock::now();
            mergeSort(array, 0, array.size() - 1);
            auto fin = chrono::high_resolution_clock::now();

            auto duraccion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duraccion.count() << " microsegundos" << "/ "<< duraccion.count()/1000000 << " segundos" << endl;
        }
    }
    else if (tipo_ordenamiento == "selectionSort") {
        for (int i = 0; i < 5; i++) {         /////////// eliminar el for para que solo se ejecute una vez antes de entregar
            auto inicio = chrono::high_resolution_clock::now();
            selectionSort(array);
            auto fin = chrono::high_resolution_clock::now();

            auto duraccion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duraccion.count() << " microsegundos" << " / "<< duraccion.count()/1000000 << " segundos" << endl;
        }
    }    

    archivo.close();

    ofstream archivoOrdenado("DataSet_Ordenada.txt");
    for (vector<int>::size_type i = 0; i < array.size(); i++) {
        archivoOrdenado << array[i] << endl;
    }
    archivoOrdenado.close();

    return 0;
}