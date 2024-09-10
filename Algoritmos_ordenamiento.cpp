#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>

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

void quickSort(vector<int>& arr, int izq, int der) {
    int i = izq, j = der;
    int tmp;
    int pivot = arr[(izq + der) / 2];

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    if (izq < j) {
        quickSort(arr, izq, j);
    }
    if (i < der) {
        quickSort(arr, i, der);
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
    int tipo_ordenamiento;
    cout << "Ingrese el nombre del archivo (sin dominio .txt): ";
    cin >> NombreArchivo ;
    cout << "Ingrese el tipo de ordenamiento (ingresar numero):\n" << "1.- selectionSort" << "\n" << "2.- mergeSort" << "\n" << "3.- quickSort" << "\n" << "4.- SortC++" << endl;
    cin >> tipo_ordenamiento;
    ifstream archivo(NombreArchivo + ".txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }

    vector<int> array;

    int numeros;
    while (archivo >> numeros) {
        array.push_back(numeros);
    }

    if (tipo_ordenamiento == 1) {
        auto inicio = chrono::high_resolution_clock::now();
        mergeSort(array, 0, array.size() - 1);
        auto fin = chrono::high_resolution_clock::now();
        auto duraccion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        cout << "Tiempo de ejecucion: " << duraccion.count() << " microsegundos" << "/ "<< duraccion.count()/1000000 << " segundos" << endl;
    }
    else if (tipo_ordenamiento == 2) {
            auto inicio = chrono::high_resolution_clock::now();
            selectionSort(array);
            auto fin = chrono::high_resolution_clock::now();

            auto duraccion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duraccion.count() << " microsegundos" << " / "<< duraccion.count()/1000000 << " segundos" << endl;
    }
    else if (tipo_ordenamiento == 3) {
            auto inicio = chrono::high_resolution_clock::now();
            quickSort(array, 0, array.size() - 1);
            auto fin = chrono::high_resolution_clock::now();

            auto duraccion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duraccion.count() << " microsegundos" << " / "<< duraccion.count()/1000000 << " segundos" << endl;
    } 
    else if(tipo_ordenamiento == 4) {
            auto inicio = chrono::high_resolution_clock::now();
            sort(array.begin(), array.end());
            auto fin = chrono::high_resolution_clock::now();

            auto duraccion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

            cout << "Tiempo de ejecucion: " << duraccion.count() << " microsegundos" << " / "<< duraccion.count()/1000000 << " segundos" << endl;
    }
    else {
        cout << "Tipo de ordenamiento no valido" << endl;
    }

    archivo.close();

    ofstream archivoOrdenado("DataSet_Ordenada.txt");
    for (vector<int>::size_type i = 0; i < array.size(); i++) {
        archivoOrdenado << array[i] << endl;
    }
    archivoOrdenado.close();

    return 0;
}