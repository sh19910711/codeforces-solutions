
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

// @snippet<sh19910711/contest:text/suffix_array.cpp>
namespace text {
  class SuffixArray {
  public:
    typedef std::vector<int> VI;
    typedef VI::const_iterator Iterator;
    
    SuffixArray() { init(""); }
    SuffixArray( const std::string& s_ ) { init(s_); }
    
    void build() {
      int maxlen = n;
      for ( int i = 0; i < n; ++ i ) {
        rank[i] = s[i];
        maxlen = std::max( maxlen, s[i] + 1 );
      }
      VI cnt(maxlen, 0);
      for ( int i = 0; i < n; ++ i )
        cnt[rank[i]] ++;
      for ( int i = 1; i < maxlen; ++ i )
        cnt[i] += cnt[i-1];
      for ( int i = 0; i < n; ++ i )
        sa[--cnt[rank[i]]] = i;
      for ( k = 1; k < n; k *= 2 ) {
        VI r = rank;
        rank[sa[0]] = 0;
        for ( int i = 1; i < n; ++ i ) {
          int s1 = sa[i-1], s2 = sa[i];
          rank[s2] = r[s1] == r[s2] && std::max( s1, s2 ) + k < n && r[s1+k/2] == r[s2+k/2] ? rank[s1] : i;
        }
        for ( int i = 0; i < n; ++ i )
          cnt[i] = i;
        VI s = sa;
        for ( int i = 0; i < n; ++ i ) {
          int s1 = s[i] - k;
          if ( s1 >= 0 )
            sa[cnt[rank[s1]]++] = s1;
        }
      }
    }
    
    void init( const std::string& s_ ) {
      s = s_;
      n = s.size();
      sa.resize(n);
      rank.resize(n+1);
    }
    
    int find( const std::string& key ) const {
      using namespace std;
      int res = -1;
      int lb = -1, ub = n;
      for ( int i = 0; i < 20; ++ i ) {
        for ( int k = -1; k < 2; ++ k ) {
          int mid = std::max(0, std::min(n - 1, ( lb + ub ) / 2 + k));
          std::string t = s.substr( sa[mid] );
          if ( t.substr( 0, key.size() ) == key ) {
            if ( res < 0 ) {
              res = sa[mid];
            } else {
              res = std::min(res, sa[mid]);
            }
          }
          if ( t < key ) {
            lb = mid;
          } else {
            ub = mid;
          }
        }
      }
      return res;
    }
    
    Iterator begin() const { return sa.begin(); }
    Iterator end() const { return sa.end(); }
    const int& operator []( const int& k ) const { return sa[k]; }
    int size() const { return n; }
    
  protected:
    std::string s;
    int n, k;
    VI sa;
    VI rank;
  };
}

#include <array>

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
  const Int SIZE = 100 + 11;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::string String;
  typedef std::array<String, SIZE> Strings;
  typedef text::SuffixArray SuffixArray;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorageMembers {
    String S;
    Int M;
    Strings P;
  };
  
  struct OutputStorageMembers {
    Int result;
  };
  
  struct InputStorage: InputStorageMembers {
    InputStorage() {}
    InputStorage( const InputStorage* p ) { InputStorage* self = this; *self = *p; }
  };
  
  struct OutputStorage: OutputStorageMembers {
    OutputStorage() {}
    OutputStorage( const OutputStorage* p ) { *this = *p; }
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Search: InputStorage {
    // using InputStorage::InputStorage;
    
    Search() {}
    Search( const InputStorage* p ) {
      InputStorage* self = this;
      *self = *p;
    }

    SuffixArray sa;
    SuffixArray sa_inv;

    Int search() {
      Int res = 0;
      build_suffix_array();
      for ( auto i = 0; i < M; ++ i ) {
        if ( check_exist(P[i]) ) {
          res ++;
        }
      }
      return res;
    }

    bool check_exist( const String& s ) {
      auto n = S.size();
      auto len = s.size();
      for ( auto j = 1; j < len; ++ j ) {
        string l = s.substr(0, j);
        string r = s.substr(j);
        string r_inv = r;
        std::reverse(begin(r_inv), end(r_inv));
        auto nl = l.size();
        auto nr = r.size();
        auto l_pos = sa.find(l);
        auto r_pos = sa_inv.find(r_inv);
        if ( r_pos >= 0 )
          r_pos = n - r_pos - nr;
        if ( l_pos >= 0 && r_pos >= 0 ) {
          if ( l_pos + nl <= r_pos ) {
            return true;
          }
        }
      }
      return false;
    }

    void build_suffix_array() {
      sa.init(S);
      sa.build();
      string S_inv = S;
      std::reverse(begin(S_inv), end(S_inv));
      sa_inv.init(S_inv);
      sa_inv.build();
    }
  };

  struct Solver: SolverInterface {
    Search search;
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      search = Search(in);
      out->result = search.search();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->S ) )
        return false;
      std::cin >> in->M;
      for ( auto i = 0; i < in->M; ++ i )
        std::cin >> in->P[i];
      return true;
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


