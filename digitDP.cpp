// 下の桁から埋めるdp
// 参考URL "https://maspypy.com/atcoder-%e5%8f%82%e5%8a%a0%e6%84%9f%e6%83%b3-2019-02-09abc-154"
#include <bits/stdc++.h>
using namespace std;
using state= pair<string, int>;

int64_t dp(state idx, map<state, int64_t> &memo){ 
  if(memo.count(idx)) return memo.at(idx);

  string N= idx.first;
  int k= idx.second;
  if(N.size() < k) return 0;
  if(k==0) return 1;
  if(N.size()==1 && k==1) return N.at(0)-'0';
  else{
    string Ndiv10= N.substr(0, N.size()-1);
    string Ndiv10minus1= Ndiv10;
    int i= Ndiv10minus1.size()-1;
    while(Ndiv10minus1.at(i)=='0'){ /* Nが2桁以上なので非零の桁が存在することは確定 */
      Ndiv10minus1.at(i)= '9';
      i--;
    }
    Ndiv10minus1.at(i)-= 1;
    if(Ndiv10minus1.at(0)=='0') Ndiv10minus1= Ndiv10minus1.substr(1); /* N=10^nのときのケア */

    int64_t ans= 0;
    ans+= dp(make_pair(Ndiv10, k), memo); // '0'
    ans+= (N.at(N.size()-1)- '0')* dp(make_pair(Ndiv10      , k-1), memo); // '1'~'末尾の数字'
    ans+= ('9'- N.at(N.size()-1))* dp(make_pair(Ndiv10minus1, k-1), memo); // '末尾の数字+1'~'9'
    return memo[idx]= ans;
  }
}