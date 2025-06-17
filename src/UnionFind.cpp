#include <vector>
#include <iostream>
#include <string>

/**
 * @brief Clase que implementa una estructura Union-Find
 *
 * Esta estructura permite gestionar particiones disjuntas de elementos, soportando
 * operaciones eficientes de unión y búsqueda.
 */
class UnionFind {
    int *padre;     // Arreglo que marca quien es el padre de cada nodo
    int *treeSize;  // Arreglo con el número de hijos de cada nodo
    int n;          // Número total de elementos en la estructura
public:

     /**
     * @brief Constructor que inicializa la estructura para `N` elementos.
     *
     * Inicialmente, cada elemento forma un conjunto independiente.
     *
     * @param N Número de elementos.
     */
    UnionFind(int N){
        n = N;
        padre = new int[n];
        treeSize = new int[n];
        for(int i=0; i<n; i++){
            padre[i] = i; // Cada nodo parte siendo su propio padre
            treeSize[i] = 1;
        }
    }

    /**
     * @brief Une dos árboles por sus raíces.
     *
     * Une por tamaño, el conjunto más pequeño se conecta al más grande.
     *
     * @param raiz_x Raíz del primer conjunto.
     * @param raiz_y Raíz del segundo conjunto.
     */
    void union_(int raiz_x, int raiz_y){
        if ( treeSize[raiz_x]< treeSize[raiz_y]) std::swap(raiz_x, raiz_y); // se hace la union al de menor treeSize

        padre[raiz_y] = raiz_x;
        
        treeSize[raiz_x]+= treeSize[raiz_y];
        
    }

     /**
     * @brief Encuentra la raíz del conjunto al que pertenece un elemento, con compresión de caminos.
     *
     * Optimiza futuras búsquedas al hacer que todos los nodos visitados apunten directamente a la raíz.
     *
     * @param x Elemento a buscar.
     * @return Identificador de la raíz del conjunto.
     */
    int find(int x){
        if(padre[x] != x) padre[x] = find(padre[x]); // Modifica el padre del nodo actual por la raiz

        return padre[x];
    }

    /**
     * @brief Encuentra la raíz del conjunto sin aplicar compresión de caminos.
     *
     * @param x Elemento a buscar.
     * @return Identificador de la raíz del conjunto.
     */
    int find_no_opt(int x) {
        if (padre[x] == x) return x; // caso base
        return find_no_opt(padre[x]);
    }

    /**
     * @brief Imprime el arreglo de padres, que representa la estructura del bosque de conjuntos.
     *
     * @param i (opcional) Índice para nombrar el conjunto en la salida.
     */
    void printPadres(int i=-1) {
        if (i != -1)
            std::cout << "padres" << i << " = [";
        else
            std::cout << "padres = [";
        for (size_t i = 0; i < n; ++i) {
            std::cout << padre[i];
            if (i < n - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    /**
     * @brief Imprime los tamaños de árbol de cada conjunto.
     *
     * @param i (opcional) Índice para nombrar el conjunto en la salida.
     */
    void printTreeSizes(int i=-1) {
        if (i != -1)
            std::cout << "treeSize" << i << " = [";
        else
            std::cout << "treeSize = [";
        for (size_t i = 0; i < n; ++i) {
            std::cout << treeSize[i];
            if (i < n - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};