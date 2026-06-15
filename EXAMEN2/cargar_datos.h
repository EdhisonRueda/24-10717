#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Coord_3D.h"

using std::vector;


vector<Coord_3D> cargar_datos(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if (!archivo.is_open()){
        std::cout << "ERROR => No se pudo abrir el archivo " << nombre_archivo << "\n";
        return {};
    }

    std::vector<Coord_3D> puntos;
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream flujo(linea);
        std::string texto_x, texto_y, texto_z;

        std::getline(flujo, texto_x, ',');
        std::getline(flujo, texto_y, ',');
        std::getline(flujo, texto_z);

        Coord_3D nuevo_punto;
        nuevo_punto.x = std::stod(texto_x);
        nuevo_punto.y = std::stod(texto_y);
        nuevo_punto.z = std::stod(texto_z);

        puntos.push_back(nuevo_punto);

    }
    return puntos;
}
