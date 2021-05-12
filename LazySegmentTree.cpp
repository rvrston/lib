#include <bits/stdc++.h>
using namespace std;

constexpr bool has_AUXILIARY_DATA= false;

int floor_log2(int N){
  assert(N > 0);
  #ifdef __GNUC__
    int logN= 31- __builtin_clz(N);
    return logN;
  #else
    int logN= 0;
    if(N >= (1<<16)){ logN+= 16; N >>= 16; }
    if(N >= (1<< 8)){ logN+=  8; N >>=  8; }
    if(N >= (1<< 4)){ logN+=  4; N >>=  4; }
    if(N >= (1<< 2)){ logN+=  2; N >>=  2; }
    if(N >= (1<< 1)){ logN+=  1; N >>=  1; }
    return logN;
  #endif
}

template <typename T, typename F>
struct LazySegmentTree{
private: // このブロックでモノイドを指定
  struct Seg{
    T   mS_rep;
    int mS_len;
    Seg(): mS_rep(0), mS_len(0){}
    Seg(const T& val, int len=1): mS_rep(val), mS_len(len){}
  };

  struct Action{
    optional<F> mF_param;
    Action(): mF_param(){}
    Action(const F& param): mF_param(param){}
    bool is_id() const{ return !mF_param.has_value(); }
  };

  const Seg e_S= Seg();
  const Action id= Action();
  Seg op(const Seg& lhs, const Seg& rhs) const{
    return Seg(max(lhs.mS_rep, rhs.mS_rep), lhs.mS_len+ rhs.mS_len);
  }
  Seg mapping(const Action& f, const Seg& s) const{
    if(f.is_id()){ return s; }
    else{
      return Seg(f.mF_param.value(), s.mS_len);
    }
  }
  Action composition(const Action& f2, const Action& f1) const{
    if(f2.is_id()){ return f1; }
    else          { return f2; }
  }
  vector<T> m_aux;
  void init(int N){
    if constexpr(not has_AUXILIARY_DATA){ return; }
    else{
      m_aux.emplace_back(T(1));
      int logN= floor_log2(N);
      for(int i= 1; i<= logN; i++){
        T ret= m_aux.back()* T(10).pow(1<<(i-1)) + m_aux.back();
        m_aux.emplace_back(ret);
      }
    }
  }

private: 
  vector<Seg> m_SegT;
  vector<Action> m_lazy;

public:
  LazySegmentTree(int N): m_SegT(2*N, e_S), m_lazy(2*N, id){ init(N); }
  LazySegmentTree(const vector<T> &data): m_SegT(2*data.size()), m_lazy(2*data.size(), id){
    init(data.size());
    size_t N= m_SegT.size() >> 1;
    for(size_t i=0; i<N; i++){
      m_SegT.at(i+N)= Seg(data.at(i));
    }
    for(size_t i=N-1; i>0; i--){
      m_SegT.at(i)= op(m_SegT.at(i << 1), m_SegT.at((i << 1) | 1));
    }
  }

public: /* メンバ関数の引数は 0-indexed */
  void set_val(size_t idx, const T& val){
    idx+= m_SegT.size() >> 1;

    propagate(idx);

    m_SegT.at(idx)= Seg(val);
    m_lazy.at(idx)= id;

    recalc(idx);
  }

  void apply(size_t left, size_t right, const F& param){// [left, right)
    const Action f= Action(param);
    left += m_SegT.size() >> 1;
    right+= m_SegT.size() >> 1;
    size_t Lupdate= left/ (left & -left);
    size_t Rupdate= right/ (right & -right);

    propagate(Lupdate);
    propagate(Rupdate);

    while(left < right){
      if(left&1){
        m_lazy.at(left)= composition(f, m_lazy.at(left));
        left++;
      }
      if(right&1){
        m_lazy.at(right-1)= composition(f, m_lazy.at(right-1));
      }

      left >>= 1;
      right>>= 1;
    }

    recalc(Lupdate);
    recalc(Rupdate);
  }

  T fold(size_t left, size_t right){// [left, right)
    left += m_SegT.size() >> 1;
    right+= m_SegT.size() >> 1;
    size_t Lupdate= left/ (left & -left);
    size_t Rupdate= right/ (right & -right);

    propagate(Lupdate);
    propagate(Rupdate);

    Seg calc_l= e_S;
    Seg calc_r= e_S;
    while(left < right){
      if(left&1){
        calc_l= op(calc_l, mapping(m_lazy.at(left), m_SegT.at(left)));
        left++;
      }
      if(right&1){
        calc_r= op(mapping(m_lazy.at(right-1), m_SegT.at(right-1)), calc_r);
      }

      left >>= 1;
      right>>= 1;
    }

    return op(calc_l, calc_r).mS_rep;
  }

private:
  void propagate(size_t idx){// idxより上のセル達からトップダウンに伝播させる
    int H= floor_log2(idx);
    for(int h= H; h>0; h--){
      int v= idx >> h;
      if(m_lazy.at(v).is_id()){ continue; }
      else{
        m_lazy.at(v << 1)      = composition(m_lazy.at(v), m_lazy.at(v << 1));
        m_lazy.at((v << 1) | 1)= composition(m_lazy.at(v), m_lazy.at((v << 1) | 1));

        m_SegT.at(v)= mapping(m_lazy.at(v), m_SegT.at(v));
        m_lazy.at(v)= id;
      }
    }
  }

  void recalc(size_t idx){// idxの更新を上のセル達にボトムアップで反映させる
    while((idx >> 1) > 0){
      idx >>= 1;
      m_SegT.at(idx)= op(mapping(m_lazy.at(idx << 1)     , m_SegT.at(idx << 1)), 
                         mapping(m_lazy.at((idx << 1)| 1), m_SegT.at((idx << 1)| 1)));
    }
  }
};

int main() {
  int W,N;
  cin >> W >> N;

  LazySegmentTree<int, int> segtree(vector<int>(W+1, 0));
  for(int i=0; i<N; i++){
    int left,right;
    cin >> left >> right;
    right++; // [left,right] -> [left,right)

    int h_new= 1+ segtree.fold(left, right);
    segtree.apply(left, right, h_new);
    
    cout << h_new <<"\n";
  }
}
