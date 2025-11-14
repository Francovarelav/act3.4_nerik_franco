#include "Orden.h"


// Estructura para almacenar los datos completos de cada orden

// Constructor default
Orden::Orden() {
    fecha = 0;
    strcpy(restaurante, "");
    strcpy(orden, "");
    precio = 0;
    strcpy(lineaOriginal, "");
}

// Constructor con parámetros
Orden::Orden(unsigned long int _fecha, const char* _restaurante, const char* _orden, unsigned long int _precio, const char* _linea) {
    fecha = _fecha;
    strcpy(restaurante, _restaurante);
    strcpy(orden, _orden);
    precio = _precio;
    strcpy(lineaOriginal, _linea);
}

// Función para extraer fecha de una línea
int extraerFecha(char *linea) {
    // Crear una copia de la linea original para no modificarla
    char copiaLinea[256];
    strcpy(copiaLinea, linea);

    const char* meses[12] = {"ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
    char mesCaracter[4], diaCaracter[3], horaCaracter[3], minutosCaracter[3], segundosCaracter[3];

    // Extraer con separadores y copiar en los arreglos de mes, dia, horas, minutos y segundos
    char *token = strtok(copiaLinea, " "); // Crear un token igual a la copia de la línea original pero cortado por strtok
    strcpy(mesCaracter, token);
    token = strtok(NULL, " ");
    strcpy(diaCaracter, token);
    token = strtok(NULL, ":");
    strcpy(horaCaracter, token); // Extrae Horas
    token = strtok(NULL, ":");
    strcpy(minutosCaracter, token); // Extrae Minutos
    token = strtok(NULL, " ");
    strcpy(segundosCaracter, token); // Extrae Segundos

    // Convertir mes de cadena de caracteres a int
    int mesNum = 0;
    for (int i = 0; i < 12; i++) {
        if (strncmp(mesCaracter, meses[i], 3) == 0) {
            mesNum = i + 1;
        }
    }

    
    // Unir fecha en formato MMDDHHMMSS
    unsigned long int fecha = mesNum*100000000 + atoi(diaCaracter)*1000000 + atoi(horaCaracter)*10000 + atoi(minutosCaracter)*100 + atoi(segundosCaracter);

    return fecha;
}

// Función para extraer restaurante de una línea
void extraerRestaurante(char *linea, char *restaurante) {
    char copiaLinea[256];
    strcpy(copiaLinea, linea);
    
    char *token = strtok(copiaLinea, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    
    if (token != NULL) {
        strcpy(restaurante, token);
    }
}

// Función para extraer orden de una línea
void extraerOrden(char *linea, char *orden) {
    char copiaLinea[256];
    strcpy(copiaLinea, linea);
    
    char *token = strtok(copiaLinea, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    
    if (token != NULL) {
        strcpy(orden, token);
    }
}

// Función para extraer precio de una línea
unsigned long int extraerPrecio(char *linea) {
    char copiaLinea[256];
    strcpy(copiaLinea, linea);
    
    // Buscar el último paréntesis
    char *inicio = strrchr(copiaLinea, '(');
    char *fin = strrchr(copiaLinea, ')');
    
    if (inicio != NULL && fin != NULL) {
        char precioStr[10];
        int len = fin - inicio - 1;
        strncpy(precioStr, inicio + 1, len);
        precioStr[len] = '\0';
        return atoi(precioStr);
    }
    return 0;
}

// Función QuickSort para ordenar por fecha
void quickSort(Orden arr[], int low, int high) {
    if (low < high) {
        // Particionar el arreglo
        int pivot = arr[high].fecha;
        int i = (low - 1);
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j].fecha <= pivot) {
                i++;
                Orden temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Orden temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        
        // Ordenar recursivamente
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función para mostrar los primeros 10 registros
void mostrarPrimeros10(Orden ordenes[], int total) {
    cout << "\n=== PRIMEROS 10 REGISTROS ORDENADOS POR FECHA ===" << endl;
    int limite;
    if (10 < total) {
        limite = 10;
    } else {
        limite = total;
    }
    for (int i = 0; i < limite; i++) {
        cout << i + 1 << ". " << ordenes[i].lineaOriginal << endl;
    }
}

// Función para guardar todos los registros ordenados en salida.txt
void guardarOrdenamientoCompleto(Orden ordenes[], int total) {
    ofstream archivo_salida("salida.txt");
    if (archivo_salida.is_open()) {
        for (int i = 0; i < total; i++) {
            archivo_salida << ordenes[i].lineaOriginal << endl;
        }
        archivo_salida.close();
        cout << "\nArchivo 'salida.txt' creado exitosamente con " << total << " registros ordenados." << endl;
    } else {
        cout << "Error al crear el archivo salida.txt" << endl;
    }
}

// Función para buscar registros en un rango de fechas
// Función para buscar registros en un rango de fechas usando búsqueda binaria
void buscarPorRango(Orden ordenes[], int total, unsigned long int fechaInicio, unsigned long int fechaFin) {
    cout << "\n=== RESULTADOS DE BÚSQUEDA (BINARIA) ===" << endl;
    cout << "Buscando registros entre fechas: " << fechaInicio << " y " << fechaFin << endl;

    // Crear un arreglo auxiliar solo con las fechas
    unsigned long int *fechas = new unsigned long int[total];
    for (int i = 0; i < total; i++) {
        fechas[i] = ordenes[i].fecha;
    }

    // Buscar índices con búsqueda binaria
    int inicio = IndicebusquedaBin(fechas, total, fechaInicio);
    int fin = IndicebusquedaBin(fechas, total, fechaFin);

    // Si no se encuentra exactamente, ajustar al rango más cercano
    if (inicio == -1) {
        // buscar el primer mayor o igual
        inicio = 0;
        while (inicio < total && ordenes[inicio].fecha < fechaInicio) inicio++;
    }
    if (fin == -1) {
        // buscar el último menor o igual
        fin = total - 1;
        while (fin >= 0 && ordenes[fin].fecha > fechaFin) fin--;
    }

    int encontrados = 0;
    if (inicio <= fin) {
        for (int i = inicio; i <= fin; i++) {
            cout << encontrados + 1 << ". " << ordenes[i].lineaOriginal << endl;
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron registros en el rango especificado." << endl;
    } else {
        cout << "\nTotal de registros encontrados: " << encontrados << endl;
    }

    delete[] fechas; // liberar memoria
}



template <class T>
int IndicebusquedaBin(T *lista, int n, T clave)
{
    T central, bajo, alto, valorCentral;
    bajo = 0;
    alto = n - 1;
    while (bajo <= alto)
    {
        central = (bajo + alto) / 2;
        valorCentral = lista[central];
        if (clave == valorCentral)
            return central;
        else if (clave < valorCentral)
            alto = central - 1;
        else
            bajo = central + 1;
    }
    return -1;
}

// Función para guardar resultados de búsqueda
void guardarBusqueda(Orden ordenes[], int total, unsigned long int fechaInicio, unsigned long int fechaFin) {
    ofstream archivo_busqueda("busqueda.txt");
    if (archivo_busqueda.is_open()) {
        archivo_busqueda << "=== RESULTADOS DE BÚSQUEDA ===" << endl;
        archivo_busqueda << "Rango de fechas: " << fechaInicio << " a " << fechaFin << endl << endl;
        
        // Búsqueda binaria
        int encontrados = 0;
        for (int i = 0; i < total; i++) {
            if (ordenes[i].fecha >= fechaInicio && ordenes[i].fecha <= fechaFin) {
                archivo_busqueda << encontrados + 1 << ". " << ordenes[i].lineaOriginal << endl;
                encontrados++;
            }
        }
        archivo_busqueda << "\nTotal de registros encontrados: " << encontrados << endl;
        archivo_busqueda.close();
        cout << "Resultados de búsqueda guardados en 'busqueda.txt'" << endl;
    } else {
        cout << "Error al crear el archivo de búsqueda" << endl;
    }
}
