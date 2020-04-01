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
  SparseTable(const vector<T> &data): m_ST(data.size()){
    int N= data.size();
    int D= 0;
    while((1<<D) <= N){ D++; } D--;

    for(int i=0; i<N; i++){
      m_ST.at(i).push_back(data.at(i));
    }
    for(int d=1; d <= D; d++){
      for(int i=0; i+(1<<d) <= N; i++){
        m_ST.at(i).push_back(idempotent_op(m_ST.at(i).at(d-1), m_ST.at(i+(1<<(d-1))).at(d-1)));
      }
    }
  }

  T range(int left, int right) const{ // 半開区間[l, r)に対するクエリ
    int len= right- left;
    assert(len > 0);
    int K= 0;
    while((1<<K) <= len){ K++; } K--;
    // 計算のアイディア: [l,r)= [l,l+k)∪[r-k,r) なるkを一つ取ると、
    // ∧[l,r)= ∧[l,r-k) ∧ ∧[r-k,l+k) ∧ ∧[l+k,r)              (∵結合律)
    //       = ∧[l,r-k) ∧ ∧[r-k,l+k) ∧ ∧[r-k,l+k) ∧ ∧[l+k,r) (∵冪等性)
    //       = ∧[l,l+k)               ∧ ∧[r-k,r)               (∵結合律)
    return idempotent_op(m_ST.at(left).at(K), m_ST.at(right-(1<<K)).at(K));
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