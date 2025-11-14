# Presentacion Proyecto ACT3.4

## Objetivo
Explicar el programa que analiza el archivo `orders.txt`, cuenta la frecuencia de cada platillo y construye un arbol binario de busqueda (BST) para ordenarlos por frecuencia de pedidos.

## Estructura sugerida
1. **Introduccion**
   - Contexto del curso y entrega.
   - Equipo y roles (Franco, Nerik, Eduardo).
2. **Problema a resolver**
   - Necesidad de analizar un historial grande de ordenes.
   - Metas: ordenar registros, encontrar platillos mas populares.
3. **Datos y fuentes**
   - Descripcion del archivo `orders.txt`.
   - Campos relevantes (fecha, restaurante, orden, precio).
4. **Arquitectura general**
   - Diagrama simple (entrada `orders.txt` -> procesamiento -> resultados).
   - Division en archivos (`main.cpp`, `act1.3_integral.cpp`, `Orden.h`, etc.).
5. **Procesamiento en `main.cpp`**
   - Lectura de `orders.txt`.
   - Extraccion del platillo (`extraerOrden`).
   - Conteo de frecuencias.
   - Construccion del BST (`insertar` en `NodoArbol`).
   - Recorrido descendente para mostrar los mas pedidos.
6. **Funciones clave**
   - `extraerOrden`: como limpia el texto.
   - `insertar`: agrupacion por frecuencia.
   - `imprimirDescendente`: salida ordenada.
7. **Resultados**
   - Muestra esperada en consola.
   - Ejemplo de interpretacion: cuantos platillos distintos, top mas pedidos.
8. **Demostracion**
   - Pasos para compilar y ejecutar:
     - `g++ main.cpp act1.3_integral.cpp -o reporte`
     - `./reporte`
   - Mostrar fragmentos de la salida.
9. **Conclusiones**
   - Lo aprendido (uso de BST, manejo de archivos grandes).
   - Posibles mejoras (visualizacion grafica, analisis por restaurante).
10. **Preguntas**
    - Preparar respuestas sobre eficiencia, complejidad, validacion de datos.

## Material de apoyo
- Capturas o fragmentos de codigo clave.
- Tabla con top 5 platillos.
- Diagrama simple del flujo.

## Practica de la presentacion
- Duracion objetivo: 8-10 minutos.
- Roles sugeridos: 
  - Franco: introduccion y problema.
  - Nerik: arquitectura y funciones clave.
  - Eduardo: resultados y conclusiones.
- Ensayar transiciones y manejo del demo en consola.

