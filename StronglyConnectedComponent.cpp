#include <bits/stdc++.h>
using namespace std;

using Edge= int;
using Graph= vector<vector<Edge>>;
using Vertex= int;
using SCC= vector<vector<Vertex>>;

constexpr bool is_ONE_INDEXED= false;

void init(int N, int M, Graph* gph, Graph* gph_inv){
  gph->resize(N);
  gph_inv->resize(N);

  for(int j=0; j<M; j++){
    int from, to;
    cin >> from >> to;
    if constexpr(is_ONE_INDEXED){
      from--; to--; // 1-indexed -> 0-indexed
    }
    gph    ->at(from).emplace_back(to);
    gph_inv->at(to).emplace_back(from);
  }
}

void DFS(const Graph& gph, int v, vector<int>* post_timestamp, vector<bool>* visited){
  if(visited->at(v)){ return; }
  else{
    visited->at(v)= true;
    for(const auto& ngh:gph.at(v)){
      DFS(gph, ngh, post_timestamp, visited);
    }
    post_timestamp->emplace_back(v);
  }
}

void DFSinv(const Graph& gph_inv, int v, vector<bool>* visited_inv, SCC* scc){
  if(visited_inv->at(v)){ return; }
  else{
    visited_inv->at(v)= true;
    for(const auto& ngh:gph_inv.at(v)){
      DFSinv(gph_inv, ngh, visited_inv, scc);
    }
    scc->back().emplace_back(v);
  }
}

void solveSCC(const Graph& gph_inv, const vector<int>& post_timestamp, SCC* scc){
  vector<int> post_timestamp_inv;
  reverse_copy(post_timestamp.begin(), post_timestamp.end(), back_inserter(post_timestamp_inv));

  vector<bool> visited_inv(post_timestamp.size(), false);
  for(const auto& v:post_timestamp_inv){
    if(visited_inv.at(v)){ continue; }
    else{
      scc->emplace_back(vector<Vertex>());
      DFSinv(gph_inv, v, &visited_inv, scc);
    }
  }
}

int main(){
  int N,M;
  cin >> N >> M;

  Graph gph;
  Graph gph_inv;
  init(N, M, &gph, &gph_inv);
  
  vector<int> post_timestamp;
  vector<bool> visited(N, false);
  for(int v=0; v<N; v++){
    DFS(gph, v, &post_timestamp, &visited);
  }

  SCC scc;
  solveSCC(gph_inv, post_timestamp, &scc);

  cout << scc.size() << "\n";
  for(const auto& comp:scc){
    cout << comp.size() <<" ";
    for(const auto& v:comp){
      cout << v <<" ";
    }
    cout << "\n";
  }
}