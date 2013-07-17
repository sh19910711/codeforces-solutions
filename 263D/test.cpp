#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;

typedef pair <int, int> Edge;
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

const int SIZE = 100000 + 11;

int n, m, k;
int A[SIZE];
int B[SIZE];
Edge edges[SIZE];
int edges_num;

bool input() {
  if ( ! ( cin >> n >> m >> k ) )
    return false;
  for ( int i = 0; i < m; ++ i ) {
    cin >> A[i] >> B[i];
  }
  return true;
}

void normalize() {
  for ( int i = 0; i < m; ++ i ) {
    A[i] --;
    B[i] --;
  }
}

void generate_edges() {
  edges_num = 0;
  for ( int i = 0; i < m; ++ i )
    edges[edges_num ++] = Edge(A[i], B[i]);
}

string to_string( int x ) {
  std::ostringstream oss;
  oss << x;
  return oss.str();
}

int main() {
  string filename_prefix = "graph_";
  string filename_suffix = ".dot";
  int num = 0;
  while ( input() ) {
    num ++;
    normalize();
    generate_edges();

    Graph G(edges, edges + edges_num, n);
    const string name = "123456789";
    string filename = filename_prefix+to_string(num)+filename_suffix;
    std::ofstream ofs(filename.c_str());
    boost::write_graphviz(ofs, G, boost::make_label_writer(name.c_str()));
  }
  return 0;
}

