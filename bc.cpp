#include <bits/stdc++.h>
using namespace std;

map<int,list<pair<int,int>>>adj;
int s,t;
const double INF = 1e9;

void read_graph() {
    ifstream file("graph.txt");
    // ifstream infile("roadNet-CA.txt");
    // ifstream infile("roadNet-PA.txt");
    // ifstream infile("roadNet-TA.txt");

    // storing it in a map graph "adj" or creating an adjacency list
    int u, v;
    double w;
    while (file >> u >> v >> w) {
        adj[u].push_back(make_pair(v, w));
    }
    file.close();
}

void bfs(int s,vector<double>&dist,vector<bool>&vis,vector<int>&cnt,vector<double>&betweeness,int n){
    queue<int>q;
    q.push(s);
    dist[s] = 0;
    cnt[s] = 1;
    vis[s] = true;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u] = false;
        for (auto e : adj[u]){
            int v = e.first;
            double w = e.second;
            if (dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u];
                if (!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
            else if (dist[v] == dist[u] + w){
                cnt[v] += cnt[u];
                if (!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        betweeness[i] += (double)cnt[i] / (double)cnt[t];
    }
}


int main(){
    read_graph();
    int n=adj.size();
    vector<double>dist(n,INF);
    vector<bool>vis(n,false);
    vector<int>cnt(n,0);
    vector<double>betweeness(n,0);

    for (auto x:adj){
        for (auto y:adj){
            s=x.first;
            t=y.first;
            if (s!=t){
                bfs(s,dist,vis,cnt,betweeness,n);
            }
        }
    }
    cout<<"\nThe betweeness centrality of the vertices is:\n";
    int i=-1;
    for(auto r:adj){
        cout<<r.first<<":   "<<betweeness[++i]<<endl;
    }
    
    return 0;
}
