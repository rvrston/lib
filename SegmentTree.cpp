#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SegmentTree{
  const T e_T= numeric_limits<T>::max();
  T op(const T &a, const T &b) const{
    return min(a, b);
  }
  vector<T> m_SegT;

  SegmentTree(int N): m_SegT(2*N, e_T){}
  SegmentTree(const vector<T> &data): m_SegT(2*data.size()){
    size_t N= m_SegT.size() >> 1;
    for(size_t i=0; i<N; i++){
      m_SegT.at(i+N)= data.at(i);
    }
    for(size_t i=N-1; i>0; i--){
      m_SegT.at(i)= op(m_SegT.at(i << 1), m_SegT.at((i << 1) | 1));
    }
  }

  /* メンバ関数の引数は 0-indexed */
  void set_val(size_t idx, T val){
    idx+= m_SegT.size() >> 1;
    m_SegT.at(idx)= val;
    while((idx >> 1) > 0){
      idx >>= 1;
      m_SegT.at(idx)= op(m_SegT.at(idx << 1), m_SegT.at((idx << 1) | 1));
    }
  }

  T range(size_t left, size_t right) const{// [left, right)
    left += m_SegT.size() >> 1;
    right+= m_SegT.size() >> 1;
    T calc_l= e_T;
    T calc_r= e_T;

    while(left < right){
      if(left&1){
        calc_l= op(calc_l, m_SegT.at(left));
        left++;
      }
      if(right&1){
        calc_r= op(m_SegT.at(right-1), calc_r);
      }

      left >>= 1;
      right>>= 1;
    }

    return op(calc_l, calc_r);
  }
};

int main() {
  int N,Q;
  cin >> N >> Q;

  SegmentTree<int> st(N);
  int buf;
  for(int i=0; i<N; i++){
    cin >> buf;
    st.set_val(i, buf);
  }

  int left,right;
  for(int i=0; i<Q; i++){
    cin >> left >> right;
    cout << st.range(left, right) << endl;
  }
}
