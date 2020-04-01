#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
using coord= pair<int, int>;

int BFS(const vector<string> &board, coord s, coord g){
  const int TBC= INT_MAX;
  const char block= '#';
  const int H= board.size();
  const int W= board.at(0).size();

  const vector<coord> diff= {make_pair(0,-1), make_pair(-1,0), make_pair(1,0), make_pair(0,1) // 上下4方向
                             // make_pair(-1,-1), make_pair(1,-1), make_pair(-1,1), make_pair(1,1) // 斜め4方向
                            }; // 探索方向

  vector<vector<int>> checked(H, vector<int>(W, TBC));
  queue<coord> bfs;
  checked.at(s.first).at(s.second)= 0;
  bfs.push(s);

  while( !bfs.empty() ){
    coord p= bfs.front();
    int x,y;
    tie(x, y)= p;
    bfs.pop();
    if(p==g){
      break;
    }
    else{
      for(const auto& ds:diff){
        int dx,dy;
        tie(dx, dy)= ds;
        if(x+dx <= -1 || x+dx >= H || y+dy <= -1 || y+dy >= W) continue;
        else if(board.at(x+dx).at(y+dy)==block){
          continue;
        }
        else if(board.at(x+dx).at(y+dy)!=block && checked.at(x+dx).at(y+dy)==TBC){
          checked.at(x+dx).at(y+dy)= checked.at(x).at(y)+ 1;
          bfs.push(make_pair(x+dx, y+dy));
        }
      }
    }
  }

  return checked.at(g.first).at(g.second);
}

int main() {
  int H,W;
  cin >> H >> W;

  coord s,g;
  cin >> s.first >> s.second;
  cin >> g.first >> g.second;
  s.first--; s.second--; g.first--; g.second--; // 1-indexed -> 0-indexed

  vector<string> Board(H);
  for(int i=0; i<H; i++){
    cin >> Board.at(i);
/*
    for(int j=0; j<W; j++){
      if(Board.at(i).at(j)=='s'){
        s= make_pair(i,j);
      }
      else if(Board.at(i).at(j)=='g'){
        g= make_pair(i,j);
      }
    }
*/
  }

  cout << BFS(Board, s, g) << endl;
}