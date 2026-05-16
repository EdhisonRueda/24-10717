#include <vector>
#include <cmath>

using namespace std;

int main(){
  return 0;
}

double mean(vector<double> v){
  double acumulado = 0;
    for(size_t contador = 0; contador < v.size(); contador++) {
        acumulado = acumulado +  v[contador];
    }
    double promedio = acumulado / v.size();
    return promedio;
}

double variance(vector<double> v){
  double promedio2 = 0;
    promedio2 = promedio2 + mean(v);
    double acumulado2 = 0;
    for(size_t contador = 0; contador < v.size(); contador++) {
        acumulado2 = acumulado2 + (v[contador] - promedio2)*(v[contador] - promedio2);
    }
    double varianza = acumulado2 / (v.size() - 1);
    return varianza;
}

double pearson_r(vector<double> A, vector<double> B){
  double promedioA = 0;
    promedioA = promedioA + mean(A);
    double promedioB = 0;
    promedioB = promedioB + mean(B);
    double acumuladoAB = 0;
    double acumuladoA_cuadrado = 0;
    double acumuladoB_cuadrado = 0;
    double acumuladoAB_cuadrado = 0;
    for(size_t contador = 0; contador < A.size(); contador++){
    acumuladoAB = acumuladoAB + (A[contador] - promedioA)*(B[contador] - promedioB);
    acumuladoA_cuadrado = acumuladoA_cuadrado + (A[contador] - promedioA)*(A[contador] - promedioA);
    acumuladoB_cuadrado = acumuladoB_cuadrado + (B[contador] - promedioB)*(B[contador] - promedioB);
    }
    acumuladoAB_cuadrado = sqrt(acumuladoAB_cuadrado + acumuladoA_cuadrado*acumuladoB_cuadrado);
    double coef_corr = acumuladoAB / acumuladoAB_cuadrado;
    return coef_corr;
}


vector<char> dec_to_septapus(int n){
    vector<char> resultado;
    if (n == 0) return {'0'};
    while(n > 0) {
        resultado.push_back((n % 7) + '0');
        n = n / 7;
    }
    vector<char> resultado_final; 
    for(int contador = resultado.size() - 1; contador >= 0; contador--) {
        resultado_final.push_back(resultado[contador]);
    }
    return resultado_final;
}

vector<char> dec_to_octopus(int n){
    vector<char> resultado;
    if (n == 0) return {'0'};
    
    while(n > 0) {
        resultado.push_back((n % 8) + '0');
        n = n / 8;
    }
    vector<char> resultado_final; 
    for(int contador = resultado.size() - 1; contador >= 0; contador--) {
        resultado_final.push_back(resultado[contador]);
    }
    return resultado_final;
}

vector<char> dec_to_hexakaidecapus(int n){
    vector<char> resultado;
    if (n == 0) return {'0'};
    
    while(n > 0) {
        int residuo = n % 16;
        if (residuo < 10) {
            resultado.push_back(residuo + '0');
        } else {
            resultado.push_back((residuo - 10) + 'A');
        }
        n = n / 16;
    }
    vector<char> resultado_final; 
    for(int contador = resultado.size() - 1; contador >= 0; contador--) {
        resultado_final.push_back(resultado[contador]);
    }
    return resultado_final;
}

vector<char> septapus_to_dec(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        total = (total * 7) + (s[contador] - '0');
    }
    
    vector<char> resultado;
    if (total == 0) return {'0'};
    while(total > 0) {
        resultado.push_back((total % 10) + '0');
        total = total / 10;
    }
    vector<char> resultado_final; 
    for(int contador = resultado.size() - 1; contador >= 0; contador--) {
        resultado_final.push_back(resultado[contador]);
    }
    return resultado_final;
}

vector<char> octopus_to_dec(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        total = (total * 8) + (s[contador] - '0');
    }
    
    vector<char> resultado;
    if (total == 0) return {'0'};
    while(total > 0) {
        resultado.push_back((total % 10) + '0');
        total = total / 10;
    }
    vector<char> resultado_final; 
    for(int contador = resultado.size() - 1; contador >= 0; contador--) {
        resultado_final.push_back(resultado[contador]);
    }
    return resultado_final;
}

vector<char> hexakaidecapus_to_dec(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        int valor_digito = 0;
        if (s[contador] >= '0' && s[contador] <= '9') {
            valor_digito = s[contador] - '0';
        } else if (s[contador] >= 'A' && s[contador] <= 'F') {
            valor_digito = (s[contador] - 'A') + 10;
        }
        total = (total * 16) + valor_digito;
    }
    
    vector<char> resultado;
    if (total == 0) return {'0'};
    while(total > 0) {
        resultado.push_back((total % 10) + '0');
        total = total / 10;
    }
    vector<char> resultado_final; 
    for(int contador = resultado.size() - 1; contador >= 0; contador--) {
        resultado_final.push_back(resultado[contador]);
    }
    return resultado_final;
}

vector<char> septapus_to_octopus(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        total = (total * 7) + (s[contador] - '0');
    }
    return dec_to_octopus(total);
}

vector<char> septapus_to_hexakaidecapus(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        total = (total * 7) + (s[contador] - '0');
    }
    return dec_to_hexakaidecapus(total);
}

vector<char> octapus_to_septapus(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        total = (total * 8) + (s[contador] - '0');
    }
    return dec_to_septapus(total);
}

vector<char> octopus_to_hexakaidecapus(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        total = (total * 8) + (s[contador] - '0');
    }
    return dec_to_hexakaidecapus(total);
}

vector<char> hexakaidecapus_to_septapus(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        int valor_digito = 0;
        if (s[contador] >= '0' && s[contador] <= '9') {
            valor_digito = s[contador] - '0';
        } else if (s[contador] >= 'A' && s[contador] <= 'F') {
            valor_digito = (s[contador] - 'A') + 10;
        }
        total = (total * 16) + valor_digito;
    }
    return dec_to_septapus(total);
}

vector<char> hexakaidecapus_to_octopus(vector<char> s){
    int total = 0;
    for(size_t contador = 0; contador < s.size(); contador++) {
        int valor_digito = 0;
        if (s[contador] >= '0' && s[contador] <= '9') {
            valor_digito = s[contador] - '0';
        } else if (s[contador] >= 'A' && s[contador] <= 'F') {
            valor_digito = (s[contador] - 'A') + 10;
        }
        total = (total * 16) + valor_digito;
    }
    return dec_to_octopus(total);
}
