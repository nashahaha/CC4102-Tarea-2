#include <vector>
#include <iostream>
#include <fstream>
#include "kruskal.cpp"
#include <chrono>

void runExpirement(int64_t N){
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
    std::chrono::duration<double> constructionDuration = startConstruction - endConstruction;
    std::cout << "Grafo construido en " << constructionDuration.count() << " segundos.\n";

    // Buscar árbol con los cuatro métodos
    std::cout << "Buscando árbol cobertor con un arreglo ordenado: \n";
    auto startMSTarray = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_array = kruskal_array(G);
    auto endMSTarray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTarrayDuration = startMSTarray - endMSTarray;
    std::cout << "Arbol encontrado en " << MSTarrayDuration.count() << " segundos.\n";


    std::cout << "Buscando árbol cobertor con un arreglo ordenado y Union-Find: \n";
    auto startMSTarrayUF = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_array_opt = kruskal_array_Opti(G);
    auto endMSTarrayUF = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTarrayUFDuration = startMSTarrayUF - endMSTarrayUF;
    std::cout << "Arbol encontrado en " << MSTarrayUFDuration.count() << " segundos.\n";

    
    std::cout << "Buscando árbol cobertor con un heap: \n";
    auto startMSTheap = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_heap = kruskal_heap(G);
    auto endMSTheap = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTheapDuration = startMSTheap - endMSTheap;
    std::cout << "Arbol encontrado en " << MSTheapDuration.count() << " segundos.\n";
    

    std::cout << "Buscando árbol cobertor con un heap y Union Find: \n";
    auto startMSTheapUF = std::chrono::high_resolution_clock::now();
    std::vector<Edge> MST_heap_opt = kruskal_heap_Opti(G);
    auto endMSTheapUF = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MSTheapUFDuration = startMSTheapUF - endMSTheapUF;
    std::cout << "Arbol encontrado en " << MSTheapUFDuration.count() << " segundos.\n";
    

    // Verificar que todos obtuvieron el mismo peso


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

    std::ofstream data("data_experimentos.txt", std::ios::app);
    if(data){
        data << N << ", " << constructionDuration.count() << ", " << MSTarrayDuration.count() << ", " << MSTarrayUFDuration.count() << ", " << MSTheapDuration.count() << ", " << MSTheapUFDuration.count() << "\n";
    } else {
        std::cerr << "No se pudo escribir el resumen en 'data_experimentos.txt'\n";
    }
}

int main(){
    std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7), Node(1,1), Node(2,3), Node(0,4) };
    Graph g1(nodos1);
    g1.addAllEdges();
    g1.print();

    std::vector<Edge> aristasOpt = kruskal_array_Opti(g1);
    printEdges(aristasOpt);
    std::vector<Edge> aristas = kruskal_array(g1);
    printEdges(aristas);
    std::vector<Edge> aristasHeap1 = kruskal_heap(g1);
    printEdges(aristasHeap1);
    std::vector<Edge> aristasHeapOpti1 = kruskal_heap_Opti(g1);
    printEdges(aristasHeapOpti1);

    for(int i=5; i<=12; i++){
        for(int j=0; i<5; j++){

        }
    }

    return 0;
}