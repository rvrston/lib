#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SparseTable{
// 冪等で結合的な演算(非可換でもOK) (ex: min, max, lcm, gcd, and, or)
// 前処理:O(NlogN), 区間クエリ:O(1), 要素の更新はNG
  vector<vector<T>> m_ST;
  T idempotent_op(const T &a, const T &b) const{ // 冪等で結合的な演算(非可換でもOK) (ex: min, max, lcm, gcd, and, or)
    return min(a, b);
  }
  SparseTable(const vector<T> &data): m_ST(1, data){
    int N= data.size();
    for(int d=1; (1<<d) <= N; d++){
      m_ST.emplace_back(vector<T>(N-(1<<d)+1));
      for(size_t i=0; i<m_ST.back().size(); i++){
        m_ST.back().at(i)= idempotent_op(m_ST.at(d-1).at(i), m_ST.at(d-1).at(i+(1<<(d-1))));
      }
    }
  }

  T range(int left, int right) const{ // 半開区間[l, r)に対するクエリ
#ifdef __GNUC__
    int logLen= 31- __builtin_clz(right- left);
#else
    int len= right- left;
    assert(len > 0);
    int logLen= 0;
    if(len >= (1<<16)){ logLen+= 16; len >>= 16; }
    if(len >= (1<< 8)){ logLen+=  8; len >>=  8; }
    if(len >= (1<< 4)){ logLen+=  4; len >>=  4; }
    if(len >= (1<< 2)){ logLen+=  2; len >>=  2; }
    if(len >= (1<< 1)){ logLen+=  1; len >>=  1; }
#endif
    // 計算のアイディア: [l,r)= [l,l+k)∪[r-k,r) なるkを一つ取ると、
    // ∧[l,r)= ∧[l,r-k) ∧ ∧[r-k,l+k) ∧ ∧[l+k,r)              (∵結合律)
    //       = ∧[l,r-k) ∧ ∧[r-k,l+k) ∧ ∧[r-k,l+k) ∧ ∧[l+k,r) (∵冪等性)
    //       = ∧[l,l+k)               ∧ ∧[r-k,r)               (∵結合律)
    return idempotent_op(m_ST.at(logLen).at(left), m_ST.at(logLen).at(right-(1<<logLen)));
  }
};

int main() {
  int N,Q;
  cin >> N >> Q;
  vector<int> data(N);
  for(int i=0; i<N; i++){
    cin >> data.at(i);
  }

  SparseTable<int> st(data);
  int left,right;
  for(int i=0; i<Q; i++){
    cin >> left >> right;
    cout << st.range(left, right) << endl;
  }
}
