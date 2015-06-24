#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
#include <map>
#include <set>

using namespace std;

const int MAX_N = 60 + 4;
const int MAX_M = 11;
const int GUARD = -1; //! 番兵
const int PLAIN = 10; // 平地

const int PEG0 = (1 << 0);
const int PEG1 = (1 << 1);
const int PEG2 = (1 << 2);
const int PEG3 = (1 << 3);
const int PEG4 = (1 << 4);
const int PEG5 = (1 << 5);
const int PEG6 = (1 << 6);
const int PEG7 = (1 << 7);
const int PEG8 = (1 << 8);
const int PEG9 = (1 << 9);

map<int, int> g_pegHash;

const int DY[4] = {-1, 0, 1, 0};
const int DX[4] = {0, 1, 0, -1};

const int UP    = (1 << 10);
const int RIGHT = (1 << 11);
const int DOWN  = (1 << 12);
const int LEFT  = (1 << 13);

map<int, int> g_directHash;

const int PEG_MASK = 511;
const int DIRECT_MASK = 7680;

unsigned long long xor128(){
  static unsigned long long rx=123456789, ry=362436069, rz=521288629, rw=88675123;
  unsigned long long rt = (rx ^ (rx<<11));
  rx=ry; ry=rz; rz=rw;
  return (rw=(rw^(rw>>19))^(rt^(rt>>8)));
}

inline int char2int(char ch){
  return ch - '0';
}

int g_field[MAX_N][MAX_N];
int g_pegValue[MAX_M];

struct Node {
  Node(int ypos, int xpos, int rt){
    y = ypos;
    x = xpos;
    reserve_turn = rt;
  }
  int y;
  int x;
  int reserve_turn;

  bool operator >(const Node &e) const{
    return reserve_turn > e.reserve_turn;
  }    
};

class PegJumping{
  public:
    int getPegNumber(int y, int x){
      assert(g_field[y][x] != PLAIN);

      return g_pegHash[(g_field[y][x] & PEG_MASK)];
    }

    /**
     * 現在いる座標からある座標に飛べるかどうかをチェックする
     */
    bool canJumping(int y, int x, int direct){
      assert(g_field[y][x] == PLAIN);

      int ny = y + DY[direct];
      int nx = x + DX[direct];

      if(g_field[ny][nx] == PLAIN || g_field[ny][nx] == GUARD) return false;
      return g_directHash[(g_field[ny][nx] & DIRECT_MASK)] > 0;
    }

    void init(vector<int> pegValue, vector<string> board){
      memset(g_field, GUARD, sizeof(g_field));

      int peg_num = pegValue.size();
      for(int i = 0; i < peg_num; i++){
        g_pegValue[i] = pegValue[i];
      }

      int height = board.size();
      int width = board[0].size();

      for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
          char ch = board[y][x];

          if(ch == '.'){
            g_field[y][x] = PLAIN;
          }else{
            g_field[y][x] = char2int(ch);
          }
        }
      }

      g_pegHash[PEG0] = 0;
      g_pegHash[PEG1] = 1;
      g_pegHash[PEG2] = 2;
      g_pegHash[PEG3] = 3;
      g_pegHash[PEG4] = 4;
      g_pegHash[PEG5] = 5;
      g_pegHash[PEG6] = 6;
      g_pegHash[PEG7] = 7;
      g_pegHash[PEG8] = 8;
      g_pegHash[PEG9] = 9;

      g_directHash[UP]    = 0;
      g_directHash[RIGHT] = 1;
      g_directHash[DOWN]  = 2;
      g_directHash[LEFT]  = 3;
    }

    vector<string> getMoves(vector<int> pegValue, vector<string> board){
      vector<string> ret;

      init(pegValue, board);

      return ret;
    }
};

int main(){
  int m = 0, n = 0;
  vector<string> ret;
  cin >> m;
  vector<int> pegValue(m);
  for(int i = 0; i < m; i++){
    cin >> pegValue[i];
  }
  cin >> n;
  vector<string> board(n);
  for(int i = 0; i < n; i++){
    cin >> board[i];
  }
  PegJumping pg;
  ret = pg.getMoves(pegValue, board);
  cout << ret.size() << endl;
  for(int i = 0; i < ret.size(); i++){
    cout << ret[i] << endl;
  }
  return 0;
}

