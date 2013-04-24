
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
    template <class ValueType> class Trie {
    public:
        typedef std::string::const_iterator StringIterator;
        static const int SIZE = 256;
        ValueType value;
        Trie *next[SIZE];
        Trie() { clear(); }
        void clear() { value = false; std::fill( next, next+SIZE, (Trie*)NULL ); }
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
    
    typedef table::Trie<bool> Trie;

    const int SIZE = 31;
    int n;
    string S[SIZE];
    Trie T;

    void add_substring( string s ) {
        int n = s.size();
        for ( int i = 0; i < n; ++ i ) {
            for ( int j = i; j < n; ++ j ) {
                int len = j - i + 1;
                string sub = s.substr(i, len);
                T[sub] = true;
            }
        }
    }
    
    class Solution: public ISolution {
    public:

        void init() {
            T.clear();
        }
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> S[i];
            return true;
        }

        string calc() {
            typedef queue <string> Queue;
            Queue Q;
            for ( char c = 'a'; c <= 'z'; ++ c ) {
                string s;
                s += c;
                Q.push(s);
            }
            while ( ! Q.empty() ) {
                string s = Q.front();
                Q.pop();

                if ( ! T[s] )
                    return s;

                for ( char c = 'a'; c <= 'z'; ++ c ) {
                    string ns = s + c;
                    if ( ! T[ns] ) {
                        Q.push(ns);
                    }
                }
            }
            return "";
        }
        
        string solve() {
            T[""] = true;
            for ( int i = 0; i < n; ++ i )
                add_substring(S[i]);
            return calc();
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


