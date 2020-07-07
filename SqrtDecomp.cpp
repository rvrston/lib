#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SqrtDecomp{
  T m_id;
  T op(const T &a, const T &b) const{
    return a+ b;
  }
  size_t m_sqrtN;
  vector<T> m_data;
  vector<T> m_bucket;

  SqrtDecomp(int N)
  : m_id(0)
  , m_sqrtN((size_t)sqrt(N))
  , m_data(N, m_id)
  , m_bucket(N/m_sqrtN, m_id) /* サイズがm_sqrtN だと m_sqrtN==1のときバグる */
  {}
  SqrtDecomp(const vector<T> &data)
  : m_id(0)
  , m_sqrtN((size_t)sqrt(data.size()))
  , m_data(data)
  {
    for(size_t offset=0; offset+ m_sqrtN <= m_data.size(); offset+= m_sqrtN){
      T calc= m_id;
      for(size_t i=0; i< m_sqrtN; i++){
        calc= op(calc, m_data.at(offset+ i));
      }
      m_bucket.emplace_back(calc);
    }
  }

  void add(int idx, T diff){
    m_data.at(idx)= op(m_data.at(idx), diff);
    if(idx/m_sqrtN < m_bucket.size()){
      m_bucket.at(idx/m_sqrtN)= op(m_bucket.at(idx/m_sqrtN), diff);
    }
  }

  T range(int left, int right) const{// [left, right)
    T calc= m_id;
    while(left < right && left% m_sqrtN != 0){
      calc= op(calc, m_data.at(left));
      left++;
    }
    while(left/m_sqrtN < right/m_sqrtN){
      calc= op(calc, m_bucket.at(left/m_sqrtN));
      left+= m_sqrtN;
    }
    while(left < right){
      calc= op(calc, m_data.at(left));
      left++;
    }

    return calc;
  }
};

int main() {
  int N,Q;
  cin >> N >> Q;

  SqrtDecomp<int64_t> sd(N);
  int64_t buf;
  for(int i=0; i<N; i++){
    cin >> buf;
    sd.add(i, buf);
  }

  int bufq,buf1,buf2;
  for(int i=0; i<Q; i++){
    cin >> bufq >> buf1 >> buf2;
    if(bufq==0){ sd.add(buf1, buf2); }
    else if(bufq==1){ cout << sd.range(buf1, buf2) << endl; }
  }
}