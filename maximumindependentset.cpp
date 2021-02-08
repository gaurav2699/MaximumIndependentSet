#include<bits/stdc++.h>

using namespace std;


void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}


void printGraph(vector<int> adj[], int V)
{
	for (int v = 0; v < V; ++v)
	{
		cout << "\n Adjacency list of vertex "
			<< v << "\n head ";
		for (auto x : adj[v])
		cout << "-> " << x;
		printf("\n");
	}
}

vector <int> bfs(int start, vector<int> adj[], int V, int tempdegree[]){
  list<int> queue_structure;
  vector<int> explored_vertices;
  vector <int> colour(V, -1);


  queue_structure.push_back(start);
  int current_vertex;
  int k=0;
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
      if((it==explored_vertices.end()) && tempdegree[adj[current_vertex][i]]!=-1){
        queue_structure.push_back(adj[current_vertex][i]);
        if(colour[adj[current_vertex][i]]==-1)
        colour[adj[current_vertex][i]]=colour[current_vertex]+1;

      }
      i++;
    }
    k++;
}
}


return colour;
}

int deterministic(int tempdegree[],vector<int> solve, vector <int> adj[], int V) {
vector <int> tempcolour1[V];
vector <int> sum(V, -1);

int k=1;
for(int i=0; i<solve.size(); i++){
	tempcolour1[solve[i]] = bfs(solve[i], adj, V, tempdegree);
}

int m =0;
while(m<V){
for(int i=0; i<solve.size(); i++){
	sum[solve[i]]=0;
	for(int j=0; j<tempcolour1[solve[i]].size(); j++){
		if(tempcolour1[solve[i]][j]==k){
			if(tempdegree[j]!=-1)
				sum[solve[i]]+=tempdegree[j];

		}

		}
	}
int u, min, max;

if(k%2==1){
	for(int l=0; l<V; l++){
		if(sum[l]!=-1){
			max=sum[l];
			break;
		}
	}
	for(int l=0; l<V; l++){

		if(max<sum[l] && sum[l]!=-1){
			max=sum[l];

		}
	}
	u=max;
}
else{
	for(int l=0; l<V; l++){
		if(sum[l]!=-1){
			min=sum[l];
			break;
		}
	}
	for(int l=0; l<V; l++){

		if(min>sum[l] && sum[l]!=-1){
			min=sum[l];

		}
	}
	u=min;
}

solve.clear();

for(int l = 0;l < V;l++){

	if(sum[l] == u){
		solve.push_back(l);

	}
}

	if(solve.size() == 1){
		break;

	}
	else{
		for(int l=0; l<V; l++){
			sum[l]=-1;
		}
		k++;

	}
	m++;
}
return solve[0];



}


int min_degree(int tempdegree[], int V,vector<int> adj[]){
	int min;
	int i;
	for(i=0; i<V; i++){
		if(tempdegree[i]!=-1){
		  min=tempdegree[i];
			break;
		}
	}
	int index=i;
	vector <int> solve;
	int ind =0;
	for(int j=0; j<V; j++){

		if(min>tempdegree[j] && tempdegree[j]!=-1){
			min=tempdegree[j];
			index=j;
		}
	}
	solve.push_back(index);

	for(int i = 0;i < V;i++){

		if(i != index && tempdegree[i] == min){
			solve.push_back(i);

		}
	}
  for(int i=0; i<solve.size(); i++){
  }
	int final_index;
  if(solve.size()>1){
    index=deterministic(tempdegree, solve, adj, V);
  }


	return index;
}


vector <int> mis(vector<int> adj[], int V, int degree[]){
	int tempdegree[V];
	vector <int> MIS;
	vector<bool> inMIS(V, false);
	for(int i=0; i<V; i++){
		tempdegree[i]=degree[i];
	}


	int k=0;
	int z=0;
	while(z<V){
		int index=min_degree(tempdegree, V, adj);

		inMIS[index]=true;
		z++;
		MIS.push_back(index);
		k++;
		tempdegree[index]=-1;
		for(auto x : adj[index]){
			inMIS[x]=true;

			if(tempdegree[x]!=-1){
				tempdegree[x]=-1;
				z++;


			for(auto y : adj[x]){
				if(tempdegree[y]!=-1)
					tempdegree[y]-=1;
			}
		}
		}


}


	cout<<"\n";
	return MIS;
}

// Driver code
int main()
{
	int V = 0, E = 0;

    cout << "Enter number of vertices: " ;
    cin >> V;
    cout << "Enter number of edges: " ;
    cin >> E;
	int degree[V];
	vector<int> adj[V];
    int i;
    for(i=0; i<E; i++)
    {
      int v1,v2;
      cout << "Enter 2 adjacent vertices: ";
      cin >> v1;
      cin >> v2;
      addEdge(adj, v1, v2);
			cout<<"\n";
    }

	printGraph(adj, V);
	for(int i=0; i<V; i++){
		degree[i]=adj[i].size();
	}
int n_V=0;
vector <bool> adj_bool(V, false);
int colour[V];
int k=0;
vector <int> MIS;
MIS= mis(adj, V, degree);

cout<<"The maximum Independent set using Deterministic Greedy Algorithm is: ";
	for(int i=0; i<MIS.size(); i++){
		cout<<MIS[i]<<" ";
	}
cout<<"\n";

	return 0;

	// 10 18 0 1 1 4 4 6 6 5 5 2 2 0 0 5 0 3 3 5 3 1 3 6 1 7 7 9 7 8 1 8 8 9 9 1 1 6
}
