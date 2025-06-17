# CC4102-Tarea-2

Este proyecto contiene la implementación de cuatro variantes del algoritmo de Kruskal para encontrar árboles de expansión mínima (MST - Minimum Spanning Tree) en grafos no dirigidos. El objetivo principal es comparar el rendimiento de las distintas variantes a través de experimentación empírica.


## Estructura del proyecto
.

├── aux_f.cpp         # Funciones auxiliares (ordenamiento, impresión etc.)

├── graph.cpp         # Implementación de grafos no dirigidos

├── kruskal.cpp       # Implementación de las cuatro versiones del algoritmo de Kruskal

├── UnionFind.cpp     # Estructura Union-Find con y sin optimizaciones

├── main.cpp          # Función principal y ejecución de experimentos

└── csv/              # Directorio que contiene los resultados experimentales en formato CSV

└── exe/              # Directorio que contiene los ejecutables

## Compilación (usando g++)
Para compilar los experimentos se debe ejecutar el main con:

```
g++ -o ./exe/main main.cpp
```

```
./exe/main
```