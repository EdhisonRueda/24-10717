#ifndef SALIDA_H
#define SALIDA_H

#include <iostream>
#include <fstream>
#include <vector>



void generarSummary(const std::string& nombre_archivo, const vector<Coord_3D>& centroides, const vector<vector<Coord_3D>>& clusters, const vector<double>& mds_indiv) {

    std::ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al crear el archivo " << nombre_archivo << "\n";
        return;
    }


    for (size_t i = 0; i < clusters.size(); i++) {
        
        char etiqueta = 'A' + i; 
        int N = clusters[i].size();

        archivo << etiqueta << ": " << N << ", (" << centroides[i].x << ", " << centroides[i].y << ", " << centroides[i].z << "), " << mds_indiv[i] << "\n";
    }

    archivo.close();
    std::cout << "\n Nuevo archivo.txt '" << nombre_archivo << "' generado con éxito.\n";
}



void generarClasificados(const std::string& nombre_archivo, const vector<vector<Coord_3D>>& clusters) {

    std::ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al crear el archivo " << nombre_archivo << "\n";
        return;
    }

    
    for (size_t i = 0; i < clusters.size(); i++) {
        
        char etiqueta = 'A' + i;

        for (size_t j = 0; j < clusters[i].size(); j++) {
            
            archivo << clusters[i][j].x << "," << clusters[i][j].y << "," << clusters[i][j].z << "," << etiqueta << "\n";
        }
    }

    archivo.close();
    std::cout << "Nuevo archivo.csv '" << nombre_archivo << "' generado con éxito.\n";
}

#endif