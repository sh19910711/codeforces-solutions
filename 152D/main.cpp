
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

  typedef std::set<int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE     = 1000 + 11;
  const string YES   = "YES";
  const string NO    = "NO";
  const char HATCHED = '#';
  const char USED    = '@';
  const char EMPTY   = '.';

  // storages
  int H, W;
  string S[SIZE];

  Set s_cand_r;
  Set s_cand_c;
  int cand_r[SIZE];
  int cand_r_num;
  int cand_c[SIZE];
  int cand_c_num;
  int hatched_num;
  int used_num;

  int ar1, ac1, ar2, ac2;
  int br1, bc1, br2, bc2;

  bool result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      hatched_num = calc_hatched_num();
      compress();
      result = has_two_rectangles();
    }

    int calc_hatched_num() {
      int res = 0;
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] == HATCHED ) {
            res ++;
          }
        }
      }
      return res;
    }

    void compress() {
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] != HATCHED ) {
            continue;
          }
          if ( has_three_hatched_cell_in_row(i, j) ) {
            s_cand_r.insert(i);
          }
          if ( has_three_hatched_cell_in_col(i, j) ) {
            s_cand_c.insert(j);
          }
        }
      }
      if ( s_cand_r.size() > 4 ) {
        s_cand_r.erase(++ ++ s_cand_r.begin(), -- -- s_cand_r.end());
      }
      if ( s_cand_c.size() > 4 ) {
        s_cand_c.erase(++ ++ s_cand_c.begin(), -- -- s_cand_c.end());
      }
      std::copy(s_cand_r.begin(), s_cand_r.end(), cand_r);
      cand_r_num = s_cand_r.size();
      std::copy(s_cand_c.begin(), s_cand_c.end(), cand_c);
      cand_c_num = s_cand_c.size();
    }

    bool has_three_hatched_cell_in_row( int r, int c ) {
      if ( c - 1 < 0 || c + 1 >= W ) {
        return false;
      }
      return S[r][c - 1] == HATCHED && S[r][c + 1] == HATCHED;
    }

    bool has_three_hatched_cell_in_col( int r, int c ) {
      if ( r - 1 < 0 || r + 1 >= H ) {
        return false;
      }
      return S[r - 1][c] == HATCHED && S[r + 1][c] == HATCHED;
    }

    bool has_two_rectangles() {
      if ( cand_r_num > 4 && cand_c_num > 4 ) {
        return false;
      }
      return has_two_rectangles_1();
    }

    bool has_two_rectangles_1() {
      for ( int r1 = 0; r1 < cand_r_num; ++ r1 ) {
        for ( int c1 = 0; c1 < cand_c_num; ++ c1 ) {
          for ( int r2 = r1 + 1; r2 < cand_r_num; ++ r2 ) {
            for ( int c2 = c1 + 1; c2 < cand_c_num; ++ c2 ) {
              ar1 = cand_r[r1], ac1 = cand_c[c1];
              ar2 = cand_r[r2], ac2 = cand_c[c2];
              if ( ar2 - ar1 < 2 || ac2 - ac1 < 2 ) {
                continue;
              }
              if ( has_two_rectangles_2() ) {
                return true;
              }
            }
          }
        }
      }
      return false;
    }

    bool has_two_rectangles_2() {
      for ( int r1 = 0; r1 < cand_r_num; ++ r1 ) {
        for ( int c1 = 0; c1 < cand_c_num; ++ c1 ) {
          for ( int r2 = r1 + 1; r2 < cand_r_num; ++ r2 ) {
            for ( int c2 = c1 + 1; c2 < cand_c_num; ++ c2 ) {
              br1 = cand_r[r1], bc1 = cand_c[c1];
              br2 = cand_r[r2], bc2 = cand_c[c2];
              if ( br2 - br1 < 2 || bc2 - bc1 < 2 ) {
                continue;
              }
              if ( check(ar1, ac1, ar2, ac2) && check(br1, bc1, br2, bc2) && used_num == hatched_num ) {
                return true;
              }
              reset(ar1, ac1, ar2, ac2);
              reset(br1, bc1, br2, bc2);
            }
          }
        }
      }
      return false;
    }

    bool check( int r1, int c1, int r2, int c2 ) {
      if ( r2 - r1 < 2 || c2 - c1 < 2 ) {
        return false;
      }
      for ( int r = r1; r <= r2; ++ r ) {
        if ( S[r][c1] == EMPTY || S[r][c2] == EMPTY ) {
          return false;
        }
        if ( S[r][c1] == HATCHED ) {
          S[r][c1] = USED;
          used_num ++;
        }
        if ( S[r][c2] == HATCHED ) {
          S[r][c2] = USED;
          used_num ++;
        }
      }
      for ( int c = c1; c <= c2; ++ c ) {
        if ( S[r1][c] == EMPTY || S[r2][c] == EMPTY ) {
          return false;
        }
        if ( S[r1][c] == HATCHED ) {
          S[r1][c] = USED;
          used_num ++;
        }
        if ( S[r2][c] == HATCHED ) {
          S[r2][c] = USED;
          used_num ++;
        }
      }
      return true;
    }

    void reset( int r1, int c1, int r2, int c2 ) {
      if ( r2 - r1 < 2 || c2 - c1 < 2 ) {
        return;
      }
      for ( int r = r1; r <= r2; ++ r ) {
        if ( S[r][c1] == EMPTY || S[r][c2] == EMPTY ) {
          return;
        }
        if ( S[r][c1] == USED ) {
          S[r][c1] = HATCHED;
          used_num --;
        }
        if ( S[r][c2] == USED ) {
          S[r][c2] = HATCHED;
          used_num --;
        }
      }
      for ( int c = c1; c <= c2; ++ c ) {
        if ( S[r1][c] == EMPTY || S[r2][c] == EMPTY ) {
          return;
        }
        if ( S[r1][c] == USED ) {
          S[r1][c] = HATCHED;
          used_num --;
        }
        if ( S[r2][c] == USED ) {
          S[r2][c] = HATCHED;
          used_num --;
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
      s_cand_r.clear();
      s_cand_c.clear();
      used_num = 0;
      cand_r_num = cand_c_num = 0;
    }

    bool input() {
      if ( ! ( cin >> H >> W ) )
        return false;

      for ( int i = 0; i < H; ++ i ) {
        cin >> S[i];
      }

      return true;
    }

    void output() {
      cout << ( result ? YES : NO ) << endl;
      if ( result ) {
        cout << ar1 + 1 << " " << ac1 + 1 << " " << ar2 + 1 << " " << ac2 + 1 << endl;
        cout << br1 + 1 << " " << bc1 + 1 << " " << br2 + 1 << " " << bc2 + 1 << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

