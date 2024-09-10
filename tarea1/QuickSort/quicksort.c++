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
int partition(vector<int> &vec, int low, int high) {
    random_device rd;
    mt19937 gen(rd());  
    uniform_int_distribution<> dist(low, high); 
    int random_number = dist(gen);
    // Selecting last element as the pivot
    swap(vec[random_number],vec[high]);
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
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
            int random_number;

            for (int i = 0; i < n; i++) {
                random_number = dist(gen);  // Generar nuevo número en cada iteración
                v[i] = random_number;           // Asignación directa
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


        quickSort(v,0,n-1);

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