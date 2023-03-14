#include <bits/stdc++.h>
using namespace std;

map<int,list<pair<int,int>>>adj;

void read_graph() {
    ifstream file("graph.txt");
    // ifstream infile("roadNet-CA.txt");
    // ifstream infile("roadNet-PA.txt");
    // ifstream infile("roadNet-TA.txt");

    // storing it in a map graph "adj" or creating an adjacency list
    int u, v, w;
    while (file >> u >> v >> w) {
        adj[u].push_back(make_pair(v, w));
    }
    file.close();
}

void closeness_centrality(int source,vector<int>&dist){
    set<pair<int,int>>st;
    dist[source]=0;
    st.insert(make_pair(0,source));

    while(!st.empty()){
        auto top= *(st.begin());
        int nodeDistance=top.first;
        int topNode=top.second;

        st.erase(st.begin());
        for(auto neighbour:adj[topNode]){
            if((nodeDistance+neighbour.second)<dist[neighbour.first]){
                auto record=st.find(make_pair(dist[neighbour.first],neighbour.first));
                if(record!=st.end()){
                    st.erase(record);
                }
                dist[neighbour.first]=nodeDistance+neighbour.second;
                st.insert(make_pair(dist[neighbour.first],neighbour.first));
            }
        }
    }
}

int main() {
    read_graph();

    // for(auto i:adj){
    //     cout<<i.first<<"->";
    //     for(auto j:i.second){
    //         cout<<"["<<j.first<<","<<j.second<<"],";
    //     }
    //     cout<<endl;
    // }

    int s=adj.size();
    map<int,int>cc;

    for(auto itr:adj){
        vector<int>dist(s,INT_MAX);
        int source=itr.first, count=0;
        //cout<<source<<" "<<count;
        closeness_centrality(source,dist);

        for(int a=0;a<s;a++){
            count+=dist[a];
        }
        //cout<<"=>"<<count<<endl;

        cc[source]=count;
        dist.clear();
    }

    map<int,list<int>>m;
    cout<<"\nThe closeness centrality of each vertex is:";
    for(auto i:cc){
        cout<<i.first<<"->"<<i.second<<"\n";
        m[i.second].push_back(i.first);
    }
    cout<<"\n---------\n";

    cout<<"\nTherefore the vertex having the same CC vertex are:\n";
    for(auto k:m){
        cout<<k.first<<"->";
        for(auto j:k.second)
            cout<<j<<" ";

        cout<<"\n";
    }
    return 0;
}
