#include "../graph.hpp"

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
  graph.PrintEdges(os);
  return os;
}

bool Graph::IsWeighted() const {
  if (edges_.empty()) return false;

  bool is_weighted = true;
  for (const auto& edge : edges_) is_weighted &= edge.IsWeighted();
  return is_weighted;
}

std::ostream& Graph::PrintVerts(std::ostream& os) const {
  os << "{";
  for (const auto& vert : verts_)
    if (vert != verts_[verts_.size() - 1])
      os << vert << ", ";
    else
      os << vert;
  os << "}" << std::endl;
  return os;
}

std::ostream& Graph::PrintEdges(std::ostream& os) const {
  os << "{";
  for (size_t i = 0; i < edges_.size(); i++) {
    auto edge = edges_[i];
    if (i != EdgesSize() - 1)
      os << edge << "; ";
    else
      os << edge;
  }
  os << "}" << std::endl;
  return os;
}

void Graph::Disorient() {
  std::unordered_set<size_t> seen_edges;
  std::vector<Edge> unique_edges;
  unique_edges.reserve(EdgesSize());

  for (size_t i = 0; i < EdgesSize(); i++) {
    if (seen_edges.count(i) != 0) continue;

    for (size_t j = i + 1; j < EdgesSize(); j++)
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
  unique_edges.reserve(EdgesSize());

  for (const auto& edge : edges_)
    if (!Contains(unique_edges, edge)) unique_edges.push_back(edge);

  edges_ = std::move(unique_edges);
}