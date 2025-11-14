/*
Descripción del programa:
1. Agregue todos los menús y almacénelos en una estructura tipo BST  dónde la llave será el número de platillor y el valor es el platillo.
2. Encuentre los pedidos con más solicitud.

Autores: Equipo SProblema 5
 - Franco Varela Villegas - A01199186
 - Nerik Nieto Gutiérrez - A01739652
 - Eduardo Mora Howard - A00829920

Fecha de modificación: 13/11/2025
*/

#include <iostream>
using namespace std;
#include <fstream>
#include <cstring>
#include "Orden.h"
#include <string>

#define MAX_ORDENES 10000
#define MAX_NOMBRE 256
#define MAX_PLATILLOS 5000  // máximo de platillos distintos

// Nodo del árbol binario de búsqueda
struct NodeT {
    int frecuencia;
    char ordenes[10][MAX_NOMBRE]; // agrupa platillos con la misma frecuencia (máx. 10)
    int numOrdenes;
    NodeT *left, *right;

    NodeT(int f, const char* nombre) {
        frecuencia = f;
        strcpy(ordenes[0], nombre);
        numOrdenes = 1;
        left = right = nullptr;
    }
};

// Inserta en el árbol según frecuencia
NodeT* insertar(NodeT* root, int frecuencia, const char* nombre) {
    if (root == nullptr)
        return new NodeT(frecuencia, nombre);

    if (frecuencia < root->frecuencia)
        root->left = insertar(root->left, frecuencia, nombre);
    else if (frecuencia > root->frecuencia)
        root->right = insertar(root->right, frecuencia, nombre);
    else {
        // Misma frecuencia → agregar al mismo nodo
        if (root->numOrdenes < 10) {
            strcpy(root->ordenes[root->numOrdenes], nombre);
            root->numOrdenes++;
        }
    }
    return root;
}

// Recorrido descendente (de mayor a menor frecuencia)
void imprimirDescendente(NodeT* root) {
    if (root == nullptr) return;

    imprimirDescendente(root->right);

    cout << root->frecuencia << " veces: ";
    for (int i = 0; i < root->numOrdenes; i++) {
        cout << root->ordenes[i];
        if (i < root->numOrdenes - 1) cout << ", ";
    }
    cout << endl;

    imprimirDescendente(root->left);
}

// Extrae el nombre del platillo del texto completo
void extraerOrden(const char* linea, char* resultado) {
    const char* inicio = strstr(linea, "O:");
    if (inicio == nullptr) {
        strcpy(resultado, ""); // no hay orden
        return;
    }
    inicio += 2; // saltar "O:"
    const char* fin = strchr(inicio, '(');
    if (fin == nullptr) {
        strcpy(resultado, inicio);
    } else {
        int len = fin - inicio;
        strncpy(resultado, inicio, len);
        resultado[len] = '\0';
    }

    // Eliminar espacios al inicio y fin
    while (resultado[0] == ' ') memmove(resultado, resultado + 1, strlen(resultado));
    int n = strlen(resultado);
    while (n > 0 && resultado[n - 1] == ' ') resultado[--n] = '\0';
}

int main() {
    ifstream archivo("orders.txt");
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir 'orders.txt'" << endl;
        return 1;
    }

    cout << "Leyendo y procesando órdenes..." << endl;

    char linea[MAX_NOMBRE];
    char ordenes[MAX_ORDENES][MAX_NOMBRE];
    int totalOrdenes = 0;

    // Leer todas las órdenes del archivo
    while (archivo.getline(linea, sizeof(linea)) && totalOrdenes < MAX_ORDENES) {
        char platillo[MAX_NOMBRE];
        extraerOrden(linea, platillo);
        if (strlen(platillo) > 0) {
            strcpy(ordenes[totalOrdenes], platillo);
            totalOrdenes++;
        }
    }
    archivo.close();

    cout << "Total de órdenes leídas: " << totalOrdenes << endl;

    // Contar repeticiones
    char nombres[MAX_PLATILLOS][MAX_NOMBRE];
    int conteos[MAX_PLATILLOS];
    int numPlatos = 0;

    for (int i = 0; i < totalOrdenes; i++) {
        bool encontrado = false;
        for (int j = 0; j < numPlatos; j++) {
            if (strcmp(nombres[j], ordenes[i]) == 0) {
                conteos[j]++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado && numPlatos < MAX_PLATILLOS) {
            strcpy(nombres[numPlatos], ordenes[i]);
            conteos[numPlatos] = 1;
            numPlatos++;
        }
    }

    cout << "Platillos únicos encontrados: " << numPlatos << endl;

    // Crear el árbol binario por frecuencia
    NodeT* root = nullptr;
    for (int i = 0; i < numPlatos; i++) {
        root = insertar(root, conteos[i], nombres[i]);
    }

    // Mostrar el árbol descendente
    cout << "\n=== ÁRBOL DE FRECUENCIAS (de más pedidas a menos) ===\n";
    imprimirDescendente(root);

    return 0;
}
