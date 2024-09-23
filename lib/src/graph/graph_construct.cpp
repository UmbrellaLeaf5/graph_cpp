#include "../graph.hpp"

template class Graph<size_t, long>;
template class Graph<std::string, long>;

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphNonWeighted(
    const std::vector<std::pair<vert_t, vert_t>>& edges_pairs) {
  if (edges_pairs.empty()) return Graph();

  std::vector<Edge> edges{};
  edges.reserve(edges_pairs.size());

  for (const auto& edge : edges_pairs) {
    edges.push_back(Edge(edge.first, edge.second));
  }

  return Graph(edges);
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphWeighted(
    const std::vector<std::pair<vert_t, vert_t>>& edges_pairs,
    const std::vector<weight_t>& weights) {
  if (edges_pairs.empty() && weights.empty()) return Graph();

  std::vector<Edge> edges{};
  edges.reserve(edges_pairs.size());

  if (edges_pairs.size() != weights.size())
    raise std::invalid_argument(
        "GraphWeighted: the sizes of the edges and weights vectors do not "
        "match.");

  for (size_t i = 0; i < weights.size(); i++) {
    auto edge = Edge(edges_pairs[i].first, edges_pairs[i].second, weights[i]);
    edges.push_back(edge);
  }

  return Graph(edges);
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphWeighted(
    const std::vector<std::tuple<vert_t, vert_t, weight_t>>& edges_tuples) {
  if (edges_tuples.empty()) return Graph();

  std::vector<Edge> edges;

  for (const auto& [start, end, weight] : edges_tuples)
    edges.emplace_back(start, end, weight);

  return Graph(edges);
}
