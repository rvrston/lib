#include <bits/stdc++.h>
using namespace std;
#define UF_SIZE 1 // 1/0: 同値類のサイズを記録する/しない

struct UnionFind{
// 同値関係をサポートするデータ構造
// 併合,所属する同値類の代表元:O(logN), 集合の分割はNG
// 経路圧縮する場合,各クエリはO(a(n)) (a(n): アッカーマン関数A(m,n)について,f(n)=A(n,n)としたときの逆関数)
  vector<int> m_root;
#if (UF_SIZE==1)
  vector<int> m_size;
#endif

  UnionFind(int N)
  : m_root(N)
#if (UF_SIZE==1)
  , m_size(N,1)
#endif
  { iota(m_root.begin(), m_root.end(), 0); }

  int find(int a){
    if(m_root.at(a)==a){
      return a;
    }
    else{
      return m_root.at(a)= find(m_root.at(a));
    }
  }

  void unify(int a, int b){
    int r_a= find(a);
    int r_b= find(b);
#if (UF_SIZE==1)
    if(r_a != r_b){
      if(m_size.at(r_a) < m_size.at(r_b)){
        m_root.at(r_a)= r_b;
        m_size.at(r_b)+= m_size.at(r_a);
        return;
      }
      else{
        m_root.at(r_b)= r_a;
        m_size.at(r_a)+= m_size.at(r_b);
        return;
      }
    }
#else
    if(r_a != r_b){
      m_root.at(r_b)= r_a;
      return;
    }
#endif
  }
  
  bool are_comrade(int a, int b){
    return find(a)==find(b);
  }

#if (UF_SIZE==1)
  int get_size(int a){
    return m_size.at(find(a));
  }
#endif
};

int main(){
  int N,Q;
  cin >> N >> Q;

  UnionFind uf(N);
  int bufq,buf1,buf2;
  for(int i=0; i<Q; i++){
    cin >> bufq >> buf1 >> buf2;
    if(bufq==0){
      uf.unify(buf1, buf2);
    }
    else{
      if(uf.are_comrade(buf1,buf2)){
        cout << 1 << endl;
      }
      else{
        cout << 0 << endl;
      }
    }
  }
}