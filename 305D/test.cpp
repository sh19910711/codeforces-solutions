#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;

typedef pair <int, int> Edge;
typedef boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
> Graph;

const int SIZE = 1000000 + 11;

int n, m, k;
int from[SIZE];
int to[SIZE];

Edge edges[SIZE];
int edges_num;
int weights[SIZE];

bool input() {
  if ( ! ( cin >> n >> m >> k ) )
    return false;
  for ( int i = 0; i < m; ++ i ) {
    cin >> from[i] >> to[i];
  }
  return true;
}

int main() {
  input();

  edges_num = 0;

  for ( int i = 0; i < m; ++ i ) {
    cout << i << ": " << from[i] << " -> " << to[i] << endl;
    edges[edges_num ++] = Edge(from[i] - 1, to[i] - 1);
  }

  for ( int i = 0; i < edges_num; ++ i )
    weights[i] = 1;
  
  Graph graph(edges, edges + edges_num, weights, n);

  const string name = "1234567";

  std::ofstream ofs1("graph_1.dot");
  boost::write_graphviz(ofs1, graph, boost::make_label_writer(name.c_str()));

  input();

  edges_num = 0;

  for ( int i = 0; i < m; ++ i ) {
    cout << i << ": " << from[i] << " -> " << to[i] << endl;
    edges[edges_num ++] = Edge(from[i] - 1, to[i] - 1);
  }

  for ( int i = 0; i < edges_num; ++ i )
    weights[i] = 1;
  
  Graph graph2(edges, edges + edges_num, weights, n);

  std::ofstream ofs2("graph_2.dot");
  boost::write_graphviz(ofs2, graph2, boost::make_label_writer(name.c_str()));

  return 0;
}

