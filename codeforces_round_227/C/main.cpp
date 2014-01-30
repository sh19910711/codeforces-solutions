
// @snippet<sh19910711/contest-base:headers.cpp>
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

#include <memory>
#include <array>

namespace utils {}


// @snippet<sh19910711/contest-base:solution/define-classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    SolverInterface* solver;
    Storages* storages;
    virtual int run() = 0;
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  using namespace utils;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/constants.cpp>
namespace solution {
  // constants
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::vector <std::string> VS;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    std::string S;
  };
  
  struct OutputStorage {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = get_maximum_number(in->S);
      return out;
    }

    static VS split( const std::string& s ) {
      VS res;
      string rs = s;
      std::reverse(begin(rs), end(rs));
      string tmp;
      for ( auto c : rs ) {
        tmp += c;
        if ( c != '0' ) {
          std::reverse(begin(tmp), end(tmp));
          res.push_back(tmp);
          tmp = "";
        }
      }
      if ( tmp != "" ) {
        std::reverse(begin(tmp), end(tmp));
        res.push_back(tmp);
        tmp = "";
      }
      std::reverse(begin(res), end(res));
      while ( res.size() >= 2 ) {
        bool flag = false;
        if ( res[0].size() == res[1].size() && res[0] < res[1] ) {
          flag = true;
        } else if ( res[0].size() < res[1].size() ) {
          flag = true;
        }
        if ( flag ) {
          // cout << "res = " << res[0] << " / " << res[1] << endl;
          res[0] += res[1];
          res.erase(begin(res) + 1);
        } else {
          break;
        }
      }
      while ( update(res) );
      return res;
    }

    static bool check( const string& a, const string& b ) {
      if ( a.size() > b.size() )
        return false;
      if ( a.size() < b.size() )
        return true;
      return a < b;
    }

    static bool update( VS& v ) {
      int n = v.size();
      if ( n <= 1 ) {
        return false;
      }
      if ( n == 2 ) {
        if ( check(v[0], v[1]) ) {
          VS nv;
          nv.push_back(v[0] + v[1]);
          v = nv;
          return true;
        }
        return false;
      }
      string tmp = "";
      for ( auto i = 0; i + 1 < n; ++ i ) {
        tmp += v[i];
        if ( check(tmp, v[i + 1]) ) {
          VS nv;
          nv.push_back(tmp);
          for ( int j = i + 1; j < n; ++ j ) {
            nv.push_back(v[j]);
          }
          v = nv;
          return true;
        }
      }
      return false;
    }
    
    static Int get_maximum_number( const std::string& s ) {
      VS ret = split(s);
      // cout << endl; for ( auto x : ret ) {cout << x << endl; } cout << endl;
      return ret.size();
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      return std::cin >> in->S;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->result << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  using namespace solution;
  std::cin.sync_with_stdio(false);
  static InputStorage in;
  static OutputStorage out;
  static Storages storages;
  static Solution solution;
  static Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

