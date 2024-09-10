#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;


int partition(vector<int> &vec, int low, int high) {
    random_device rd;
    mt19937 gen(rd());  
    uniform_int_distribution<> dist(low, high); 
    int random_number = dist(gen);
    swap(vec[random_number],vec[high]);
    int pivot = vec[high];


    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);

    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {

    if (low < high) {


        int pi = partition(vec, low, high);

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
