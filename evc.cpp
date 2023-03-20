#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <cmath>
#include <vector>
using namespace std;

map<int,list<int>>adj;
map<int,list<int>>::iterator k=adj.begin();

void read_graph() {
    ifstream file("graph.txt");
    // ifstream infile("roadNet-CA.txt");
    // ifstream infile("roadNet-PA.txt");
    // ifstream infile("roadNet-TA.txt");

    // storing it in a map graph "adj" or creating an adjacency list
    int u, v, w;
    while (file >> u >> v >> w) {
        adj[u].push_back(v);
    }
    file.close();
}

void creatematrix(vector<vector<int>>&mat){
    for(auto i:adj){
        int u=i.first;
        for(auto j:i.second){
            int v=j;
            if(k->first!=0)
                mat[u][v]=1;
            else
                mat[u-1][v-1]=1;
        }
    }
}

void evc(vector<vector<float>>&v, vector<vector<int>>&mat, int n){
    vector<vector<float>>v1(n, vector<float>(1, 0));
    float norm = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            v1[i][0] += mat[i][j] * v[j][0];
        }
        norm += v1[i][0] * v1[i][0];
    }
    norm = sqrt(norm);
    for (int i = 0; i < n; i++) {
        v1[i][0] /= norm;
    }
    v = v1;
}

void display(vector<vector<float>>&v){
    int x=-1;
    for(auto i:adj)
        cout<<i.first<<":  "<<v[++x][0]<<endl;
}

int main(){
    read_graph();
    int n=adj.size();
    vector<vector<int>>mat(n,vector<int>(n,0));
    creatematrix(mat);

    vector<vector<float>>v(n,vector<float>(1,1.0));
    vector<vector<float>>v1(n,vector<float>(1,0));
    float epsilon = 1e-6;
    while (true) {
        v1 = v;
        evc(v, mat, n);
        float diff = 0;
        for (int i = 0; i < n; i++) {
            diff += fabs(v[i][0] - v1[i][0]);
        }
        if (diff < epsilon) {
            break;
        }
    }
  
    display(v);
    return 0;
}

