
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


// @snippet<sh19910711/contest:set/disjoints_set.cpp>
namespace setlib {
    class DisjointSets {
    public:
        std::vector<int> data;
        DisjointSets( int size ): data(size, -1) {};
        void init( int size ) { data.resize(size); std::fill( data.begin(), data.end(), -1 ); }
        bool merge( int x, int y ) {
            x = root(x), y = root(y);
            if ( x != y ) {
                if ( data[y] < data[x] ) std::swap( x, y );
                data[x] += data[y], data[y] = x;
            }
            return x != y;
        }
        bool same( int x, int y ) { return root(x) == root(y); }
        int root( int x ) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    };
}


// @snippet<sh19910711/contest:io/config.cpp>
namespace io {
    const std::string OUTPUT_VECTOR_DELIMITER = ",";
}

// @snippet<sh19910711/contest:io/vector.cpp>
namespace io {
    template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
        typedef typename std::vector<T>::const_iterator Iterator;
        for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
            os << *it_i;
            if ( it_i + 1 != v.end() )
                os << OUTPUT_VECTOR_DELIMITER;
        }
        return os;
    }
    template <typename T> std::istream& operator >>( std::istream& is, std::vector<T>& v ) {
        int n = v.size();
        for ( int i = 0; i < n; ++ i ) {
            is >> v[i];
        }
        return is;
    }
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    using namespace setlib;
    using namespace io;
    
    typedef set<int> Set;

    const int SIZE = 1000 + 11;
    const int NONE = -1;
    
    int n, x;
    int A[SIZE]; // A[i] := front of i
    int B[SIZE]; // B[i] := back of i
    
    void get_norm() {
        x --;
        for ( int i = 0; i < n; ++ i )
            if ( A[i] == 0 )
                A[i] = NONE;
        for ( int i = 0; i < n; ++ i )
            if ( A[i] > 0 )
                A[i] --;
    }
    
    int get_front_length( int from ) {
        if ( A[from] != NONE )
            return 1 + get_front_length(A[from]);
        return 0;
    }
    
    int get_back_length( int from ) {
        if ( B[from] != NONE )
            return 1 + get_back_length(B[from]);
        return 0;
    }
    
    void solve() {
        get_norm();

        fill(B, B + SIZE, NONE);
        for ( int i = 0; i < n; ++ i )
            if ( A[i] >= 0 )
                B[A[i]] = i;
        
        bool ind[SIZE];
        fill(ind, ind + SIZE, false);
        int zeros = 0;
        for ( int i = 0; i < n; ++ i ) {
            if ( A[i] == NONE && B[i] == NONE )
                ind[i] = true;
            if ( i != x && ind[i] )
                zeros ++;
        }
        
        DisjointSets uf(n);
        for ( int i = 0; i < n; ++ i )
            if ( A[i] != NONE )
                uf.merge(i, A[i]);

        bool ok[SIZE];
        fill(ok, ok + SIZE, false);
        if ( ind[x] ) {
            VI lens;
            for ( int i = 0; i < n; ++ i ) {
                if ( ! ind[i] && uf.root(i) == i ) {
                    int len = 1 + get_front_length(i) + get_back_length(i);
                    lens.push_back(len);
                }
            }

            int m = lens.size();
            bool dp[SIZE][SIZE];
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    dp[i][j] = false;
            for ( int i = 0; i <= m; ++ i )
                dp[i][0] = true;
            for ( int i = 1; i <= m; ++ i ) {
                for ( int j = n; j >= 0; -- j ) {
                    if ( ! dp[i][j] )
                        continue;
                    {
                        int ni = i + 1;
                        int nj = j;
                        dp[ni][nj] = true;
                    }
                    {
                        int ni = i + 1;
                        int nj = j + lens[i - 1];
                        if ( nj <= n )
                            dp[ni][nj] = true;
                    }
                }
            }
            for ( int i = 0; i < SIZE; ++ i ) {
                for ( int j = 0; j < SIZE; ++ j ) {
                    if ( dp[i][j] ) {
                        for ( int o = 0; o <= zeros; ++ o )
                            ok[j + 1 + o] = true;
                    }
                }
            }
        } else {
            VI lens;
            for ( int i = 0; i < n; ++ i ) {
                if ( ! ind[i] && uf.root(i) == i && ! uf.same(i, x) ) {
                    int len = 1 + get_front_length(i) + get_back_length(i);
                    lens.push_back(len);
                }
            }

            int m = lens.size();
            bool dp[SIZE][SIZE];
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    dp[i][j] = false;
            for ( int i = 0; i <= m; ++ i )
                dp[i][0] = true;
            for ( int i = 1; i <= m; ++ i ) {
                for ( int j = n; j >= 0; -- j ) {
                    if ( ! dp[i][j] )
                        continue;
                    {
                        int ni = i + 1;
                        int nj = j;
                        dp[ni][nj] = true;
                    }
                    {
                        int ni = i + 1;
                        int nj = j + lens[i - 1];
                        if ( nj <= n )
                            dp[ni][nj] = true;
                    }
                }
            }

            int mine = get_front_length(x);
            for ( int i = 0; i < SIZE; ++ i ) {
                for ( int j = 0; j < SIZE; ++ j ) {
                    if ( dp[i][j] ) {
                        for ( int o = 0; o <= zeros; ++ o )
                            ok[mine + j + 1 + o] = true;
                    }
                }
            }
        }

        for ( int i = 1; i <= n; ++ i )
            if ( ok[i] )
                cout << i << endl;
        cout << endl;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n >> x ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }
        
        int run() {
            while ( init(), input() ) {
                solve();
                output();
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}



