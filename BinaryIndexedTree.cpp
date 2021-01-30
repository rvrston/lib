#include <bits/stdc++.h>
using namespace std;

constexpr bool ONE_INDEXED= false; // falseなら 0-indexed
template <typename T>
struct BinaryIndexedTree{
// アーベル群に対応するデータ構造
// 1要素更新:O(logN), 区間演算:O(logN)
  vector<T> m_BIT;
  size_t m_sz_pow2;
 
  BinaryIndexedTree(int N)
  : m_BIT(N+1)
#ifdef __GNUC__
  , m_sz_pow2(1 << (31- __builtin_clz(N)))
#endif
  {
#ifndef __GNUC__
    m_sz_pow2= N;
    m_sz_pow2|= (m_sz_pow2 >>  1);
    m_sz_pow2|= (m_sz_pow2 >>  2);
    m_sz_pow2|= (m_sz_pow2 >>  4);
    m_sz_pow2|= (m_sz_pow2 >>  8);
    m_sz_pow2|= (m_sz_pow2 >> 16);
    m_sz_pow2++;
    m_sz_pow2 >>= 1;
#endif
  }
 
  void add(int idx, T diff){ /* 1-indexed */
    if constexpr(not ONE_INDEXED){ idx++; }
    for(size_t i=idx; i< m_BIT.size(); i+= i&-i){
      m_BIT.at(i)+= diff;
    }
  }
 
  T cumulative(int right) const{// [1, right)
    if constexpr(not ONE_INDEXED){ right++; }
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

  size_t lower_bound(T val) const{// a[i]>= 0 のとき
    size_t offset= 0;
    for(size_t s= m_sz_pow2; s>0; s>>=1){
      if(offset+ s < m_BIT.size() && m_BIT.at(offset+ s) < val){
        offset+= s;
        val-= m_BIT.at(offset);
      }
    }
    if constexpr(ONE_INDEXED){ return offset+ 1; }
    else                     { return offset; }
  }
};

int main(){
  int N,Q;
  cin >> N >> Q;

  BinaryIndexedTree<int64_t> data(N);
  int64_t buf;
  for(int i=0; i<N; i++){
    cin >> buf;
    data.add(i, buf);
  }

  int64_t query,buf1,buf2;
  for(int i=0; i<Q; i++){
    cin >> query >> buf1 >> buf2;
    if(query==0){
      data.add(buf1, buf2);
    }
    else{
      cout << data.range(buf1, buf2) << endl;
    }
  }
}
