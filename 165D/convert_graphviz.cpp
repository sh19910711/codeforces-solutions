#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

const int SIZE = 10000 + 11;
int n;
int A[SIZE];
int B[SIZE];

Graph G;

bool input() {
  if ( ! ( cin >> n ) )
    return false;
  for ( int i = 0; i < n - 1; ++ i ) {
    cin >> A[i] >> B[i];
  }
  return true;
}

void normalize() {
  for ( int i = 0; i < n - 1; ++ i ) {
    A[i] --;
    B[i] --;
  }
}

int main() {
  while ( input() ) {
    normalize();
    G = Graph(n);

    for ( int i = 0; i < n - 1; ++ i ) {
      boost::add_edge(A[i], B[i], G);
    }

    const char* names[9] = {
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "9"
    };
    boost::write_graphviz(std::cout, G, boost::make_label_writer(names));
  }
  return 0;
}
