#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main(){


    int des=1;
    int dis, n,m,j,k;
    int count =1;
    while(des!=0){
        cout<<"Elige las dimensiones de la primera matriz: ";
        cin>>n>>m;
        cout<<"\nElige las dimensiones de la segunda matriz: ";
        cin>>j>>k;
        vector<vector<int>>mat1(n, vector<int>(m,0));//segun los numeros introducidos por consola se generan las dos matrices
        vector<vector<int>>mat2(j, vector<int>(k,0));//la primera es n x m y la segunda es j x k

        random_device rd;  
        mt19937 gen(rd()); 
        uniform_int_distribution<> dist(1, 10);//se introducen numeros del 1 al 10 en cada casilla
        int random_number;
    
        for(int i=0; i<n;i++){
            for(int ii=0; ii<m; ii++){
                random_number = dist(gen);
                mat1[i][ii] = random_number;
              
            }
        }
        for(int i=0; i<j;i++){
            for(int ii=0; ii<k; ii++){
                random_number = dist(gen);
                mat2[i][ii] = random_number;
     
            }

        }


        
        
        //vector<vector<int>> res= mmul(mat1,mat2); multiplicacion de matrices

    
        cout<<"Desea continuar(1 si, 0 no): ";
        cin>>des;
    }

    return 0;
}
