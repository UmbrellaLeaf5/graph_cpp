#include "graph.hpp"

std::ostream& operator<<(std::ostream& os, const Graph::Edge& edge) {
  os << edge.Name();
  return os;
}

double Graph::Edge::Weight() const {
  if (!IsWeighted())
    raise std::logic_error("Edge: " + Name() + " is not weighted.");

  return weight_;
}

const std::string& Graph::Edge::Name() const {
  if (IsWeighted())
    return "[" + std::to_string(StartVert()) + " -> " +
           std::to_string(EndVert()) + ", w: " + std::to_string(Weight()) + "]";

  else
    return "[" + std::to_string(StartVert()) + " -> " +
           std::to_string(EndVert()) + "]";
}

Graph Graph::GraphNonWeighted(
    const std::vector<std::pair<size_t, size_t>>& edges_pairs) {
  std::vector<Edge> edges{};
  edges.reserve(edges_pairs.size());

  for (const auto& edge : edges_pairs) {
    edges.push_back(Edge(edge.first, edge.second));
  }

  return Graph(edges);
}

Graph Graph::GraphWeighted(
    const std::vector<std::pair<size_t, size_t>>& edges_pairs,
    const std::vector<double>& weights) {
  std::vector<Edge> edges{};
  edges.reserve(edges_pairs.size());

  if (edges.size() != weights.size())
    raise std::invalid_argument(
        "Graph: the sizes of the edges and weights vectors do not match.");

  for (size_t i = 0; i < weights.size(); i++) {
    auto edge = Edge(edges_pairs[i].first, edges_pairs[i].second, weights[i]);
    edges.push_back(edge);
  }

  return Graph(edges);
}

Graph Graph::GraphFromAdjMatrix(
    const std::vector<std::vector<double>>& adj_matrix, bool is_weighted) {
  std::vector<Edge> edges{};

  if (adj_matrix.empty()) return Graph();

  if (adj_matrix.size() != adj_matrix[0].size())
    raise std::invalid_argument(
        "GraphFromAdjMatrix: AdjacencyMatrix is not squared.");

  for (size_t row = 0; row < adj_matrix.size(); row++) {
    if (row != 0)
      if (adj_matrix[row].size() != adj_matrix[row - 1].size())
        raise std::invalid_argument(
            "GraphFromAdjMatrix: AdjacencyMatrix is not squared [row "
            "problem].");

    for (size_t col = 0; col < adj_matrix[row].size(); col++) {
      if (adj_matrix[row][col] != 0)
        if (is_weighted)
          edges.push_back(Edge(col, row, adj_matrix[row][col]));
        else
          edges.push_back(Edge(col, row));
    }
  }

  return Graph(edges);
}

Graph Graph::GraphFromAdjList(
    const std::vector<std::vector<size_t>>& adj_list) {
  std::vector<Edge> edges{};

  for (size_t row = 0; row < adj_list.size(); row++)
    for (size_t col = 0; col < adj_list[row].size(); col++)
      edges.push_back(Edge(row, adj_list[row][col]));

  return Graph(edges);
}

Graph::Graph(const std::vector<Edge>& edges) : edges_{edges}, verts_() {
  // кол-во вершин = максимальная вершина среди ребер
  size_t max_vert = 0;
  for (const auto& edge : edges_) {
    max_vert = std::max(max_vert, edge.StartVert());
    max_vert = std::max(max_vert, edge.EndVert());
  }

  verts_.resize(max_vert + 1);
  std::iota(verts_.begin(), verts_.end(), 0);
}
