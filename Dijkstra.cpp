#include <bits/stdc++.h>
using namespace std;
using edge= pair<int64_t, int>;
using Graph= vector<vector<edge>>;

void solve(const Graph &gph, int s, vector<int64_t> *dists){
  using path= edge;

  priority_queue<path, vector<path>, greater<path>> search;
  search.push(make_pair(0, s));
  while( !search.empty() ){
    int64_t d_tmp; int from_tmp;
    tie(d_tmp, from_tmp)= search.top();
    search.pop();

    if(dists->at(from_tmp) <= d_tmp){ continue; }
    else{
      dists->at(from_tmp)= d_tmp;
      for(auto e:gph.at(from_tmp)){
        int64_t d_to; int to_tmp;
        tie(d_to, to_tmp)= e;
        search.push(make_pair(d_tmp+ d_to, to_tmp));
      }
    }
  }
}

int main(){
  int N;
  cin >> N;
  const int M= N-1;

  Graph gph(N);
  int v1,v2; int64_t w;
  for(int i=0; i<M; i++){
    cin >> v1 >> v2 >> w;
    v1--; v2--; // 1-indexed -> 0-indexed

    gph.at(v1).emplace_back(make_pair(w, v2));
    gph.at(v2).emplace_back(make_pair(w, v1));
  }

  int Q,K;
  cin >> Q >> K;
  K--; // 1-indexed -> 0-indexed

  vector<int64_t> dists(N, INT64_MAX);
  solve(gph, K, &dists);

  for(int i=0; i<Q; i++){
    cin >> v1 >> v2;
    v1--; v2--; // 1-indexed -> 0-indexed

    cout << dists.at(v1)+ dists.at(v2) << endl;
  }
}