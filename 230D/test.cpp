#include <iostream>
#include <fstream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;

typedef int EdgeWeight;
typedef std::vector<int> VI;

typedef boost::no_property GraphVertexProperty;
// typedef boost::no_property GraphEdgeProperty;
typedef boost::property<boost::edge_weight_t, EdgeWeight> GraphEdgeProperty;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        GraphVertexProperty, GraphEdgeProperty> Graph;

typedef std::pair<int, int> Edge;
typedef std::vector<Edge> Edges;

const int SIZE = 100000 + 11;

int n;
int m;
int A[SIZE];
int B[SIZE];
int C[SIZE];

int K[SIZE];
VI T[SIZE];

Graph G;
Edge edges[SIZE];
EdgeWeight edge_weights[SIZE];
int edges_num;

void init() {
  for ( int i = 0; i < SIZE; ++ i ) {
    T[i].clear();
  }

  edges_num = 0;
}

bool input() {
  if ( ! ( cin >> n >> m ) )
    return false;
  for ( int i = 0; i < m; ++ i )
    cin >> A[i] >> B[i] >> C[i];
  for ( int i = 0; i < n; ++ i ) {
    cin >> K[i];
    for ( int j = 0; j < K[i]; ++ j ) {
      int t;
      cin >> t;
      T[i].push_back(t);
    }
  }
  return true;
}

void normalize() {
  for ( int i = 0; i < m; ++ i ) {
    A[i] --;
    B[i] --;
  }
}

int main() {
  init();
  while ( input() ) {
    normalize();

    for ( int i = 0; i < m; ++ i ) {
      edges[edges_num ++] = Edge(A[i], B[i]);
    }
    for ( int i = 0; i < m; ++ i ) {
      edge_weights[i] = C[i];
    }

    G = Graph(edges, edges + edges_num, edge_weights, n);

    const char* vertex_names[8] = {
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8"
    };

    std::ofstream ofs("graph_sample_1.dot");
    boost::write_graphviz(ofs, G,
        boost::make_label_writer(vertex_names),
        boost::make_label_writer(boost::get(boost::edge_weight, G)));

  }
  return 0;
}

