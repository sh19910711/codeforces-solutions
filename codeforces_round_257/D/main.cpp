
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
/* default headers {{{ */
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
/* }}} */


// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  using namespace std;
  /* primitives {{{ */
  typedef long long Int;
  typedef long double Double;
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int N_MAX = 100000 + 11;
  const Int M_MAX = 3 * 100000 + 11;
  const Int K_MAX = 100000 + 11;
  
  const Int INF = numeric_limits<Int>::max() / 2;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int K;
    Int U[M_MAX];
    Int V[M_MAX];
    Int X[M_MAX];
    Int S[K_MAX];
    Int Y[K_MAX];
  };
  
  struct Output {
    Int res;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if (s >> in.N >> in.M >> in.K && in.N) {
        for (int i = 0; i < in.M; ++ i) s >> in.U[i] >> in.V[i] >> in.X[i];
        for (int i = 0; i < in.K; ++ i) s >> in.S[i] >> in.Y[i];
        return true;
      }
      return false;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.res << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Solution() {}
    
    bool solve() {
      out.res = find_max();
      return true;
    }
    
    typedef tuple<Int, Int> Node; // steps, cur
    typedef priority_queue<Node, vector<Node>, greater<Node>> NodeQueue;
    typedef tuple<Int, Int> Edge; // to, cost
    typedef vector<Edge> EdgeVector;
    typedef map<Int, Int> IntMap;
    
    Int dist[N_MAX];
    EdgeVector graph[N_MAX];
    IntMap id2index[N_MAX];
    
    Int find_max() {
      fill(dist, dist + N_MAX, INF);
      fill(graph, graph + N_MAX, EdgeVector());
      fill(id2index, id2index + N_MAX, IntMap());
      normalize_input();
      sort_input();
      generate_graph();
      update_dist_first();
      // check_dist();
      return update_dist();
    }
    
    bool update_dist_func() {
      return false;
    }
    
    Int update_dist() {
      Int res = 0;
      for ( Int i = 0; i < in.K; ++ i ) {
        if (update_dist_func()) {
          res ++;
        }
      }
      return res;
    }
    
    void check_dist() {
      cout << "@check_dist:" << endl;
      for (int i = 0; i < in.N; ++ i) {
        cout << "  " << i << ": " << dist[i] << endl;
      }
    }
    
    void normalize_input() {
      for (int i = 0; i < in.M; ++ i) {
        in.U[i] --;
        in.V[i] --;
      }
      for (int i = 0; i < in.K; ++ i) {
        in.S[i] --;
      }
    }
    
    typedef tuple<Int, Int, Int> Road;
    typedef vector<Road> RoadVector;
    typedef tuple<Int, Int> Train;
    typedef vector<Train> TrainVector;
    
    void sort_input() {
      RoadVector r;
      for(int i = 0; i < in.M; ++ i) r.push_back(Road(min(in.U[i], in.V[i]), max(in.U[i], in.V[i]), in.X[i]));
      sort(begin(r), end(r));
      for (int i = 0; i < in.M; ++ i) {
        in.U[i] = get<0>(r[i]);
        in.V[i] = get<1>(r[i]);
        in.X[i] = get<2>(r[i]);
      }
      
      TrainVector t;
      for(int i = 0; i < in.K; ++ i) t.push_back(Train(in.S[i], in.Y[i]));
      sort(begin(t), end(t));
      for (int i = 0; i < in.K; ++ i) {
        in.S[i] = get<0>(t[i]);
        in.Y[i] = get<1>(t[i]);
      }
    }
    
    typedef pair<Int, Int> VertexPair;
    typedef set<VertexPair> VertexPairSet;
    
    void generate_graph() {
      VertexPairSet vps;
      for (int i = 0; i < in.M; ++ i) {
        const auto& s = in.U[i];
        const auto& t = in.V[i];
        const auto& c = in.X[i];
        VertexPair st(s, t);
        if (vps.count(st)) continue;
        vps.insert(st);
        // printf("@gen_graph: %d, %d, %d\n", s, t, c);
        id2index[s][t] = graph[s].size();
        graph[s].push_back(Edge(t, c));
        id2index[t][s] = graph[t].size();
        graph[t].push_back(Edge(s, c));
      }
    }
    
    NodeQueue Q;
    
    void update_dist_first() {
      Q = NodeQueue();
      Q.push(Node(0, 0));
      dist[0] = 0;
      
      while (! Q.empty()) {
        const Node& node = Q.top();
        Q.pop();
        
        const auto& steps = get<0>(node);
        const auto& cur = get<1>(node);
        
        // cout << cur << ": " << steps << " steps" << endl;
        
        for ( const auto& e : graph[cur] ) {
          const auto& to = get<0>(e);
          const auto& len = get<1>(e);
          Int next_steps = steps + len;
          if ( next_steps >= dist[to] ) continue;
          dist[to] = next_steps;
          // cout << cur << " -> " << to << ": " << next_steps << endl;
          Q.push(Node(next_steps, to));
        }
      }
    }
    
    /* action methods {{{ */
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  /* Runner Class {{{ */
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
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

