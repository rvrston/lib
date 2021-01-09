#include <bits/stdc++.h>
using namespace std;

struct DPState{
  int64_t m_rep;
  int m_sub;

  DPState(int64_t rep=0LL, int v=0): m_rep(rep), m_sub(v) {}
  DPState& operator*=(const DPState& x){
    m_rep+= x.m_rep;
    m_sub+= x.m_sub;

    return *this;
  }
  DPState operator*(const DPState x) const {
    DPState ans(*this);
    ans*= x;
    return ans;
  }
  DPState Act(const DPState& x, int64_t diff){
    DPState ans(*this);
    ans.m_rep+= x.m_rep+ diff;
    ans.m_sub+= x.m_sub;

    return ans;
  }
  DPState& AddRoot(){
    m_sub++;
    return *this;
  }
  DPState& SubRoot(){
    m_sub--;
    return *this;
  }
};

using Edge= tuple<int, int64_t, int64_t>;
using Graph= vector<vector<Edge>>;
constexpr int nil= -1;

void DFS1(const Graph& tree, int parent, int root, vector<DPState>* bottomup){
  // ボトムアップに木DPする
  DPState ret= DPState();
  for(const auto& [ngh, from, to]:tree.at(root)){
    if(ngh==parent){ continue; }
    else{
      DFS1(tree, root, ngh, bottomup);
      ret= ret.Act(bottomup->at(ngh), from);
    }
  }
  ret.AddRoot();

  bottomup->at(root)= ret;
}

void DFS2(const Graph& tree, int parent, int root, const vector<DPState>* bottomup, vector<DPState>* topdown){
  // トップダウンに木DPする
  size_t Nroot= tree.at(root).size();
  vector<DPState> cumL(Nroot+ 1); // cumL[i]= cum[0,i)
  vector<DPState> cumR(Nroot+ 1); // cumR[i]= cum[i,Nroot)
  for(size_t i=0; i<Nroot; i++){
    auto [ngh, from, to]= tree.at(root).at(i);
    cumL.at(i+1)= (ngh != parent) ? cumL.at(i).Act(bottomup->at(ngh), from)
                                  : cumL.at(i);
  }
  for(size_t i=0; i<Nroot; i++){
    auto [ngh, from, to]= tree.at(root).at(Nroot-i -1);
    cumR.at(Nroot-i -1)= (ngh != parent) ? cumR.at(Nroot-i).Act(bottomup->at(ngh), from)
                                         : cumR.at(Nroot-i);
  }

  for(size_t i=0; i<Nroot; i++){
    auto [ngh, from, to]= tree.at(root).at(i);
    if(ngh==parent){ continue; }
    else{
      DPState ret= topdown->at(root).Act(cumL.at(i)* cumR.at(i+1), to);
      ret.AddRoot();
      topdown->at(ngh)= ret;
      DFS2(tree, root, ngh, bottomup, topdown);
    }
  }
}

void ReRooting(const Graph& tree, vector<DPState>* bottomup, vector<DPState>* topdown){
  DFS1(tree, nil, 0, bottomup);
  DFS2(tree, nil, 0, bottomup, topdown);
}

int main(){
  int N;
  cin >> N;
  const int M= N-1;

  using EdgeIO= tuple<int, int, int64_t, int64_t>;
  vector<EdgeIO> edgesIO(M);
  int v1,v2;
  for(int j=0; j<M; j++){
    cin >> v1 >> v2;
    v1--; v2--; // 1-indexed -> 0-indexed
    edgesIO.at(j)= make_tuple(v1, v2, 0LL, 0LL);
  }

  int Q;
  cin >> Q;
  for(int q=0; q<Q; q++){
    int query, e; int64_t diff;
    cin >> query >> e >> diff;
    e--; // 1-indexed -> 0-indexed
    if(query==1){
      get<2>(edgesIO.at(e))+= diff;
    }
    else{
      get<3>(edgesIO.at(e))+= diff;
    }
  }

  Graph tree(N);
  for(int j=0; j<M; j++){
    auto [v1,v2, off1,off2]= edgesIO.at(j);
    tree.at(v1).emplace_back(make_tuple(v2, off1, off2));
    tree.at(v2).emplace_back(make_tuple(v1, off2, off1));
  }

  vector<DPState> bottomup(N);
  vector<DPState> topdown(N);
  ReRooting(tree, &bottomup, &topdown);

  for(int v=0; v<N; v++){
    DPState ans= bottomup.at(v).SubRoot()* topdown.at(v);
    cout << ans.m_rep << endl;
  }
}