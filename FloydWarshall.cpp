#include <bits/stdc++.h>
using namespace std;
using Graph= vector<vector<int>>;
const int INF= 1e9;

void solve(const Graph &weights, Graph *dp){
  const size_t N= weights.size();

  for(size_t k=0; k<N; k++){
    for(size_t from=0; from<N; from++){
      for(size_t to=0; to<N; to++){
        dp->at(from).at(to)= min(dp->at(from).at(to), dp->at(from).at(k)+ dp->at(k).at(to));
      }
    }
  }
}

int main(){
  int N,M,R;
  cin >> N >> M >> R;

  vector<int> checkpoints(R);
  for(int i=0; i<R; i++){
    cin >> checkpoints.at(i);
    checkpoints.at(i)--; // 1-indexed -> 0-indexed
  }
  vector<int> route(R);
  iota(route.begin(), route.end(), 0);

  Graph gph(N, vector<int>(N, INF));
  for(int v=0; v<N; v++){
    gph.at(v).at(v)= 0;
  }
  int v1,v2,dist;
  for(int j=0; j<M; j++){
    cin >> v1 >> v2 >> dist;
    v1--; v2--; // 1-indexed -> 0-indexed
    gph.at(v1).at(v2)= dist;
    gph.at(v2).at(v1)= dist;
  }

  Graph dp= gph;
  solve(gph, &dp);

  int ans= INF;
  do{
    int cand= 0;
    for(int i=1; i<R; i++){
      int from= checkpoints.at(route.at(i-1));
      int to  = checkpoints.at(route.at(i));
      cand+= dp.at(from).at(to);
    }
    ans= min(ans, cand);
  } while(next_permutation(route.begin(), route.end()));

  cout << ans << endl;
}
