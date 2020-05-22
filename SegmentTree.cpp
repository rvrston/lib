#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SegmentTree{
  T m_id;
  T op(const T &a, const T &b) const{
    return min(a, b);
  }
  vector<T> m_SegT;

  SegmentTree(int N): m_id(numeric_limits<T>::max()), m_SegT(2*N, m_id){}
  SegmentTree(const vector<T> &data): m_id(numeric_limits<T>::max()), m_SegT(2*data.size()){
    int N= m_SegT.size() >> 1;
    for(int i=0; i<N; i++){
      m_SegT.at(i+N)= data.at(i);
    }
    for(int i=N-1; i>0; i--){
      m_SegT.at(i)= op(m_SegT.at(i << 1), m_SegT.at((i << 1) | 1));
    }
  }

  void set_val(int idx, T val){
    idx+= m_SegT.size() >> 1;
    m_SegT.at(idx)= val;
    while((idx >> 1) > 0){
      idx >>= 1;
      m_SegT.at(idx)= op(m_SegT.at(idx << 1), m_SegT.at((idx << 1) | 1));
    }
  }

  T range(int left, int right) const{// [left, right)
    left += m_SegT.size() >> 1;
    right+= m_SegT.size() >> 1;
    T calc_l= m_id;
    T calc_r= m_id;

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
