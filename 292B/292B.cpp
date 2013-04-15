
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
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
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

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    const int SIZE = 100011;
    const int NONE = -1;
    const string TYPE_BUS = "bus topology";
    const string TYPE_RING = "ring topology";
    const string TYPE_STAR = "star topology";
    const string TYPE_NONE = "unknown topology";
    
    int n, m;
    int X[SIZE];
    int Y[SIZE];
    VI G[SIZE];
    int D[SIZE];

    void generate_graph() {
        for ( int i = 0; i < m; ++ i ) {
            int x = X[i] - 1, y = Y[i] - 1;
            G[x].push_back(y);
            G[y].push_back(x);
            D[x] ++;
            D[y] ++;
        }
    }

    bool is_bus() {
        int cand1 = NONE, cand2 = NONE;
        for ( int i = 0; i < n; ++ i ) {
            if ( D[i] == 1 ) {
                if ( cand1 == NONE ) {
                    cand1 = i;
                } else if ( cand2 == NONE ) {
                    cand2 = i;
                } else {
                    return false;
                }
            }
        }
        if ( cand1 == NONE || cand2 == NONE )
            return false;
        for ( int i = 0; i < n; ++ i ) {
            if ( cand1 == i || cand2 == i )
                continue;
            if ( D[i] != 2 )
                return false;
        }
        return true;
    }

    bool is_ring() {
        for ( int i = 0; i < n; ++ i ) {
            if ( D[i] != 2 )
                return false;
        }
        return true;
    }

    bool is_star() {
        int cand1 = NONE;
        for ( int i = 0; i < n; ++ i ) {
            if ( D[i] == n - 1 ) {
                if ( cand1 != NONE )
                    return false;
                cand1 = i;
            }
        }
        if ( cand1 == NONE )
            return false;
        for ( int i = 0; i < n; ++ i ) {
            if ( cand1 == i )
                continue;
            if ( D[i] != 1 )
                return false;
        }
        return true;
    }

    class Solution: public ISolution {
    public:
        void init() {
            for ( int i = 0; i < SIZE; ++ i )
                G[i].clear();
            for ( int i = 0; i < SIZE; ++ i )
                D[i] = 0;
        }
        
        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            for ( int i = 0; i < m; ++ i ) {
                cin >> X[i] >> Y[i];
            }
            return true;
        }
        
        string solve() {
            generate_graph();
            bool f1 = is_bus();
            bool f2 = is_ring();
            bool f3 = is_star();
            int cnt = 0;
            if ( f1 )
                cnt ++;
            if ( f2 )
                cnt ++;
            if ( f3 )
                cnt ++;
            if ( cnt != 1 )
                return TYPE_NONE;
            if ( f1 )
                return TYPE_BUS;
            if ( f2 )
                return TYPE_RING;
            if ( f3 )
                return TYPE_STAR;
            return "hoge";
        }

        void output( string result ) {
            cout << result << endl;
        }
        
        int run() {
            while ( init(), input() ) {
                output(solve());
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

