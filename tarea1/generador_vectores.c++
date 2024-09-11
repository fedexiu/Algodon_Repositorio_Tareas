#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

//sort()

int main(){
    ofstream results("results.txt");

    int des=1;
    int dis, n;
    while(des!=0){
        cout<<"Elige que distribucion quieres usar(1 aleatoria, 2 semi ordenada): ";
        cin>>dis;
        cout<<"\nElige el tamaño del vector: ";
        cin>>n;
        vector<int> v(n); //dependiendo de la elección v será un vector desordenado o uno semi ordenado
        if(dis==1){
            random_device rd;  
            mt19937 gen(rd());  
            uniform_int_distribution<> dist(1, n); 
            int random_number;

            for (int i = 0; i < n; i++) {
                random_number = dist(gen); 
                v[i] = random_number;          
            }
        }else if(dis==2){
            int d = n/2;
            for(int i=0;i<d;i++){
                v[i]=i;
            }
            for(int i=0;i<d;i++){
                v[i+d]=i;
            }
        }

        //sort_a_eleccion(v);

        cout<<"Desea continuar(1 si, 0 no): ";
        cin>>des;
    }
    return 0;
}
