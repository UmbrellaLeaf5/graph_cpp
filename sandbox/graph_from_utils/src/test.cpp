#include <gtest/gtest.h>

#include "graph.hpp"

TEST(GraphTest, CreateNonWeightedGraph) {
  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  Graph graph = Graph::GraphNonWeighted(edges_pairs);

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 3);

  ASSERT_FALSE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());
}

TEST(GraphTest, CreateWeightedGraph) {
  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  std::vector<long> weights = {1, 2, 3};
  Graph graph = Graph::GraphWeighted(edges_pairs, weights);

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 3);

  ASSERT_TRUE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());
}

TEST(GraphTest, CreateGraphFromAdjacencyMatrix) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // std::cout << graph.ReturnAdjList() << std::endl;

  graph.Disorient();

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 2);

  ASSERT_FALSE(graph.IsWeighted());

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // std::cout << graph.ReturnAdjList() << std::endl;
}

TEST(GraphTest, CreateGraphFromAdjacencyMatrix2) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 4);

  ASSERT_FALSE(graph.IsWeighted());

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // std::cout << graph.ReturnAdjList() << std::endl;
}

TEST(GraphTest, CreateWeightedGraphFromAdjacencyMatrix) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 5}, {0, 7, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix, true);

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // graph.PrintAdjList();
  // std::cout << graph << std::endl;

  graph.Disorient();

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 2);

  ASSERT_TRUE(graph.IsWeighted());

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // graph.PrintAdjList();
  // std::cout << graph << std::endl;
}

TEST(GraphTest, CreateWeightedGraphFromAdjacencyMatrix2) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 9}, {0, 6, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix, true);

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 4);

  ASSERT_TRUE(graph.IsWeighted());

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // std::cout << graph.ReturnAdjList() << std::endl;
}

TEST(GraphTest, CreateGraphFromAdjacencyList) {
  std::vector<std::vector<size_t>> adj_list = {{1}, {0, 2}, {1}};
  Graph graph = Graph::GraphFromAdjList(adj_list);

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // std::cout << graph.ReturnAdjList() << std::endl;

  graph.Disorient();

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 2);

  ASSERT_FALSE(graph.IsWeighted());

  graph.Orient();
  ASSERT_TRUE(graph.IsOrient());

  // std::cout << graph.ReturnAdjMatrix() << std::endl;
  // std::cout << graph.ReturnAdjList() << std::endl;
}

TEST(GraphTest, Disorient) {
  std::vector<std::pair<size_t, size_t>> edges = {{0, 1}, {1, 2}, {2, 0}};
  Graph g = Graph::GraphNonWeighted(edges);

  ASSERT_TRUE(g.IsOrient());
  g.Disorient();
  ASSERT_FALSE(g.IsOrient());
}

TEST(GraphTest, CreateGraphWithEmptyEdges) {
  std::vector<std::pair<size_t, size_t>> edges;
  Graph g = Graph::GraphNonWeighted(edges);

  ASSERT_EQ(g.VertsAmount(), 0);
  ASSERT_EQ(g.EdgesAmount(), 0);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_TRUE(g.IsOrient());
}

TEST(GraphTest, CreateGraphWithDuplicateEdges) {
  std::vector<std::pair<size_t, size_t>> edges = {
      {0, 1}, {1, 2}, {0, 1}, {2, 1}, {1, 2}};
  // для скорости работы по умолчанию дубликаты допускаются
  Graph g = Graph::GraphNonWeighted(edges);

  ASSERT_EQ(g.VertsAmount(), 3);
  ASSERT_EQ(g.EdgesAmount(), 5);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_TRUE(g.IsOrient());

  g.RemoveDuplicates();

  ASSERT_EQ(g.VertsAmount(), 3);
  ASSERT_EQ(g.EdgesAmount(), 3);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_TRUE(g.IsOrient());

  g.Disorient();

  ASSERT_EQ(g.VertsAmount(), 3);
  ASSERT_EQ(g.EdgesAmount(), 2);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_FALSE(g.IsOrient());
}

TEST(GraphTest, CreateGraphWithInvalidWeights) {
  std::vector<std::pair<size_t, size_t>> edges = {{0, 1}, {1, 2}, {2, 0}};
  std::vector<long> weights = {1, 2, -1};

  ASSERT_THROW(Graph::GraphWeighted(edges, weights), std::invalid_argument);
}

TEST(GraphTest, CreateGraphFromAdjMatrixWithInvalidSize) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1}, {1, 0, 1}, {1, 0}};

  ASSERT_THROW(Graph::GraphFromAdjMatrix(adj_matrix), std::invalid_argument);
}

TEST(GraphTest, GraphFromMapTest) {
  std::unordered_map<std::string, weight_t> edges_dict = {
      {"0->1", 5}, {"2->1", 1}, {"3->2", 2}, {"1->3", 3}};

  Graph graph = Graph::GraphFromMap(edges_dict);

  // graph.PrintAdjList();
  // std::cout << graph.ReturnAdjList() << std::endl;

  ASSERT_EQ(graph.VertsAmount(), 4);
  ASSERT_EQ(graph.EdgesAmount(), 4);

  ASSERT_TRUE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());

  std::unordered_map<std::string, weight_t> empty_edges_dict;
  Graph empty_graph = Graph::GraphFromMap(empty_edges_dict);

  ASSERT_EQ(empty_graph.VertsAmount(), 0);
  ASSERT_EQ(empty_graph.EdgesAmount(), 0);

  ASSERT_FALSE(empty_graph.IsWeighted());
  ASSERT_TRUE(empty_graph.IsOrient());

  std::unordered_map<std::string, weight_t> invalid_edges_dict = {
      {"0-1", 0}, {"2-1", 1}, {"3->2", 2}, {"1>3", 3}};

  ASSERT_THROW(Graph::GraphFromMap(invalid_edges_dict), std::invalid_argument);

  edges_dict = {{"0->14", 5}, {"25->1", 1}, {"3->2", 2}, {"1->3", 3}};

  graph = Graph::GraphFromMap(edges_dict);

  // graph.PrintAdjList();
  // std::cout << graph.ReturnAdjList() << std::endl;
  // std::cout << graph << std::endl;

  ASSERT_EQ(graph.VertsAmount(), 26);
  ASSERT_EQ(graph.EdgesAmount(), 4);

  ASSERT_TRUE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());
}

