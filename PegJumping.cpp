#include <iostream>
#include <vector>
#include <sstream>
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

const int DY[4]     = {-1, 0, 1, 0};
const int DX[4]     = {0, 1, 0, -1};
const string DS[4]  = {"U","R","D","L"};

const int UP    = (1 << 10);
const int RIGHT = (1 << 11);
const int DOWN  = (1 << 12);
const int LEFT  = (1 << 13);

map<int, int> g_directHash;

const int PEG_MASK = 511;
const int DIRECT_MASK = 7680;

int g_height;
int g_width;

unsigned long long xor128(){
  static unsigned long long rx=123456789, ry=362436069, rz=521288629, rw=88675123;
  unsigned long long rt = (rx ^ (rx<<11));
  rx=ry; ry=rz; rz=rw;
  return (rw=(rw^(rw>>19))^(rt^(rt>>8)));
}

inline int char2int(char ch){
  return ch - '0';
}

string int2string(int number){
  stringstream ss; 
  ss << number;
  return ss.str();
}

int g_field[MAX_N][MAX_N];
int g_pegValue[MAX_M];

struct Node {
  int score;
  int board[MAX_M][MAX_M];

  Node(){
    score = 0;
  }

  bool operator >(const Node &e) const{
    return score > e.score;
  }    
};

class PegJumping{
  public:
    int getPegNumber(int y, int x){
      assert(g_field[y][x] != PLAIN);

      return g_pegHash[(g_field[y][x] & PEG_MASK)];
    }

    string move2string(int y, int x, string move){
      return (int2string(y) + " " + int2string(x) + " " + move);
    }

    /**
     * 現在いる座標からある座標に飛べるかどうかをチェックする
     * 条件1: 飛ぶ先が平地
     * 条件2: 間にペグが存在している
     */
    bool canJumping(int y, int x, int direct){
      //fprintf(stderr,"canJumping => y = %d, x = %d\n", y, x);
      int ny = y + DY[direct];
      int nx = x + DX[direct];

      int dy = y + DY[direct] * 2;
      int dx = x + DX[direct] * 2;

      if(g_field[dy][dx] != PLAIN) return false;
      return g_directHash[(g_field[ny][nx] & DIRECT_MASK)] > 0;
    }

    /**
     * ジャンプする
     * 出発地点を平地に
     * 目的地にペグ
     * 飛んだペグは消す
     */
    void jumpPeg(int fromY, int fromX, int direct){
      fprintf(stderr,"jumpPeg =>\n");
      int pegType = g_field[fromY][fromX];
      g_field[fromY][fromX] = PLAIN;

      int ny = fromY + DY[direct];
      int nx = fromX + DX[direct];
      g_field[ny][nx] = PLAIN;

      int dy = fromY + DY[direct] * 2;
      int dx = fromX + DX[direct] * 2;
      g_field[dy][dx] = pegType;
    }

    void init(vector<int> pegValue, vector<string> board){
      memset(g_field, GUARD, sizeof(g_field));

      int peg_num = pegValue.size();
      for(int i = 0; i < peg_num; i++){
        g_pegValue[i] = pegValue[i];
      }

      g_height = board.size();
      g_width = board[0].size();

      fprintf(stderr,"height = %d, width = %d\n", g_height, g_width);

      for(int y = 2; y < g_height+2; y++){
        for(int x = 2; x < g_width+2; x++){
          char ch = board[y-2][x-2];

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
      showField();

      string str;

      while(str != "NO"){
        str = getNextPegMove();

        if(str != "NO"){
          ret.push_back(str);
        }
      }

      return ret;
    }

    /**
     * 指定した座標のペグのスコアを取得する
     */
    int getPegValue(int y, int x){
      return g_pegValue[g_pegHash[(g_field[y][x] & PEG_MASK)]];
    }

    string getNextPegMove(){
      string str;
      int max_score = INT_MIN;
      int bestY, bestX, bestDirect;

      for(int y = 2; y < g_height+2; y++){
        for(int x = 2; x < g_width+2; x++){
          for(int direct = 0; direct < 4; direct++){
            if(g_field[y][x] != PLAIN && canJumping(y, x, direct)){
              fprintf(stderr,"can jump: y = %d, x = %d, direct = %d\n", y, x, direct); 
              int score = getPegValue(y, x);

              if(max_score < score){
                max_score = score;
                bestY = y;
                bestX = x;
                bestDirect = direct;
              }
            }
          }
        }
      }

      if(max_score != INT_MIN){
        jumpPeg(bestY, bestX, bestDirect);
        return move2string(bestY, bestX, DS[bestDirect]);
      }else{
        return "NO";
      }
    }

    void showField(){
      for(int y = 2; y < g_height+2; y++){
        for(int x = 2; x < g_width+2; x++){
          fprintf(stderr,"%3d", g_field[y][x]);
        }
        fprintf(stderr,"\n");
      }
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

