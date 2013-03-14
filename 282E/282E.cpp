
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

// @snippet<sh19910711/contest:table/trie.cpp>
namespace table {
    // @desc トライ木の実装
    template <class ValueType> class Trie {
    public:
        typedef std::string::const_iterator StringIterator;
        static const int SIZE = 2;
        ValueType value;
        Trie *next[SIZE];
        Trie() { clear(); }
        void clear() {
            std::fill( next, next+SIZE, (Trie*)NULL );
        }
        Trie& find( const long long& s ) {
            Trie* res = this;
            int len = s > 0 ? log2(s) + 1 : 0;
            for ( int i = 40; i >= 0; -- i ) {
                long long bi = 1LL << i;
                int c = 0;
                if ( i < len )
                    c = ( ( s & bi ) > 0 ? 1 : 0 );
                if ( ! res->next[c] ) res->next[c] = new Trie;
                res = res->next[c];
            }
            return *res;
        }
        int count( const long long& s ) {
            Trie* res = this;
            int len = s > 0 ? log2(s) + 1 : 0;
            for ( int i = 0; i < len; ++ i ) {
                int bi = 1 << i;
                int c = ( s & bi ) > 0 ? 1 : 0;
                if ( ! res->next[c] ) return 0;
                res = res->next[c];
            }
            return 1;
        }
        ValueType& operator []( const long long& s ) { return find(s).value; }
    };
}


// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    
    typedef table::Trie<bool> Trie;

    const int SIZE = 100011;
    int n;
    LL A[SIZE];
    Trie T;
    
    class Solution: public ISolution {
    public:
        void init() {
            T.clear();
        }

        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }

        LL query( LL x ) {
            LL res = 0;
            Trie* cur = &T;
            int len = x > 0 ? log2(x) + 1 : 1;
            for ( int i = 40; i >= 0; -- i ) {
                LL bi = 1LL << i;
                int c = 0;
                if ( i < len )
                    c = ( ( x & bi ) > 0 ? 1 : 0 );
                if ( cur->next[1-c] != NULL ) {
                    cur = cur->next[1-c];
                    res *= 2;
                    res += 1;
                } else {
                    cur = cur->next[c];
                    res *= 2;
                }
            }
            return res;
        }

        LL solve() {
            LL whole = 0;
            for ( int i = 0; i < n; ++ i )
                whole ^= A[i];
            LL suffix = 0;
            for ( int i = 0; i < n; ++ i )
                suffix ^= A[i];
            LL prefix = 0;
            LL res = suffix;
            T[prefix] = true;
            for ( int i = 0; i < n; ++ i ) {
                prefix ^= A[i];
                suffix ^= A[i]; // suffixとして利用する値
                T[prefix] = true; // A[0...i]のxorが登録される
                res = max( res, query(suffix) );
            }
            return res;
        }

        int run() {
            while ( init(), input() ) {
                cout << solve() << endl;
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



