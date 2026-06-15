#include <vector>
#include <cmath>


double Distancia(const Coord_3D& a, const Coord_3D& b) {

    double Dx = b.x - a.x;
    double Dy = b.y - a.y;
    double Dz = b.z - a.z;

    double DistT =  sqrt((Dx * Dx) + (Dy * Dy) + (Dz * Dz));
    return DistT;
}

