#include "graph.cpp"

//Funciones auxiliares

//Funcion auxiliar para ver que aristas se escogieron como optimas
void printEdges(std::vector<Edge> edgesList){
    std::cout << "Las aristas que minimizan el peso son: ";
    for(auto a :edgesList){
        std::cout << "(" << a.n1->id << "," << a.n2->id << ")" << "->w:" << a.peso << "  ";
    }
    std::cout << "\n";
}


bool sortByWeight(Edge a1, Edge a2){
    return a1.peso<a2.peso;
}


bool sortByWeightHeap(Edge a1, Edge a2){
    return a1.peso>a2.peso;
}

bool mismosPesos(const std::vector<Edge>& A,
    const std::vector<Edge>& B,
    const std::vector<Edge>& C,
    const std::vector<Edge>& D) {

    auto suma = [](const std::vector<Edge>& edges) -> double {
        double total = 0;
        for (const Edge& e : edges) total += e.peso;
        return total;
    };

    double pesoA = suma(A);
    double pesoB = suma(B);
    double pesoC = suma(C);
    double pesoD = suma(D);

    return (pesoA == pesoB) && (pesoB == pesoC) && (pesoC == pesoD);
}
