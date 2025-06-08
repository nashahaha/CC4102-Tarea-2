#include <vector>
#include <iostream>
#include <fstream>
#include "kruskal.cpp"
#include <chrono>
bool mismosPesos(const std::vector<Edge>& A,
                 const std::vector<Edge>& B,
                 const std::vector<Edge>& C,
                 const std::vector<Edge>& D) {

    auto suma = [](const std::vector<Edge>& edges) -> int64_t {
    int64_t total = 0;
    for (const Edge& e : edges) total += e.peso;
    return total;
    };

    int64_t pesoA = suma(A);
    int64_t pesoB = suma(B);
    int64_t pesoC = suma(C);
    int64_t pesoD = suma(D);

    return (pesoA == pesoB) && (pesoB == pesoC) && (pesoC == pesoD);
}

void runExpirement(int N){
    // Contar el tiempo de construcción
    std::cout << "Creando grafo de " << N << " aristas \n";
    auto startConstruction = std::chrono::high_resolution_clock::now();
    // Crear N nodos
    std::vector<Node> nodos = {};
    for (int i=0; i<N; i++) nodos.push_back(Node());

    // Crear árbol con todas sus posibles aristas
    Graph G(nodos);
    G.addAllEdges();
    auto endConstruction = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> constructionDuration = endConstruction - startConstruction;
    std::cout << "Grafo construido en " << constructionDuration.count() << " segundos.\n";

    // Buscar árbol con los cuatro métodos
    std::cout << "Buscando árbol cobertor con un arreglo ordenado: \n";
    auto startMSTarray = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_array = kruskal_array(G);
    auto endMSTarray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTarrayDuration = endMSTarray - startMSTarray;
    std::cout << "Arbol encontrado en " << MSTarrayDuration.count() << " segundos.\n";


    std::cout << "Buscando árbol cobertor con un arreglo ordenado y Union-Find: \n";
    auto startMSTarrayUF = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_array_opt = kruskal_array_Opti(G);
    auto endMSTarrayUF = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTarrayUFDuration = endMSTarrayUF - startMSTarrayUF;
    std::cout << "Arbol encontrado en " << MSTarrayUFDuration.count() << " segundos.\n";

    
    std::cout << "Buscando árbol cobertor con un heap: \n";
    auto startMSTheap = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_heap = kruskal_heap(G);
    auto endMSTheap = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTheapDuration = endMSTheap - startMSTheap;
    std::cout << "Arbol encontrado en " << MSTheapDuration.count() << " segundos.\n";
    

    std::cout << "Buscando árbol cobertor con un heap y Union Find: \n";
    auto startMSTheapUF = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_heap_opt = kruskal_heap_Opti(G);
    auto endMSTheapUF = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTheapUFDuration = endMSTheapUF - startMSTheapUF;
    std::cout << "Arbol encontrado en " << MSTheapUFDuration.count() << " segundos.\n";
    

    // Verificar que todos obtuvieron el mismo peso
    if(!mismosPesos(MST_array, MST_array_opt, MST_heap, MST_heap_opt)){
        std::cerr << "Error: no se obtuvieron los mismos pesos";
        exit(1);
    }


    // Mostrar resultados
    std::cout << "\n-------------------------Resultados del experimento:-------------------------\n";
    std::cout <<   "|   Tamaño del input: " << N << " pares de enteros.       \n";
    std::cout <<   "|   Tiempo de creación del grafo: " << constructionDuration.count() << "\n";
    std::cout <<   "|   Tiempo de Kruskal sin optimización find y usando un arreglo ordenado: " << MSTarrayDuration.count() << " segundos.  \n";
    std::cout <<   "|   Tiempo de Kruskal con optimización find y usando un arreglo ordenado: " << MSTarrayUFDuration.count() << " segundos.\n";
    std::cout <<   "|   Tiempo de Kruskal sin optimización find y usando un heap: " << MSTheapDuration.count() << " segundos. \n";
    std::cout <<   "|   Tiempo de Kruskal con optimización find y usando un heap: " << MSTheapUFDuration.count() << " segundos. \n";
    std::cout <<   "-----------------------------------------------------------------------------\n";

    // Guardar resumen en archivo de texto (modo append)
    std::ofstream summary("resumen_experimentos.txt", std::ios::app);
    if (summary) {
        summary << "----- Resultado del experimento -----\n";
        summary << "Tamaño del input: " << N << " pares de enteros.       \n";
        summary << "Tiempo de creación del grafo: " << constructionDuration.count() << "\n";
        summary << "Tiempo de Kruskal sin optimización find y usando un arreglo ordenado: " << MSTarrayDuration.count() << " segundos. \n";
        summary << "Tiempo de Kruskal con optimización find y usando un arreglo ordenado: " << MSTarrayUFDuration.count() << " segundos.\n";
        summary << "Tiempo de Kruskal sin optimización find y usando un heap: " << MSTheapDuration.count() << " segundos. \n";
        summary << "Tiempo de Kruskal con optimización find y usando un heap: " << MSTheapUFDuration.count() << " segundos. \n";
        summary << "--------------------------------------\n\n";
        summary.close();
    } else {
        std::cerr << "No se pudo escribir el resumen en 'resumen_experimentos.txt'\n";
    }

    std::ofstream data("resultados.csv", std::ios::app);
    if(data){
        data << N << "," 
             << constructionDuration.count() << "," 
             << MSTarrayDuration.count() << "," 
             << MSTarrayUFDuration.count() << "," 
             << MSTheapDuration.count() << "," 
             << MSTheapUFDuration.count() << "\n";
    } else {
        std::cerr << "No se pudo escribir el resumen en 'resultados.csv'\n";
    }
}

int main(){

    for(int i=5; i<=15; i++){
        int N = std::pow(2, i);
        for(int j=0; j<5; j++){
            runExpirement(N);
        }
    }

    return 0;
}