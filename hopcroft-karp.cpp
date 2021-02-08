#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
#include <queue>
using namespace std;

const int INF=10000;
int v;
int m=0,n=0;
int colour[1000];


bool bipartite(int start, vector<int> adj[]){
  list<int> queue_structure;
  vector<int> explored_vertices;

  fill_n(colour, v , -1);

  queue_structure.push_back(start);
  int current_vertex;
while(queue_structure.empty()==false){
  current_vertex=queue_structure.front();
  queue_structure.pop_front();
  if(colour[current_vertex]==-1){
    colour[current_vertex]=0;
  }
  vector<int>::iterator it;
  it=find(explored_vertices.begin(), explored_vertices.end(), current_vertex);
  if((it==explored_vertices.end())){
    explored_vertices.push_back(current_vertex);
    int i=0;
    while(i<adj[current_vertex].size()){
      it=find(explored_vertices.begin(), explored_vertices.end(), adj[current_vertex][i]);
      if((it==explored_vertices.end())){
        queue_structure.push_back(adj[current_vertex][i]);
        if((colour[current_vertex]==0&&colour[adj[current_vertex][i]]==-1)||(colour[current_vertex]==0&&colour[adj[current_vertex][i]]==1))
          colour[adj[current_vertex][i]]=1;
        else if((colour[current_vertex]==1&&colour[adj[current_vertex][i]]==-1)||(colour[current_vertex]==1&&colour[adj[current_vertex][i]]==0))
          colour[adj[current_vertex][i]]=0;
        else
          return false;

      }
      i++;
    }
}
}
cout<<"The two bipartite Sets are: ------\nU\n"<<endl;
for(int i=0; i<v; i++){
  if(colour[i]==0){
    cout<<i<<endl;
    m++;
  }

  else if(colour[i]==1){
    n++;
  }
}
cout<<"\nV\n"<<endl;
for(int i=0; i<v; i++){
  if(colour[i]==1){
      cout<<i<<endl;
  }
}
return true;
}




bool bfs(vector<int> &pairU, vector<int> &pairV,  vector<int> &dist, vector<int> adj[] ){
  queue<int> Q;
  for (int u=1; u<=m; u++)
  {
    if (pairU[u]==0)
    {
        dist[u] = 0;
        Q.push(u);
      }
      else dist[u] = INF;
    }
    dist[0] = INF;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
  
        if(dist[u] < dist[0])
        {

            for(auto x:adj[u])
            {
                if (dist[pairV[x]] == INF)
                {
                    dist[pairV[x]] = dist[u] + 1;
                    Q.push(pairV[x]);
                }

          }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u, vector<int> &pairU, vector<int> &pairV, vector<int> &dist, vector<int> adj[])
{
    if (u != 0)
    {
        for (auto v:adj[u])
        {
            if (dist[pairV[v]] == dist[u]+1)
            {
                if (dfs(pairV[v], pairU, pairV, dist, adj) == true)
                {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}


int Hopkroft_Karp(vector<int> U[]){

  vector<int>pairU(m+1);
  vector<int>pairV(n+1);
  vector<int>dist(m+1);
  int matching =0;
  while(bfs(pairU, pairV, dist, U)){
    for (int i=0; i<m; i++)
       {
         if(pairU[i]==0 && dfs(i, pairU, pairV, dist, U))
            {
              matching++;
            }
       }
  }

  return matching;
}

int main(){
  int x,y,e;
  bool bipart;
  int matching;

  cout<<"Enter the number of nodes: "<<endl;
  cin>>v;
  cout<<"Enter the number of edges: "<<endl;
  cin>>e;
  vector<int> U[v];
  vector<int> adj[v];
  for(int i=0;i<e;i++){
    cout<<"Enter the vertices of any edge: "<<endl;
    cin>>x>>y;
    U[x].push_back(y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

bipart=bipartite(0,adj);
if(bipart){
  matching =Hopkroft_Karp(U);
  cout<<"\nTotal Maximum Number of Matchings are: "<<matching+1<<endl;
}
else
  cout<<"The graph is not bipartite"<<endl;

  return 0;
}
