#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
using coord= pair<int, int>;

bool BFS(const vector<string> &board, coord s, coord g){ // 辺の重みが0/1のときは両端キューを使って重み0の辺を辿るときpush_front, 重み1の辺を辿るときpush_backすると簡単にBFSできる。
  const int dist= 2; // 探索する深さの最大値
  const int TBC= INT_MAX;
  const char block= '#';
  const int H= board.size();
  const int W= board.at(0).size();

  const vector<coord> diff= {make_pair(0,-1), make_pair(-1,0), make_pair(1,0), make_pair(0,1) // 上下4方向
                             // make_pair(-1,-1), make_pair(1,-1), make_pair(-1,1), make_pair(1,1) // 斜め4方向
                            }; // 探索方向

  vector<vector<int>> checked(H, vector<int>(W, TBC));
  deque<coord> bfs;
  checked.at(s.first).at(s.second)= 0;
  bfs.push_front(s);

  bool ans= false;
  while( !bfs.empty() ){
    coord p= bfs.front();
    int x,y;
    tie(x, y)= p;
    bfs.pop_front();
    if(p==g && checked.at(x).at(y) <= dist){
      ans= true;
      break;
    }
    else if(checked.at(x).at(y) > dist){
      break;
    }
    else{
      for(const auto& ds:diff){
        int dx,dy;
        tie(dx, dy)= ds;
        if(x+dx <= -1 || x+dx >= H || y+dy <= -1 || y+dy >= W) continue;
        else if(board.at(x+dx).at(y+dy)!=block && checked.at(x+dx).at(y+dy)==TBC){
          checked.at(x+dx).at(y+dy)= checked.at(x).at(y);
          bfs.push_front(make_pair(x+dx, y+dy));
        }
        else if(board.at(x+dx).at(y+dy)==block && checked.at(x+dx).at(y+dy)==TBC){
          checked.at(x+dx).at(y+dy)= checked.at(x).at(y)+ 1;
          bfs.push_back(make_pair(x+dx, y+dy));
        }
      }
    }
  }

  return ans;
}

int main() {
  int H,W;
  cin >> H >> W;

  coord s,g;
  vector<string> Board(H);
  for(int i=0; i<H; i++){
    cin >> Board.at(i);
    for(int j=0; j<W; j++){
      if(Board.at(i).at(j)=='s'){
        s= make_pair(i,j);
      }
      else if(Board.at(i).at(j)=='g'){
        g= make_pair(i,j);
      }
    }
  }

  if(BFS(Board, s, g)){
    cout << "YES" << endl;
  } 
  else{
    cout << "NO" << endl;
  }
}