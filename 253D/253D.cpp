
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 400 + 11;
  const int ALPHABETS = 26;
  // storages
  int H, W;
  LL K;
  string S[SIZE];

  LL A[SIZE][SIZE];
  int cols[ALPHABETS][SIZE];
  int cols_num[ALPHABETS];

  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      get_sum();
      result = get_rects();
    }

    int get_index( char c ) {
      return c - 'a';
    }

    LL get_rects() {
      LL res = 0;
      for ( int r1 = 0; r1 < H; ++ r1 ) {
        for ( int r2 = r1 + 1; r2 < H; ++ r2 ) {
          fill(cols_num, cols_num + ALPHABETS, 0);
          for ( int ck = 0; ck < W; ++ ck ) {
            if ( S[r1][ck] == S[r2][ck] ) {
              cols[get_index(S[r1][ck])][cols_num[get_index(S[r1][ck])] ++] = ck;
            }
          }
          for ( char c = 'a'; c <= 'z'; ++ c ) {
            int num = cols_num[get_index(c)];
            if ( num < 2 )
              continue;
            int c2 = 0;
            for ( int c1 = 0; c1 < num; ++ c1 ) {
              c2 = max(c2, c1 + 1);
              for ( ; c2 < num; ++ c2 ) {
                if ( get_a_sum(r1, cols[get_index(c)][c1], r2, cols[get_index(c)][c2]) > K ) {
                  break;
                }
              }
              res += c2 - c1 - 1;
            }
          }
        }
      }
      return res;
    }

    LL get_a_sum( int r1, int c1, int r2, int c2 ) {
      return get_a(r2, c2) - get_a(r1 - 1, c2) - get_a(r2, c1 - 1) + get_a(r1 - 1, c1 - 1);
    }

    LL get_a( int r, int c ) {
      return ( r < 0 || r >= H || c < 0 || c >= W ) ? 0 : A[r][c];
    }

    void get_sum() {
      // A[i][j] := (0, 0)から(i, j)までの累積和
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          A[i][j] = get_a(i - 1, j) + get_a(i, j - 1) - get_a(i - 1, j - 1) + ( S[i][j] == 'a' ? 1 : 0 );
        }
      }
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void init() {
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          A[i][j] = 0;
      for ( int i = 0; i < ALPHABETS; ++ i )
        cols_num[i] = 0;
    }
    
    bool input() {
      if ( ! ( cin >> H >> W >> K ) )
        return false;
      for ( int i = 0; i < H; ++ i )
        cin >> S[i];
      return true;
    }

    void output() {
      cout << result << endl << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  std::freopen("input.txt", "r", stdin);
  std::freopen("output.txt", "w", stdout);
  return solution::Solution().run();
}

