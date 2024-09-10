#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

/*Parametros: vector<int>& v, este será el vector a ordenar
  Resumen: Este algoritmo recorre el vector haciendo un swap de valores si un elemento es mayor al elemento que le sigue
  Return: No hay return
*/
void bubbleSort(vector<int>& v) {
    int n = v.size();                       //obtiene el tamaño
    for (int i = 0; i < n - 1; i++) {       //ejecuta un for que se repite n-1 veces
        for (int j = 0; j < n - i - 1; j++){//ejecuta un for que solo va desde 0 hasta n-i debido a que los elementos mas grandes "flotaron"
            if (v[j] > v[j + 1])            
                swap(v[j], v[j + 1]);       //si un elemento es mayor al elemento siguiente se intercambian
        }
    }
}

int main(){
    ofstream results("results.txt");

    int des=1;
    int dis, n;
    int count =1;
    while(des!=0){
        cout<<"Elige que distribucion quieres usar(1 aleatoria, 2 semi ordenada): ";
        cin>>dis;
        cout<<"\nElige el tamaño del vector: ";
        cin>>n;
        vector<int> v(n); 
        string txt = "dataset"+to_string(count)+".txt";
        ofstream dataset(txt);
        if(dis==1){
            random_device rd;  //La generación aleatoria fue obtenida a través de ChatGPT
            mt19937 gen(rd());  
            uniform_int_distribution<> dist(1, n); 
            int random_number = dist(gen);

            for(int i=0; i<n;i++){
                v.push_back(random_number);
                dataset<<random_number<<" ";
                random_number = dist(gen);
            }
        }else if(dis==2){
            int d = n/2;
            for(int i=0;i<d;i++){
                v.push_back(i);
                dataset<<i<<" ";
            }
            for(int i=0;i<d;i++){
                v.push_back(i);
                dataset<<i<<" ";
            }
        }
        dataset.close();

        auto start = chrono::high_resolution_clock::now();


        bubbleSort(v);

        cout << "Sorted vector\n";

        auto end = chrono::high_resolution_clock::now();
    
        chrono::duration<double> duration = end - start;

        cout << "Tiempo transcurrido: " << duration.count() << " segundos" << "\n";

        results<<"Dataset"<<count<<" Tamaño "<<n;
        if(dis ==1) results<<", aleatorio ";
        else if(dis ==2) results<<", semi ordenado ";
        results<<", tiempo transcurrido: "<<duration.count()<<"\n";


        count++;
        cout<<"Desea continuar(1 si, 0 no): ";
        cin>>des;
    }
    results.close();
    return 0;
}