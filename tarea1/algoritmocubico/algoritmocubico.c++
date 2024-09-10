#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mmul(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
    int n = mat1.size();        // Número de filas de la primera matriz
    int m = mat2[0].size();     // Número de columnas de la segunda matriz
    int common = mat1[0].size(); // Número de columnas de la primera matriz (igual al número de filas de la segunda)

    // Crear una matriz resultado de tamaño n x m inicializada con 0
    vector<vector<int>> result(n, vector<int>(m, 0));

    // Algoritmo clásico de multiplicación de matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < common; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}
int main(){
    ofstream results("results.txt");

    int des=1;
    int dis, n,m,j,k;
    int count =1;
    while(des!=0){
        cout<<"Elige las dimensiones de la primera matriz: ";
        cin>>n>>m;
        cout<<"\nElige las dimensiones de la segunda matriz: ";
        cin>>j>>k;
        vector<vector<int>>mat1(n, vector<int>(m,0));
        vector<vector<int>>mat2(j, vector<int>(k,0));
        string txt = "dataset"+to_string(count)+".txt";
        ofstream dataset(txt);
        random_device rd;  // Fuente de entropía
        mt19937 gen(rd()); // Generador Mersenne Twister (algoritmo de generación)
        uniform_int_distribution<> dist(1, 10); // Números entre 1 y n
        int random_number;
    
        for(int i=0; i<n;i++){
            for(int ii=0; ii<m; ii++){
                random_number = dist(gen);
                mat1[i][ii] = random_number;
                dataset<<random_number<<" ";
            }
            dataset<<"\n";
        }
        for(int i=0; i<j;i++){
            for(int ii=0; ii<k; ii++){
                random_number = dist(gen);
                mat2[i][ii] = random_number;
                dataset<<random_number<<" ";
            }
            dataset<<"\n";
        }
        dataset.close();

        auto start = chrono::high_resolution_clock::now();
        
        vector<vector<int>> res= mmul(mat1,mat2);


        auto end = chrono::high_resolution_clock::now();
    
        chrono::duration<double> duration = end - start;

        cout << "Tiempo transcurrido: " << duration.count() << " segundos" << "\n";
        results<<"Dataset"<<count<<" Tamaño "<<n;
        results<<", tamaño de la primera matriz "<<n<<" x "<<m<<", tamaño de la segunda matriz "<<j<<" x "<<k<<", tiempo transcurrido: "<<duration.count()<<"\n";


        count++;
        cout<<"Desea continuar(1 si, 0 no): ";
        cin>>des;
    }
    results.close();
    return 0;
}