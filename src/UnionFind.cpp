#include <vector>

class UnionFind {
    std::vector<int> padre; // Arreglo que marca quien es el padre de cada nodo
    std::vector<int> rango; // Rango de cada nodo
public:
    UnionFind(int n): padre(n), rango(n, 1){
        for(int i=0; i<n; i++) padre[i] = i; // Cada nodo parte siendo su propio padre
    }

    int find(int x){
        if(padre[x] != x) padre[x] = find(padre[x]);
        return padre[x];
    }

    bool union_(int x, int y){
        int raiz_x = find(x);
        int raiz_y = find(y);
        if (raiz_x == raiz_y) return false;

        
        if ( rango[raiz_x]< rango[raiz_y]) std::swap(raiz_x, raiz_y); 

        padre[raiz_y] = raiz_x;
        
        rango[raiz_x]+= rango[raiz_y];
        
        return true;
    }
};