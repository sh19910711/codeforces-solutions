
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
        static const int SIZE = 26;
        ValueType value;
        Trie *next[SIZE];
        Trie() { clear(); }
        void clear() { value = 0; std::fill( next, next+SIZE, (Trie*)NULL ); }
        Trie& find( const std::string& s ) {
            Trie* res = this;
            for ( StringIterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
                const int& c = *it_i;
                if ( ! res->next[c] ) res->next[c] = new Trie;
                res = res->next[c];
            }
            return *res;
        }
        int count( const std::string& s ) {
            Trie* res = this;
            for ( StringIterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
                const int& c = *it_i;
                if ( ! res->next[c] ) return 0;
                res = res->next[c];
            }
            return 1;
        }
        ValueType& operator []( const std::string& s ) { return find(s).value; }
    };
}


// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    table::Trie<int> T;

    int n;

    class Solution: public ISolution {
    public:
        void init() {
            T.clear();
        }
        bool input() {
            return cin >> n;
        }
        void solve() {
            for ( int i = 0; i < n; ++ i ) {
                string s;
                cin >> s;
                string t = s;
                for ( int j = 0; j < (int)t.size(); ++ j )
                    t[j] = t[j] - 'a';
                if ( T[t] == 0 ) {
                    cout << "OK" << endl;
                } else {
                    cout << s << T[t] << endl;
                }
                T[t] ++;
            }
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



