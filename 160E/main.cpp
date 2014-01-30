
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

#include <memory>
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
  const Int SIZE = 100000 + 11;
  const Int TREE_SIZE = 500000;
  const Int INF = std::numeric_limits<Int>::max();
  const Int NONE = INF;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorageMembers {
    Int N;
    Int M;
    Int S[SIZE];
    Int F[SIZE];
    Int T[SIZE];
    Int L[SIZE];
    Int R[SIZE];
    Int B[SIZE];
  };
  
  struct OutputStorageMembers {
    Int M;
    Int result[SIZE];
  };
  
  struct InputStorage: InputStorageMembers {
    InputStorage() {}
    InputStorage( const InputStorage* p ) { InputStorage* self = this; *self = *p; }
  };
  
  struct OutputStorage: OutputStorageMembers {
    OutputStorage() {}
    OutputStorage( const OutputStorage* p ) { OutputStorage* self = this; *self = *p; }
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  enum EventIndex {EVENT_POS, EVENT_TYPE, EVENT_TYPE_ID};
  enum EventType {EVENT_TYPE_BUS, EVENT_TYPE_PERSON};
  typedef std::tuple<Int, Int, Int> Event;
  typedef std::set<Event> Events;
  typedef std::unique_ptr<Events> EventsPointer;
  enum BusIndex {BUS_TIME, BUS_ID};
  typedef std::tuple<Int, Int> Bus;
  typedef std::set<Bus> Buses;
  typedef std::array<Buses, TREE_SIZE> BusesArray;
  typedef std::unique_ptr<BusesArray> BusesPointers;
  typedef std::map<Int, Int> Pos;

  struct Search: InputStorage {
    Search() {}
    Search( const InputStorage* p ) { InputStorage* self = this; *self = *p; }

    EventsPointer events;
    BusesPointers buses;
    Pos pos;
    Int pos_cnt;
    Int result[SIZE];
    Int result_time[SIZE];

    void search() {
      events = EventsPointer(new Events);
      buses = BusesPointers(new BusesArray);

      init_pos();
      init_events();
      init_buses();
      std::fill(begin(result), end(result), NONE);
      std::fill(begin(result_time), end(result_time), INF);

      for ( auto event : *events ) {
        const auto& type = std::get<EVENT_TYPE>(event);
        const auto& cur_pos = std::get<EVENT_POS>(event);
        if ( type == EVENT_TYPE_BUS ) {
          const auto& id = std::get<EVENT_TYPE_ID>(event);
          Int p = pos[F[id]];
          while ( p > 0 ) {
            (*buses)[p].insert(Bus(T[id], id));
            p -= p & -p;
          }
        } else if ( type == EVENT_TYPE_PERSON ) {
          const auto& id = std::get<EVENT_TYPE_ID>(event);
          Int p = pos[R[id]];
          while ( p < TREE_SIZE ) {
            const auto& bus = (*buses)[p];
            const auto& it_ret = bus.lower_bound(Bus(B[id], -1));
            if ( it_ret != end(bus) ) {
              auto bus_id = std::get<BUS_ID>(*it_ret);
              if ( result_time[id] > T[bus_id] ) {
                result[id] = bus_id + 1;
                result_time[id] = T[bus_id];
              }
            }
            p += p & -p;
          }
        }
      }
    }

    void init_pos() {
      pos.clear();
      for ( auto i = 0; i < N; ++ i ) {
        pos[S[i]] = 0;
        pos[F[i]] = 0;
      }
      for ( auto i = 0; i < M; ++ i ) {
        pos[L[i]] = 0;
        pos[R[i]] = 0;
      }
      pos_cnt = 1;
      for ( auto it_i = pos.begin(); it_i != pos.end(); ++ it_i ) {
        pos[it_i->first] = pos_cnt;
        pos_cnt ++;
      }
    }

    void init_buses() {
      for ( auto item : *buses )
        item.clear();
    }

    void init_events() {
      events->clear();
      for ( auto i = 0; i < N; ++ i ) {
        events->insert(Event(pos[S[i]], EVENT_TYPE_BUS, i));
      }
      for ( auto i = 0; i < M; ++ i ) {
        events->insert(Event(pos[L[i]], EVENT_TYPE_PERSON, i));
      }
    }
  };

  struct Solver: SolverInterface {
    Search search;
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      search = Search(in);
      out->M = in->M;
      search.search();
      std::copy(begin(search.result), end(search.result), begin(out->result));
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        std::cin >> in->S[i] >> in->F[i] >> in->T[i];
      for ( auto i = 0; i < in->M; ++ i )
        std::cin >> in->L[i] >> in->R[i] >> in->B[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      for ( auto i = 0; i < out->M; ++ i ) {
        if ( out->result[i] == NONE ) {
          std::cout << -1 << " ";
        } else {
          std::cout << out->result[i] << " ";
        }
      }
      std::cout << std::endl;
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



