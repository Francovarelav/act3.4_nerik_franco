#ifndef ORDEN_H
#define ORDEN_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Estructura para almacenar los datos completos de cada orden
struct Orden {
    unsigned long int fecha;
    char restaurante[256];
    char orden[256];
    unsigned long int precio;
    char lineaOriginal[256];

    Orden();
    Orden(unsigned long int _fecha, const char* _restaurante, const char* _orden,
          unsigned long int _precio, const char* _linea);
};

// Prototipos de funciones
int extraerFecha(char *linea);
void extraerRestaurante(char *linea, char *restaurante);
void extraerOrden(char *linea, char *orden);
unsigned long int extraerPrecio(char *linea);

void quickSort(Orden arr[], int low, int high);
void mostrarPrimeros10(Orden ordenes[], int total);
void guardarOrdenamientoCompleto(Orden ordenes[], int total);
void buscarPorRango(Orden ordenes[], int total, unsigned long int fechaInicio, unsigned long int fechaFin);

template <class T>
int IndicebusquedaBin(T *lista, int n, T clave);

void guardarBusqueda(Orden ordenes[], int total, unsigned long int fechaInicio, unsigned long int fechaFin);

#endif
