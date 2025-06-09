#include <fstream>
#include "kruskal.cpp"
#include <chrono>

/**
 * @brief Ejecuta un experimento de rendimiento para comparar variantes del algoritmo de Kruskal.
 *
 * Esta función genera un grafo completo de N nodos con posiciones aleatorias, calcula todas las aristas posibles,
 * y luego ejecuta cuatro variantes del algoritmo de Kruskal para obtener el Árbol de Expansión Mínima (MST).
 * Se mide y compara el tiempo de ejecución de cada variante:
 * 
 * 1. Kruskal con arreglo ordenado (sin Union-Find).
 * 2. Kruskal con arreglo ordenado + Union-Find.
 * 3. Kruskal con heap (sin Union-Find).
 * 4. Kruskal con heap + Union-Find.
 *
 * Además, verifica que todas las variantes produzcan MSTs con el mismo peso total y guarda los resultados en un archivo CSV.
 *
 * @param N Cantidad de nodos a generar para el grafo.
 *
 * ### CSV generado
 * La función guarda una línea por experimento en el archivo `./csv/resultados.csv`, con el siguiente formato:
 * ```
 * N,tiempo_construccion,kruskal_array,kruskal_array_uf,kruskal_heap,kruskal_heap_uf
 * ```
 */
void runExpirement(int N){
    // Contar el tiempo de construcción
    std::cout << "Creando grafo de " << N << " aristas \n";
    auto startConstruction = std::chrono::high_resolution_clock::now();
    // Crear N nodos
    std::vector<Node> nodos = {};
    for (int i=0; i<N; i++) nodos.push_back(Node());

    // Crear árbol con todas sus posibles aristas
    Graph G(nodos);

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
    
    G.print();
    printEdges(MST_array);
    printEdges(MST_array_opt);
    printEdges(MST_heap);
    printEdges(MST_heap_opt);

    // Verificar que todos obtuvieron el mismo peso
    if(!mismosPesos(MST_array, MST_array_opt, MST_heap, MST_heap_opt)){
        std::cerr << "Error: no se obtuvieron los mismos pesos\n";
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

    // Guardar resumen de datos como csv
    std::ofstream data("./csv/resultados.csv", std::ios::app);
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


/**
 * @brief Función principal del programa.
 *
 * Ejecuta una serie de experimentos para medir el rendimiento de distintas variantes
 * del algoritmo de Kruskal sobre grafos completos de tamaño creciente. Los resultados
 * se registran en un archivo CSV.
 *
 * ### Detalles del experimento:
 * - Se prueban tamaños de entrada N = 2^i con i en [5, 13] (de 32 a 8192 nodos).
 * - Cada tamaño se ejecuta 5 veces.
 *
 * @return int 0 si el programa finaliza correctamente.
 */
int main(){

    for(int i=5; i<=13; i++){
        int N = std::pow(2, i);
        for(int j=0; j<5; j++){
            runExpirement(N);
        }
    }

    return 0;
}