TEST(GraphTest, GraphFromStrsTest) {
  std::vector<std::string> edges_strs = {"0->1", "2->1", "3->2", "1->3"};
  Graph graph = Graph::GraphFromStrs(edges_strs);

  ASSERT_EQ(graph.VertsAmount(), 4);
  ASSERT_EQ(graph.EdgesAmount(), 4);

  ASSERT_FALSE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());

  std::vector<std::string> empty_edges_strs;
  Graph empty_graph = Graph::GraphFromStrs(empty_edges_strs);

  ASSERT_EQ(empty_graph.VertsAmount(), 0);
  ASSERT_EQ(empty_graph.EdgesAmount(), 0);

  ASSERT_FALSE(empty_graph.IsWeighted());
  ASSERT_TRUE(empty_graph.IsOrient());

  std::vector<std::string> invalid_edges_strs = {"0-1", "2-1", "3->2", "1>3"};
  ASSERT_THROW(Graph::GraphFromStrs(invalid_edges_strs), std::invalid_argument);

  invalid_edges_strs = {"0->vert", "2->1", "3->2", "1->3"};
  ASSERT_THROW(Graph::GraphFromStrs(invalid_edges_strs), std::invalid_argument);
}

TEST(GraphTest, GraphWeighted_EmptyInput) {
  std::vector<std::tuple<size_t, size_t, weight_t>> empty_input;
  Graph graph = Graph::GraphWeighted(empty_input);

  ASSERT_EQ(graph.VertsAmount(), 0);
  ASSERT_EQ(graph.EdgesAmount(), 0);
}

TEST(GraphTest, GraphWeighted_SingleEdge) {
  std::vector<std::tuple<size_t, size_t, weight_t>> input = {{0, 1, 5}};
  Graph graph = Graph::GraphWeighted(input);

  ASSERT_EQ(graph.VertsAmount(), 2);
  ASSERT_EQ(graph.EdgesAmount(), 1);
  ASSERT_TRUE(graph.IsWeighted());
}

TEST(GraphTest, GraphWeighted_MultipleEdges) {
  std::vector<std::tuple<size_t, size_t, weight_t>> input = {
      {0, 1, 5}, {1, 2, 10}, {2, 0, 3}};
  Graph graph = Graph::GraphWeighted(input);

  ASSERT_EQ(graph.VertsAmount(), 3);
  ASSERT_EQ(graph.EdgesAmount(), 3);
  ASSERT_TRUE(graph.IsWeighted());
}

TEST(GraphTest, Edges_EmptyGraph) {
  std::vector<std::tuple<size_t, size_t, weight_t>> empty_input;
  Graph graph = Graph::GraphWeighted(empty_input);
  auto edges = graph.Edges();

  ASSERT_TRUE(edges.empty());
}

TEST(GraphTest, Edges_SingleEdge) {
  std::vector<std::tuple<size_t, size_t, weight_t>> input = {{0, 1, 5}};
  Graph graph = Graph::GraphWeighted(input);
  auto edges = graph.Edges();

  ASSERT_EQ(edges.size(), 1);
  ASSERT_EQ(StartVert(edges[0]), 0);
  ASSERT_EQ(EndVert(edges[0]), 1);
  ASSERT_EQ(Weight(edges[0]), 5);
}

TEST(GraphTest, Edges_MultipleEdges) {
  std::vector<std::tuple<size_t, size_t, weight_t>> input = {
      {0, 1, 5}, {1, 2, 10}, {2, 0, 3}};
  Graph graph = Graph::GraphWeighted(input);
  auto edges = graph.Edges();

  ASSERT_EQ(edges.size(), 3);

  ASSERT_EQ(StartVert(edges[0]), 0);
  ASSERT_EQ(EndVert(edges[0]), 1);
  ASSERT_EQ(Weight(edges[0]), 5);

  ASSERT_EQ(StartVert(edges[1]), 1);
  ASSERT_EQ(EndVert(edges[1]), 2);
  ASSERT_EQ(Weight(edges[1]), 10);

  ASSERT_EQ(StartVert(edges[2]), 2);
  ASSERT_EQ(EndVert(edges[2]), 0);
  ASSERT_EQ(Weight(edges[2]), 3);
}

TEST(GraphTest, Edges_ConstAccess) {
  std::vector<std::tuple<size_t, size_t, weight_t>> input = {
      {0, 1, 5}, {1, 2, 10}, {2, 0, 3}};
  Graph graph = Graph::GraphWeighted(input);
  const auto& edges = graph.Edges();

  ASSERT_EQ(edges.size(), 3);

  ASSERT_EQ(StartVert(edges[0]), 0);
  ASSERT_EQ(EndVert(edges[0]), 1);
  ASSERT_EQ(Weight(edges[0]), 5);
}
