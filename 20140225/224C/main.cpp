
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
  const Int SIZE = 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    String S;
  };
  struct Output {
    Int max_num;
    String S;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    Input in;
    Output out;

    typedef std::pair <Int, Int> Node; // (pos, type)
    typedef std::stack <Node> NodeStack;
    typedef std::array<NodeStack, SIZE> NodeStackArray;
    typedef std::array<Int, SIZE> IntArray;
    
    String S;
    IntArray cnt;

    Solution() {}
    
    bool solve() {
      S = in.S;
      init_cnt();
      auto ret = find_max_substring();
      out.max_num = std::count(std::begin(ret), std::end(ret), '[');
      out.S = ret;
      return true;
    }

    void init_cnt() {
      auto n = S.size();
      std::fill(std::begin(cnt), std::end(cnt), 0);
      cnt[0] = S[0] == '[' ? 1 : 0;
      for ( auto i = 1; i < n; ++ i ) {
        cnt[i] = cnt[i - 1];
        if ( S[i] == '[' )
          cnt[i] ++;
      }
    }

    Int get_cnt( const Int& id ) {
      if ( id < 0 )
        return 0;
      return cnt[id];
    }

    Int get_cnt( const Int& l, const Int& r ) {
      return get_cnt(r) - get_cnt(l - 1);
    }

    void print( const Int& l, const Int& r ) {
      std::cout << l << "-" << r << ": " << S.substr(l, r - l + 1);
    }

    String find_max_substring() {
      auto n = S.size();
      Int max_num = 0;
      String max_sub;
      NodeStack st;
      NodeStackArray st_range;
      for ( auto i = 0; i < n; ++ i ) {
        if ( S[i] == '[' ) {
          st.push(Node {i, 0});
        } else if ( S[i] == '(' ) {
          st.push(Node {i, 1});
        } else if ( S[i] == ']' ) {
          if ( ! st.empty() ) {
            auto tmp = st.top(); st.pop();
            auto l = tmp.first;
            auto r = i;
            if ( st_range[st.size()].size() ) {
              if ( st_range[st.size()].top().second == l - 1 ) {
                l = st_range[st.size()].top().first;
              }
              while ( st_range[st.size()].size() ) st_range[st.size()].pop();
            }
            auto len = r - l + 1;
            auto num = get_cnt(l, r);
            if ( tmp.second == 0 ) {
              if ( num > max_num ) {
                max_num = num;
                max_sub = S.substr(l, len);
              }
              st_range[st.size()].push(Node {l, r});
            } else {
              while ( st.size() ) st.pop();
              while ( st_range[st.size()].size() ) st_range[st.size()].pop();
            }
          }
        } else if ( S[i] == ')' ) {
          if ( ! st.empty() ) {
            auto tmp = st.top(); st.pop();
            auto l = tmp.first;
            auto r = i;
            if ( st_range[st.size()].size() ) {
              if ( st_range[st.size()].top().second == l - 1 ) {
                l = st_range[st.size()].top().first;
              }
              while ( st_range[st.size()].size() ) st_range[st.size()].pop();
            }
            auto len = r - l + 1;
            auto num = get_cnt(l, r);
            if ( tmp.second == 1 ) {
              if ( num > max_num ) {
                max_num = num;
                max_sub = S.substr(l, len);
              }
              st_range[st.size()].push(Node {l, r});
            } else {
              while ( st.size() ) st.pop();
              while ( st_range[st.size()].size() ) st_range[st.size()].pop();
            }
          }
        }
      }
      return max_sub;
    }
    
    template <class Stream> bool input( Stream& s ) {
      return s >> in.S;
    }
    
    template <class Stream> bool output( Stream& s ) {
      s << out.max_num << std::endl;
      s << out.S << std::endl;
      return s;
    }
    
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    //
    //
    //
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

