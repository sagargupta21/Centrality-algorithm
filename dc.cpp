#include <bits/stdc++.h>
using namespace std;

map<int,list<int>>adj;

int main() {
    ifstream infile("graph.txt");
    //ifstream infile("roadNet-CA.txt");
    // ifstream infile("roadNet-PA.txt");
    // ifstream infile("roadNet-TA.txt");

    int u,v;
    while (infile >> u >> v) {
        adj[u].push_back(v);
    }
    infile.close();
    //cout<<adj.size()<<endl;
    
    map<int,int>dc;
    map<int,list<int>>m;

    //counting number of neighbours in each node and saving them
    map<int,list<int>>::iterator k;
    list<int>::iterator d;
    for(k=adj.begin();k!=adj.end();k++){
        int count=0;
        for(d=adj[k->first].begin();d!=adj[k->first].end();d++){
            count++;
        }
        dc[k->first]=count;
    }

    cout<<"The degree centraility of each vertex is:\n";

    map<int,int>::iterator itr;
    for(itr=dc.begin();itr!=dc.end();itr++){
        m[itr->second].push_back(itr->first);
        cout<<itr->first<<" "<<itr->second<<endl;
    }
    cout<<m.size()<<"\n";

    cout<<"\nTherefore the vertex having the same DC vertex are:\n";
    for(k=m.begin();k!=m.end();k++){
        cout<<k->first<<"->";
        for(d=m[k->first].begin();d!=m[k->first].end();d++){
            cout<<*d<<" ";
        }
        cout<<endl;
    }
    return 0;
}
