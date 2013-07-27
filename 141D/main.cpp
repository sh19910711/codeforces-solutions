
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
  typedef std::map<int, int> Map;

  typedef std::pair<int, int> Node;
  typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node> > Queue;
  
  class Ramp {
  public:
    friend istream& operator >> ( istream& is, Ramp& r ) {
      return is >> r.x >> r.d >> r.t >> r.p;
    }

    int getPrepared() {
      return x - p;
    }

    int getJumped() {
      return x + d;
    }

    int x, d, t, p;
  };
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 1000000 + 11;
  const int INF = std::numeric_limits<int>::max();
  const int ID_NONE = -1;
  const int PREV_NONE = -1;

  // event
  class Event {
  public:
    Event(): dest(-1), ramp_id(ID_NONE), dist(-1) {}

    Event& set_ramp_id( const int& id ) {
      ramp_id = id;
      return *this;
    }
    Event& set_dest( const int& x ) {
      dest = x;
      return *this;
    }
    Event& set_dist( const int& x ) {
      dist = x;
      return *this;
    }
    Event self() {
      return *this;
    }

    friend ostream& operator << ( ostream& os, const Event& e ) {
      return os << "(event: dest = " << e.dest << ", dist = " << e.dist << ", ramp_id = " << e.ramp_id << ")";
    }

    int dest;
    int ramp_id;
    int dist;
  };

  typedef std::vector<Event> Events;
  typedef std::map<int, Events> Pos2Event;

  // storages
  int n, L;
  Ramp ramps[SIZE];

  VI x;
  Map x_id; // x_id[pos] = id (x[id])
  Pos2Event pos2event;

  Queue Q;
  int min_dist[SIZE];
  int prev[SIZE];
  int prev_ramp_id[SIZE];

  int result;
  bool checked[SIZE];
  int used_ramps[SIZE];
  int used_ramps_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      compress();
      set_events();
      result = find_minimum_dist();
      build_route();
    }

    void build_route() {
      std::fill(checked, checked + SIZE, false);
      int pos = x_id[L];
      while ( pos != PREV_NONE ) {
        int ramp_id = prev_ramp_id[pos];
        if ( ramp_id != ID_NONE && ! checked[ramp_id] ) {
          used_ramps[used_ramps_num ++] = ramp_id;
          checked[ramp_id] = true;
        }
        pos = prev[pos];
      }
      std::reverse(used_ramps, used_ramps + used_ramps_num);
    }

    int find_minimum_dist() {
      int num = x.size();
      Q = Queue();
      std::fill(min_dist, min_dist + SIZE, INF);
      std::fill(prev, prev + SIZE, PREV_NONE);
      std::fill(prev_ramp_id, prev_ramp_id + SIZE, ID_NONE);
      Q.push(Node(0, 0));
      min_dist[0] = 0;

      while ( ! Q.empty() ) {
        Node node = Q.top();
        Q.pop();

        int dist = node.first;
        int pos = node.second;

        Events& events = pos2event[pos];
        for ( Events::iterator it_i = events.begin(); it_i != events.end(); ++ it_i ) {
          Event& event = *it_i;
          int next_dist = dist + event.dist;
          int next_pos = event.dest;
          if ( next_dist >= min_dist[next_pos] )
            continue;
          min_dist[next_pos] = next_dist;
          prev[next_pos] = pos;
          prev_ramp_id[next_pos] = event.ramp_id;
          Q.push(Node(next_dist, next_pos));
        }
      }

      return min_dist[num - 1];
    }

    void set_events() {
      int num = x.size();
      for ( int i = 0; i < num; ++ i ) {
        if ( i - 1 >= 0 )
          pos2event[i].push_back(Event().set_dest(i - 1).set_dist(x[i] - x[i - 1]).self());
        if ( i + 1 < num )
          pos2event[i].push_back(Event().set_dest(i + 1).set_dist(x[i + 1] - x[i]).self());
      }

      for ( int i = 0; i < n; ++ i ) {
        int p = ramps[i].getPrepared();
        if ( p < 0 )
          continue;
        int dest = ramps[i].getJumped();
        int time = ramps[i].p + ramps[i].t;
        pos2event[x_id[p]].push_back(Event().set_ramp_id(i).set_dest(x_id[dest]).set_dist(time).self());
      }
    }

    void compress() {
      Set x_set;
      x_set.insert(0);
      x_set.insert(L);
      for ( int i = 0; i < n; ++ i ) {
        x_set.insert(ramps[i].x);
        x_set.insert(ramps[i].getPrepared());
        x_set.insert(ramps[i].getJumped());
      }
      x_set.erase(x_set.begin(), x_set.lower_bound(0));
      x = VI(x_set.begin(), x_set.end());

      int num = x.size();
      for ( int i = 0; i < num; ++ i ) {
        x_id[x[i]] = i;
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
      result = INF;
      used_ramps_num = 0;
      x.clear();
      pos2event.clear();
      x_id.clear();
    }

    bool input() {
      if ( ! ( cin >> n >> L ) ) {
        return false;
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> ramps[i];
      }
      return true;
    }

    void output() {
      cout << result << endl;
      cout << used_ramps_num << endl;
      for ( int i = 0; i < used_ramps_num; ++ i ) {
        cout << used_ramps[i] + 1 << endl;
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

