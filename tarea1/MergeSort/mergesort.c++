#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

/*Parametros: vector<int>& arr, este será el vector a ordenar
              int left,
              int mid,
              int right,
  Resumen: Este algoritmo toma dos subvectores que ya están ordenados y los junta para crear un vector ordenado.
  Return: No hay return
*/
void merge(vector<int>& arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*Parametros: vector<int>& arr, este será el vector a ordenar
              int left,
              int right,
  Resumen: Este algoritmo separa el vector en subvectores para ordenar estos primero y luego hacer un merge en el que el vector original este ordenado
  Return: No hay return
*/
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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
            int random_number;

            for (int i = 0; i < n; i++) {
                random_number = dist(gen); 
                v[i] = random_number;          
                dataset << random_number << " ";
            }
        }else if(dis==2){
            int d = n/2;
            for(int i=0;i<d;i++){
                v[i]=i;
                dataset<<i<<" ";
            }
            for(int i=0;i<d;i++){
                v[i+d]=i;
                dataset<<i<<" ";
            }
        }
        dataset.close();

        auto start = chrono::high_resolution_clock::now();


        mergeSort(v,0,n-1);

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