#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,K;
  cin >> N >> K;
  vector<string> parts(N);
  for(int i=0; i<N; i++){
    cin >> parts.at(i);
  }
  sort(parts.begin(), parts.end());

  unordered_set<string> S;
  for(int tmp=0; tmp<(1<<N); tmp++){ /* 先にK個選んで、選んだものだけをpermutateする */
    bitset<10> bits(tmp);
    if(bits.count()==K){
      vector<string> chosen;
      for(int i=0; i<N; i++){
        if(bits.test(i)) chosen.push_back(parts.at(i));
      }

      do {
        string str= "";
        for(int j=0; j<K; j++){
          str+= chosen.at(j);
        }
        S.insert(str);
      } while(next_permutation(chosen.begin(), chosen.end()));
    }
  }

  cout << S.size() << endl;
}
