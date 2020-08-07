#include <bits/stdc++.h>
using namespace std;
using edge= pair<int, int64_t>;
using Graph= vector<vector<edge>>;
const int64_t INF= 1e15;

void solve(const Graph &gph, int s, vector<int64_t> *dists){
  const size_t N= gph.size();

  dists->at(s)= 0;
  queue<int> s_inf;
  for(size_t d=1; d<=N; d++){
    for(size_t from=0; from<N; from++){
      for(auto e:gph.at(from)){
        int to; int64_t cost;
        tie(to, cost)= e;
        if(dists->at(to) > dists->at(from)+ cost){
          dists->at(to)= dists->at(from)+ cost;

          if(d==N){
            dists->at(to)= -INF;
            s_inf.push(to);
          }
        }
      }
    }
  }

  if(s_inf.size()){
    while( !s_inf.empty() ){
      int from= s_inf.front();
      s_inf.pop();
      for(auto e:gph.at(from)){
        int to;
        tie(to, ignore)= e;

        if(dists->at(to) > -INF){
          dists->at(to)= -INF;
          s_inf.push(to);
        }
      }
    }
  }
}

int main(){
  int N,M;
  cin >> N >> M;

  Graph gph(N);
  int v1,v2; int64_t cost;
  for(int j=0; j<M; j++){
    cin >> v1 >> v2 >> cost;
    v1--; v2--; // 1-indexed -> 0-indexed
    gph.at(v1).emplace_back(make_pair(v2, cost));
  }

  vector<int64_t> dists(N, INF);
  solve(gph, 0, &dists);

  string ans= (dists.back() > -INF) ? to_string(dists.back())
                                    : "-inf";

  cout << ans << endl;
}
