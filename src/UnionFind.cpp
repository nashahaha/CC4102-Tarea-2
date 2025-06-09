#include <vector>

class UnionFind {
    std::vector<int> padre; // Arreglo que marca quien es el padre de cada nodo
    std::vector<int> rango; // Rango de cada nodo
public:
    UnionFind(int n): padre(n), rango(n, 1){
        for(int i=0; i<n; i++) padre[i] = i; // Cada nodo parte siendo su propio padre
    }

    int find(int x){
        if(padre[x] != x) padre[x] = find(padre[x]); // Modifica el padre del nodo actual por la raiz

        return padre[x];
    }

    int find_no_opt(int x) {
        if (padre[x] == x) return x; // caso base
        return find_no_opt(padre[x]);
    }

    void union_(int raiz_x, int raiz_y){
        if ( rango[raiz_x]< rango[raiz_y]) std::swap(raiz_x, raiz_y); // se hace la union al de menor rango

        padre[raiz_y] = raiz_x;
        
        rango[raiz_x]+= rango[raiz_y];
        
    }

    // Solo cambia el padre de la raiz y
    void union_no_opt(int raiz_x, int raiz_y){
        padre[raiz_y] = raiz_x;
    }
};