#include <bits/stdc++.h>
using namespace std;

constexpr int64_t MOD= 1000000007;
constexpr bool is_FACTORIAL_STORED= false; // 階乗を配列に格納をする前処理をする/しない
constexpr int Nfac= is_FACTORIAL_STORED ? 2000007
                                        : 0;
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
vector<mint> g_mfac(Nfac+1), g_ifac(Nfac+1);
void fact_modp_init(int N= Nfac){
  if constexpr(is_FACTORIAL_STORED){
    static bool initialized = false;
    if(!initialized){
      g_mfac.at(0)= 1;
      for(int i=1; i<=N; i++){
        g_mfac.at(i)= g_mfac.at(i-1)* (mint)i;
      }
  
      g_ifac.at(N)= g_mfac.at(N).inv();
      for(int i=N; i>0; i--){
        g_ifac.at(i-1)= g_ifac.at(i)* (mint)i;
      }

      initialized= true;
    }
  }
  else{
    return;
  }
}

inline mint mfac(int N){
  if constexpr(is_FACTORIAL_STORED){
    fact_modp_init();
    return g_mfac.at(N);
  }
  else{
    mint ans= 1;
    for(int i=1; i<=N; i++){
      ans*= (mint)i;
    }
    return ans;
  }
}

inline mint ifac(int N){
  if constexpr(is_FACTORIAL_STORED){
    fact_modp_init();
    return g_ifac.at(N);
  }
  else{
    return mfac(N).inv();
  }
}

mint binom_modp(int n, int k){
  if constexpr(is_FACTORIAL_STORED){
    if(n < 0 || min(k,n-k) < 0) return 0;
    else{
      fact_modp_init();
      return g_mfac.at(n)* g_ifac.at(k)* g_ifac.at(n-k);
    }
  }
  else{
    if(n < 0 || min(k,n-k) < 0) return 0;
    else{
      k= min(k, n-k);
      mint ans= 1;
      for(int i=1; i<=k; i++){
        ans*= (mint)(n-i+1);
      }
      ans/= mfac(k);

      return ans;
    }
  }
}

mint multiset_modp(int n, int r){
  if(n==0 && r==0) return 1;
  else{
    return binom_modp(n+r-1, r);
  }
}
// ^^^ テンプレここまで ^^^
