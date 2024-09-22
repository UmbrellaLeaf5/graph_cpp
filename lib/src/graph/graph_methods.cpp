#include "../graph.hpp"

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
  os << "Edges:\n     ";
  graph.PrintEdges(os);

  os << "\n";

  os << "Vertices:\n     ";
  graph.PrintVerts(os);
  return os;
}

bool Graph::IsWeighted() const {
  if (edges_.empty()) return false;

  bool is_weighted = true;
  for (const auto& edge : edges_) is_weighted &= edge.IsWeighted();
  return is_weighted;
}

std::vector<std::tuple<size_t, size_t, weight_t>> Graph::Edges() {
  if (edges_.empty()) return {};

  std::vector<std::tuple<size_t, size_t, weight_t>> edges_tuples(edges_.size());
  std::transform(
      edges_.begin(), edges_.end(), edges_tuples.begin(), [](const Edge& edge) {
        return std::make_tuple(edge.StartVert(), edge.EndVert(), edge.Weight());
      });

  return edges_tuples;
}

std::ostream& Graph::PrintVerts(std::ostream& os) const {
  os << Verts();
  return os;
}

std::ostream& Graph::PrintEdges(std::ostream& os) const {
  os << edges_;
  return os;
}

void Graph::Disorient() {
  std::unordered_set<size_t> seen_edges;
  std::vector<Edge> unique_edges;
  unique_edges.reserve(EdgesAmount());

  for (size_t i = 0; i < EdgesAmount(); i++) {
    if (seen_edges.count(i) != 0) continue;

    for (size_t j = i + 1; j < EdgesAmount(); j++)
      if (edges_[i].StartVert() == edges_[j].EndVert() &&
          edges_[j].StartVert() == edges_[i].EndVert()) {
        seen_edges.insert(j);
        break;
      }

    unique_edges.push_back(edges_[i]);
  }

  edges_ = std::move(unique_edges);
  is_orient = false;
}

void Graph::RemoveDuplicates() {
  std::vector<Edge> unique_edges;
  unique_edges.reserve(EdgesAmount());

  for (const auto& edge : edges_)
    if (!Contains(unique_edges, edge)) unique_edges.push_back(edge);

  edges_ = std::move(unique_edges);
}

std::pair<size_t, size_t> Graph::ParseEdgeString(const std::string& edge_str) {
  size_t pos = edge_str.find("->");

  if (pos == std::string::npos)
    throw std::invalid_argument("EdgeString: invalid edge string format: " +
                                edge_str);

  try {
    size_t start_vert = std::stoul(edge_str.substr(0, pos));
    size_t end_vert = std::stoul(edge_str.substr(pos + 2));

    return {start_vert, end_vert};
  }

  except(...) {
    raise std::invalid_argument(
        "EdgeString: invalid edge string format "
        "(vertices should be numbers): " +
        edge_str);
  }
}