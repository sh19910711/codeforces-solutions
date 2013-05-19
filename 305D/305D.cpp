
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

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    typedef set<int> Set;

    const int V_SIZE = 1000000 + 11;
    const int E_SIZE = 100000 + 11;
    const LL MOD = 1000000000 + 7;

    const int OFF = 0;
    const int ON = 1;

    int n;
    int m;
    int k;
    set <int> G[V_SIZE];
    int EF[E_SIZE];
    int ET[E_SIZE];
    LL D[V_SIZE][2];

    void init_graph() {
        for ( int i = 0; i < m; ++ i )
            G[EF[i]].insert(ET[i]);
    }

    bool is_invalid() {
        bool jump[n];
        fill(jump, jump + n, false);
        for ( int i = 0; i < n; ++ i ) {
            if ( G[i].size() == 1 ) {
                if ( ! G[i].count(i + 1) )
                    jump[i] = true;
            } else if ( G[i].size() > 1 ) {
                jump[i] = true;
            }
        }

        for ( int i = 0; i < n; ++ i ) {
            if ( ! jump[i] )
                continue;
            for ( Set::iterator it_i = G[i].begin(); it_i != G[i].end(); ++ it_i ) {
                int j = *it_i;
                if ( j <= i + 1 )
                    continue;
                if ( jump[j] )
                    return true;
            }
        }

        for ( int i = 0; i < n; ++ i ) {
            for ( Set::iterator it_i = G[i].begin(); it_i != G[i].end(); ++ it_i ) {
                int j = *it_i;
                if ( i >= j )
                    return true;
            }
        }

        return false;
    }
    
    LL solve() {
        init_graph();

        if ( is_invalid() )
            return 0;
        
        D[0][OFF] = 1;
        for ( int i = 0; i < n; ++ i ) {
            D[i + 1][OFF] = ( D[i][OFF] + D[i][ON] ) % MOD;
            if ( ! G[i].count(i + 1) )
                D[i + 1][OFF] = ( D[i + 1][OFF] + 1 ) % MOD;
            if ( i + k + 1 < n && ! G[i].count(i + k + 1) )
                D[i + k + 1][ON] = ( D[i + k + 1][ON] + D[i][OFF] ) % MOD;
        }
        return ( D[n - 1][OFF] - 1 + MOD ) % MOD;
    }

    class Solution: public ISolution {
    public:

        void init() {
            for ( int i = 0; i < V_SIZE; ++ i )
                for ( int j = 0; j < 2; ++ j )
                    D[i][j] = 0;
            for ( int i = 0; i < V_SIZE; ++ i )
                G[i].clear();
        }
        
        bool input() {
            if ( ! ( cin >> n >> m >> k ) )
                return false;
            for ( int i = 0; i < m; ++ i ) {
                cin >> EF[i] >> ET[i];
                EF[i] --;
                ET[i] --;
            }
            return true;
        }

        void output( LL result ) {
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

