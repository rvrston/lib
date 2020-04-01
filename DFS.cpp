#include <bits/stdc++.h>
using namespace std;
using Graph= vector<vector<int>>;
using lint= long long int;

void DFS(Graph &gph, int id){
  if(gph.at(id).size()==0){
    return 1;
  }
  else{
    lint sal_max= -1;
    lint sal_min= LLONG_MAX;
    for(auto sub:gph.at(id)){
      sal_max= max(sal_max, DFS(gph, sub));
      sal_min= min(sal_min, DFS(gph, sub));
    }
    return sal_max+ sal_min+ 1;
  }
}

int main(){
  int N,boss;
  cin >> N;

  Graph staff(N);
  for(int i=1; i<N; i++){
    cin >> boss;
    boss--; // 1-indexed -> 0-indexed
    staff.at(boss).emplace_back(i);
  }

  cout << DFS(staff, 0) << endl;
}