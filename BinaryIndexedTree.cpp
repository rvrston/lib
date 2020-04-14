#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BinaryIndexedTree{
// アーベル群に対応するデータ構造
// 1要素更新:O(logN), 区間演算:O(logN)
  vector<T> m_BIT;
 
  BinaryIndexedTree(int N): m_BIT(N+1){}
 
  void add(int idx, T diff){
    for(int i=idx; i< m_BIT.size(); i+= i&-i){
      m_BIT.at(i)+= diff;
    }
  }
 
  T cumulative(int right) const{// [1, right)
    T ans= 0;
    for(int i=right-1; i>0; i-= i&-i){
      ans+= m_BIT.at(i);
    }
    return ans;
  }
 
  T range(int left, int right) const{// [left, right)
    return cumulative(right)- cumulative(left);
  }
 
  void set_val(int idx, T val){
    T a_i= range(idx, idx+ 1);
    add(idx, val- a_i);
  }
};

int main(){
  int N,Q;
  cin >> N >> Q;

  BinaryIndexedTree<int64_t> data(N);
  int64_t buf;
  for(int i=1; i<=N; i++){// 1-indexed
    cin >> buf;
    data.add(i, buf);
  }

  int query,buf1,buf2;
  for(int i=0; i<Q; i++){
    cin >> query >> buf1 >> buf2;
    if(query==0){
      buf1++; // 0-indexed -> 1-indexed
      data.add(buf1, buf2);
    }
    else{
      buf1++; buf2++; // 0-indexed -> 1-indexed
      cout << data.range(buf1, buf2) << endl;
    }
  }
}
