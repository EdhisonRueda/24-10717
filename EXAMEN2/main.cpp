#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "cargar_datos.h"
#include "mi_Kmeans.h"
#include "gen_archivos.h"

using std::vector;


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Uso incorrecto. Debe invocarse asi:\n";
        std::cerr << "cluster <k> <archivo_datos>\n";
        return 1;
    }

    int k = std::stoi(argv[1]);
    std::string nombre_archivo = argv[2];


    vector<Coord_3D> P = cargar_datos("datos.csv");

    if (P.empty()) {
        return 1; 
    }

    vector<double> MDi;
    vector<vector<Coord_3D>> clusters;

    std::cout << "clusters: " << k << "\n";
    
    std::cout << "\n buscando centroides iniciales \n";
    vector<Coord_3D> centroides = paso1(k, P);
    std::cout << "centroides iniciales encontrados \n";

    std::cout << "\n calculando medida de dispersion \n";    
    double cambio_medida_dispersion = paso4(P, centroides, clusters, MDi);
    std::cout << "medida de dispersion calculada \n";
   
    std::cout << "\n MEDIA DE DISPERSION GLOBAL: " << cambio_medida_dispersion << "\n";
    
    generarSummary("Summary.txt", centroides, clusters, MDi);
    generarClasificados("Clasificados.csv", clusters);

     return 0;
}