#include <bits/stdc++.h>
using namespace std;

void Zalgo(const string& data, vector<int>* LCPlen){
  const int N= int(data.size());
  LCPlen->at(0)= N;

  int rightmost= 1; // data[:rightmost)まで探索済み
  int left_rm= 0;   // left_rm= max l s.t. LCPlen[l]= rightmost- l
  for(int i=1; i<N; i++){
    if(LCPlen->at(i- left_rm) < rightmost- i){
      LCPlen->at(i)= LCPlen->at(i- left_rm);
    }
    else{
      while(rightmost < N and data.at(rightmost)==data.at(rightmost- i)){
        rightmost++;
      }
      LCPlen->at(i)= rightmost- i;
      left_rm= i;
      if(rightmost==i){ rightmost++; }
    }
  }
}

int main(){
  string S;
  cin >> S;

  vector<int> answer(S.size());
  Zalgo(S, &answer);

  for(const auto& elem:answer){
    cout << elem <<" ";
  }
}