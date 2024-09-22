#include <gtest/gtest.h>

#include "graph.hpp"

TEST(GraphTest, CreateNonWeightedGraph) {
  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  Graph graph = Graph::GraphNonWeighted(edges_pairs);

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 3);

  ASSERT_FALSE(graph.IsWeighted());
}

TEST(GraphTest, CreateWeightedGraph) {
  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  std::vector<double> weights = {1.0, 2.0, 3.0};
  Graph graph = Graph::GraphWeighted(edges_pairs, weights);

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 3);

  ASSERT_TRUE(graph.IsWeighted());
}

TEST(GraphTest, CreateGraphFromAdjacencyMatrix) {
  std::vector<std::vector<double>> adj_matrix = {
      {0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);

  // std::cout << graph << std::endl;
  graph.Disorient();
  // std::cout << graph << std::endl;

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 2);

  ASSERT_FALSE(graph.IsWeighted());
}

TEST(GraphTest, CreateWeightedGraphFromAdjacencyMatrix) {
  std::vector<std::vector<double>> adj_matrix = {
      {0, 1, 0}, {1, 0, 2.5}, {0, 2.5, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix, true);
  graph.Disorient();

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 2);

  ASSERT_TRUE(graph.IsWeighted());
}

TEST(GraphTest, CreateGraphFromAdjacencyList) {
  std::vector<std::vector<size_t>> adj_list = {{1}, {0, 2}, {1}};
  Graph graph = Graph::GraphFromAdjList(adj_list);
  graph.Disorient();

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 2);

  ASSERT_FALSE(graph.IsWeighted());
}
