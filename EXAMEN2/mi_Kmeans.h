#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>

#include "operaciones.h"

// PASO 1: SELECCIONAR K CENTROIDES ALEATORIAMENTE

vector<Coord_3D> paso1(const int& k, const vector<Coord_3D>& P) {
    std::random_device semillaC;
    std::mt19937 genC(semillaC());
    std::uniform_int_distribution<int> distribucion(0, P.size() - 1);

    vector<Coord_3D> centroides;

    for (int i = 0; i < k; i++) {

int icent = distribucion(genC);

    centroides.push_back(P[icent]);

    }
    return centroides;
}

// PASO 2: ASIGNAR CADA PUNTO AL CENTROIDE MÁS CERCANO

vector<vector<Coord_3D>> paso2(vector<Coord_3D> P, vector<Coord_3D> Centroides) {

int k = Centroides.size();
vector<vector<double>> Ds;

for(int o = 0; o < k; o++) {

    vector<double> P_C;

    for (size_t i = 0; i < P.size(); i++) {

        double DistP_C = Distancia(P[i], Centroides[o]);
        P_C.push_back(DistP_C);

    }

    Ds.push_back(P_C);

}

    
vector<vector<Coord_3D>> clusters(k);

    for (size_t j = 0; j < Ds[0].size(); j++) {

        int p_menor = 0;
        double elemm = 999999.0;

        for (size_t q = 0; q < Ds.size(); q++) {
            
            if (Ds[q][j] < elemm) {

                elemm = Ds[q][j]; 
                p_menor = q;
            }    
        }
        
        clusters[p_menor].push_back(P[j]);
    }

    return clusters;
}

// PASO 3: ACTUALIZAR LOS CENTROIDES

vector<Coord_3D> paso3(vector<vector<Coord_3D>> clusters, vector<Coord_3D> Centroides) {

    
for (size_t i = 0; i < clusters.size(); i++) {

    double suma_x = 0;
    double suma_y = 0;
    double suma_z = 0;


     for (size_t j = 0; j < clusters[i].size(); j++) {

         suma_x = suma_x + clusters[i][j].x;
         suma_y = suma_y + clusters[i][j].y;
         suma_z = suma_z + clusters[i][j].z;
    }
    if (clusters[i].size() > 0) {
    double prom_x = suma_x / clusters[i].size(); 
    double prom_y = suma_y / clusters[i].size();
    double prom_z = suma_z / clusters[i].size();

    Centroides[i] = {prom_x, prom_y, prom_z};
    }
}
    return Centroides;
}

//PASO 4: REPETIR PASOS 2 Y 3 HASTA QUE SE CUMPLA LA CONDICIÓN DE PARADA


 // Función: condicion_parada:
bool condicion_parada(double J) {
    return J <= 1.0;
}
 // Parámetros:
 // J: Es la diferencia absoluta entre la inercia anterior y la actual.
 //    Cuando J es menor o igual a 1, significa que los 
 //    centroides casi no se movieron. El algoritmo se ha estabilizado y 
 //    seguir iterando solo gastaría recursos de la computadora sin mejorar los grupos.
 

double paso4(vector<Coord_3D>& P, vector<Coord_3D>& Centroides,  vector<vector<Coord_3D>>& clusters, vector<double>& mds_indiv) {
    double EV = 9999;
    double EN = 0;
    double J = 100;
    
    while (!condicion_parada(J)) {
         clusters = paso2(P, Centroides);
         Centroides = paso3(clusters, Centroides);

        double md = 0;
        for (size_t i = 0; i < clusters.size(); i++) {
            double mdj = 0;
        for (size_t j = 0; j < clusters[i].size(); j++) {
            mdj = mdj + (Distancia(clusters[i][j], Centroides[i]) * Distancia(clusters[i][j], Centroides[i]));
          }
            md = md + mdj;
            
           
        }
            
        EN = md;
        J = abs(EV - EN);
        EV = EN;
        std::cout << "\nJ = " << J;

    

    }

    for (size_t i = 0; i < clusters.size(); i++) {
        double mdj_final = 0;
        for (size_t j = 0; j < clusters[i].size(); j++) {
            mdj_final = mdj_final + (Distancia(clusters[i][j], Centroides[i]) * Distancia(clusters[i][j], Centroides[i]));
        }
        mds_indiv.push_back(mdj_final); 

        std::cout << "\nCluster " << i + 1 << " -> Dispersión final: " << mdj_final << "\n";
    }
    
    return EV;
}
    