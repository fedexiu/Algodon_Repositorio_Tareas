#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

void add_matrix(vector<vector<int> > matrix_A,vector<vector<int> > matrix_B,vector<vector<int> >& matrix_C,int split_index){
    for (auto i = 0; i < split_index; i++)
        for (auto j = 0; j < split_index; j++)
            matrix_C[i][j]= matrix_A[i][j] + matrix_B[i][j];
}
 
vector<vector<int>> Strassen(vector<vector<int> > matrix_A,vector<vector<int> > matrix_B){
    int col_1 = matrix_A[0].size();
    int row_1 = matrix_A.size();
    int col_2 = matrix_B[0].size();
    int row_2 = matrix_B.size();
 
    if (col_1 != row_2) {
        cout << "\nError: The number of columns in Matrix "
                "A  must be equal to the number of rows in "
                "Matrix B\n";
        return {};
    }
 
    vector<int> result_matrix_row(col_2, 0);
    vector<vector<int> > result_matrix(row_1,result_matrix_row);
 
    if (col_1 == 1)
        result_matrix[0][0]
            = matrix_A[0][0] * matrix_B[0][0];
    else {
        int split_index = col_1 / 2;
 
        vector<int> row_vector(split_index, 0);
        vector<vector<int> > result_matrix_00(split_index,row_vector);
        vector<vector<int> > result_matrix_01(split_index,row_vector);
        vector<vector<int> > result_matrix_10(split_index,row_vector);
        vector<vector<int> > result_matrix_11(split_index,row_vector);
 
        vector<vector<int> > a00(split_index, row_vector);
        vector<vector<int> > a01(split_index, row_vector);
        vector<vector<int> > a10(split_index, row_vector);
        vector<vector<int> > a11(split_index, row_vector);
        vector<vector<int> > b00(split_index, row_vector);
        vector<vector<int> > b01(split_index, row_vector);
        vector<vector<int> > b10(split_index, row_vector);
        vector<vector<int> > b11(split_index, row_vector);
 
        for (auto i = 0; i < split_index; i++)
            for (auto j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + split_index];
                a10[i][j] = matrix_A[split_index + i][j];
                a11[i][j] = matrix_A[i + split_index][j + split_index];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + split_index];
                b10[i][j] = matrix_B[split_index + i][j];
                b11[i][j] = matrix_B[i + split_index][j + split_index];
            }
 
        add_matrix(Strassen(a00, b00),Strassen(a01, b10),result_matrix_00, split_index);
        add_matrix(Strassen(a00, b01),Strassen(a01, b11),result_matrix_01, split_index);
        add_matrix(Strassen(a10, b00),Strassen(a11, b10),result_matrix_10, split_index);
        add_matrix(Strassen(a10, b01),Strassen(a11, b11),result_matrix_11, split_index);
 
        for (auto i = 0; i < split_index; i++)
            for (auto j = 0; j < split_index; j++) {
                result_matrix[i][j]= result_matrix_00[i][j];
                result_matrix[i][j + split_index]= result_matrix_01[i][j];
                result_matrix[split_index + i][j]= result_matrix_10[i][j];
                result_matrix[i + split_index][j + split_index]= result_matrix_11[i][j];
            }
 
        result_matrix_00.clear();
        result_matrix_01.clear();
        result_matrix_10.clear();
        result_matrix_11.clear();
        a00.clear();
        a01.clear();
        a10.clear();
        a11.clear();
        b00.clear();
        b01.clear();
        b10.clear();
        b11.clear();
    }
    return result_matrix;
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
        
        vector<vector<int>> res= Strassen(mat1,mat2);


        auto end = chrono::high_resolution_clock::now();
    
        chrono::duration<double> duration = end - start;

        cout << "Tiempo transcurrido: " << duration.count() << " segundos" << "\n";
        results<<"Dataset"<<count;
        results<<", tamaño de la primera matriz "<<n<<" x "<<m<<", tamaño de la segunda matriz "<<j<<" x "<<k<<", tiempo transcurrido: "<<duration.count()<<"\n";


        count++;
        cout<<"Desea continuar(1 si, 0 no): ";
        cin>>des;
    }
    results.close();
    return 0;
}