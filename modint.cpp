#include <bits/stdc++.h>
using namespace std;

const int64_t MOD= 1000000007;
const int Nfac= 2000007;
#define MEMORY 0 // 1/0: 階乗を配列に格納をする前処理をする/しない
/* 剰余環 Z/nZ */
struct mint{ // Z/nZ に関する演算(n:素数の場合は除算も)をサポートする構造体
  int64_t rep; // 出力すべき代表元 rep \in {0,1,..,MOD- 1}
  mint(int64_t x=0): rep(((x%MOD)+ MOD)% MOD){}
  mint operator-() const { return mint(-rep);}
  mint& operator+=(const mint& x){
    rep+= x.rep; 
    if(rep>= MOD) rep-= MOD;
    return *this;
  }
  mint& operator-=(const mint& x){
    rep-= x.rep;
    if(rep< 0) rep+= MOD;
    return *this;
  }
  mint& operator*=(const mint& x){
    rep*= x.rep; rep%= MOD;
    return *this;
  }
  mint operator+(const mint x) const {
    mint ans(*this);
    ans+= x;
    return ans;
  }
  mint operator-(const mint x) const {
    mint ans(*this);
    ans-= x;
    return ans;
  }
  mint operator*(const mint x) const {
    mint ans(*this);
    ans*= x;
    return ans;
  }
  bool operator==(const mint x) const {
    return rep==x.rep;
  }
  bool operator!=(const mint x) const {
    return rep!=x.rep;
  }

  mint pow(int64_t d) const{ // d \geq 0
    mint ans= 1;
    mint x= *this;
    while(d > 0){
      if(d&1){ ans*= x; }
      d >>= 1;
      x*= x;
    }

    return ans;
  }

  friend istream& operator >> (istream &is, mint& x) noexcept{
    int64_t a;
    is >> a;
    x= a;
    return is;
  }
  friend ostream& operator << (ostream &os, const mint& x) noexcept{
      return os << x.rep;
  }
  // MOD が素数(<=> Z/nZ が体)のとき
  mint inv() const{
    return pow(MOD-2);
  }
  mint& operator/=(const mint& x){
    *this *= x.inv();
    return *this;
  }
  mint operator/(const mint x) const {
    mint ans(*this);
    ans/= x;
    return ans;
  }
};

/* 階乗,二項係数 */
#if (MEMORY==1)
// 前処理として,階乗を配列に格納をするver.
vector<mint> g_mfac(Nfac+1), g_ifac(Nfac+1);
void fact_modp_init(int N= Nfac){
  static bool initialized = false;
  if(!initialized){
    g_mfac.at(0)= 1;
    mint buf;
    for(int i=1; i<=N; i++){
      buf= i;
      g_mfac.at(i)= g_mfac.at(i-1)* buf;
    }

    g_ifac.at(N)= g_mfac.at(N).inv();
    for(int i=N; i>0; i--){
      buf= i;
      g_ifac.at(i-1)= g_ifac.at(i)* buf;
    }

    initialized= true;
  }
}
inline mint mfac(int N){
  fact_modp_init();
  return g_mfac.at(N);
}
inline mint ifac(int N){
  fact_modp_init();
  return g_ifac.at(N);
}
#else
// 前処理を回避するver.
mint mfac(int N){
  mint ans= 1;
  mint buf;
  for(int i=1; i<=N; i++){
    buf= i;
    ans*= buf;
  }

  return ans;
}
#endif

mint binom_modp(int n, int k){
  if(n < 0 || min(k,n-k) < 0) return 0;
  else{
#if (MEMORY==1)
    fact_modp_init();
    return g_mfac.at(n)* g_ifac.at(k)* g_ifac.at(n-k);
#else
    k= min(k, n-k);
    mint ans= 1;
    for(int i=1; i<=k; i++){
      mint num= n-i+1;
      ans*= num;
    }
    ans/= mfac(k);

    return ans;
#endif
  }
}

mint multiset_modp(int n, int r){
  if(n==0 && r==0) return 1;
  else{
    return binom_modp(n+r-1, r);
  }
}
// ^^^ テンプレここまで ^^^
