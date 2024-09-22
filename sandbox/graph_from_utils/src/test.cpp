#include <gtest/gtest.h>

#include "graph.hpp"

TEST(GraphTest, CreateNonWeightedGraph) {
  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  Graph graph = Graph::GraphNonWeighted(edges_pairs);

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 3);

  ASSERT_FALSE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());
}

TEST(GraphTest, CreateWeightedGraph) {
  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  std::vector<long> weights = {1, 2, 3};
  Graph graph = Graph::GraphWeighted(edges_pairs, weights);

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 3);

  ASSERT_TRUE(graph.IsWeighted());
  ASSERT_TRUE(graph.IsOrient());
}

TEST(GraphTest, CreateGraphFromAdjacencyMatrix) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);
  graph.Disorient();

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 2);

  ASSERT_FALSE(graph.IsWeighted());
}

TEST(GraphTest, CreateGraphFromAdjacencyMatrix2) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 4);

  ASSERT_FALSE(graph.IsWeighted());
}

TEST(GraphTest, CreateWeightedGraphFromAdjacencyMatrix) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 5}, {0, 7, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix, true);
  graph.Disorient();

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 2);

  ASSERT_TRUE(graph.IsWeighted());
}

TEST(GraphTest, CreateWeightedGraphFromAdjacencyMatrix2) {
  std::vector<std::vector<long>> adj_matrix = {{0, 1, 0}, {1, 0, 9}, {0, 6, 0}};
  Graph graph = Graph::GraphFromAdjMatrix(adj_matrix, true);

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 4);

  ASSERT_TRUE(graph.IsWeighted());
}

TEST(GraphTest, CreateGraphFromAdjacencyList) {
  std::vector<std::vector<size_t>> adj_list = {{1}, {0, 2}, {1}};
  Graph graph = Graph::GraphFromAdjList(adj_list);
  graph.Disorient();

  ASSERT_EQ(graph.VertsSize(), 3);
  ASSERT_EQ(graph.EdgesSize(), 2);

  ASSERT_FALSE(graph.IsWeighted());

  graph.Orient();
  ASSERT_TRUE(graph.IsOrient());
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
  ASSERT_EQ(g.VertsSize(), 0);
  ASSERT_EQ(g.EdgesSize(), 0);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_TRUE(g.IsOrient());
}

TEST(GraphTest, CreateGraphWithDuplicateEdges) {
  std::vector<std::pair<size_t, size_t>> edges = {
      {0, 1}, {1, 2}, {0, 1}, {2, 1}, {1, 2}};
  // для скорости работы по умолчанию дубликаты допускаются
  Graph g = Graph::GraphNonWeighted(edges);
  ASSERT_EQ(g.VertsSize(), 3);
  ASSERT_EQ(g.EdgesSize(), 5);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_TRUE(g.IsOrient());

  g.RemoveDuplicates();

  ASSERT_EQ(g.VertsSize(), 3);
  ASSERT_EQ(g.EdgesSize(), 3);
  ASSERT_FALSE(g.IsWeighted());
  ASSERT_TRUE(g.IsOrient());

  g.Disorient();

  ASSERT_EQ(g.VertsSize(), 3);
  ASSERT_EQ(g.EdgesSize(), 2);
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
