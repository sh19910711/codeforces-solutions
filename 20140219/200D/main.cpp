
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif

// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int SIZE = 1000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    String A[SIZE];
    Int M;
    String B[SIZE];
    Int K;
    String C[SIZE];
  };
  struct Output {
    Int results[SIZE];
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
 
    typedef std::map <String, Int> StringMap;
    typedef std::vector <Int> IntVector;
    enum Type { TYPE_INT, TYPE_STRING, TYPE_DOUBLE, TYPE_TEMPLATE };

    String def_func_name[SIZE];
    IntVector def_func[SIZE];
    StringMap var;
    String call_func_name[SIZE];
    IntVector call_func[SIZE];

    void init() {
    }
    
    void solve() {
      var.clear();
      std::fill(def_func, def_func + SIZE, IntVector());
      std::fill(call_func, call_func + SIZE, IntVector());
      parse();
      for ( auto i = 0; i < in->K; ++ i ) {
        out->results[i] = count(i);
      }
    }

    Int count( const Int& call_id ) {
      Int res = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        if ( call_func_name[call_id] == def_func_name[i] ) {
          if ( check(call_id, i) )
            res ++;
        }
      }
      return res;
    }

    bool check( const Int& call_id, const Int& def_id ) {
      Int num = call_func[call_id].size();
      if ( num != def_func[def_id].size() )
        return false;
      for ( auto i = 0; i < num; ++ i ) {
        if ( def_func[def_id][i] != TYPE_TEMPLATE && def_func[def_id][i] != call_func[call_id][i] )
          return false;
      }
      return true;
    }

    String conv( const String& s ) {
      String res = s;
      std::replace(std::begin(res), std::end(res), '(', ' ');
      std::replace(std::begin(res), std::end(res), ')', ' ');
      std::replace(std::begin(res), std::end(res), ',', ' ');
      return res;
    }

    Type get_type( const String& s ) {
      if ( s == "int" )
        return TYPE_INT;
      if ( s == "string" )
        return TYPE_STRING;
      if ( s == "double" )
        return TYPE_DOUBLE;
      return TYPE_TEMPLATE;
    }

    void parse() {
      for ( auto i = 0; i < in->N; ++ i ) {
        const String& s = conv(in->A[i]);
        std::istringstream iss(s);
        String t;
        iss >> t;
        iss >> def_func_name[i];
        while ( iss >> t )
          def_func[i].push_back(get_type(t));
      }
      for ( auto i = 0; i < in->M; ++ i ) {
        const String& s = conv(in->B[i]);
        std::istringstream iss(s);
        String type, name;
        iss >> type >> name;
        var[name] = get_type(type);
      }
      for ( auto i = 0; i < in->K; ++ i ) {
        const String& s = conv(in->C[i]);
        std::istringstream iss(s);
        iss >> call_func_name[i];
        String t;
        while ( iss >> t )
          call_func[i].push_back(var[t]);
      }
    }
    
    bool input() {
      return input_number(in->N) && input_lines(in->N, in->A) && input_number(in->M) && input_lines(in->M, in->B) && input_number(in->K) && input_lines(in->K, in->C);
    }

    bool input_number( Int& N ) {
      String line;
      if ( ! std::getline(std::cin, line) )
        return false;
      std::istringstream iss(line);
      return iss >> N;
    }

    bool input_lines( const Int& N, String S[SIZE] ) {
      for ( auto i = 0; i < N; ++ i ) {
        if ( ! ( std::getline(std::cin, S[i]) ) )
          return false;
      }
      return true;
    }
    
    void output() {
      for ( auto i = 0; i < in->K; ++ i ) {
        std::cout << out->results[i] << std::endl;
      }
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) { this->init(); }
    
    int run() {
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
    
    bool action() {
      if ( ! this->input() ) return false;
      this->solve();
      this->output();
      return true;
    }
    
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using namespace solution;
  static Input in;
  static Output out;
  static Solution sol(&in, &out);
  return sol.run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

