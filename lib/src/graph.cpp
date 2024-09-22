#include "graph.hpp"

std::ostream& operator<<(std::ostream& os, const Graph::Edge& edge) {
  os << edge.Name();
  return os;
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
  graph.PrintEdges(os);
  return os;
}

Graph::Edge::Edge(size_t start_vert, size_t end_vert, double weight)
    : start_vert_{start_vert}, end_vert_{end_vert}, weight_{weight} {
  if (weight <= 0)
    raise std::invalid_argument("Edge: weight must be greater than zero.");
}

double Graph::Edge::Weight() const {
  if (!IsWeighted())
    raise std::logic_error("Edge: " + Name() + " is not weighted.");

  return weight_;
}

auto Graph::Edge::operator<=>(const Edge& rhs) const {
  if (!(IsWeighted() && rhs.IsWeighted()))
    raise std::invalid_argument("Edge: unweighted edges are not comparable.");

  return weight_ <=> rhs.Weight();
}

const std::string& Graph::Edge::Name() const {
  static std::string name;

  if (IsWeighted())
    name = "[" + std::to_string(StartVert()) + " -> " +
           std::to_string(EndVert()) + ", w: " + std::to_string(Weight()) + "]";
  else
    name = "[" + std::to_string(StartVert()) + " -> " +
           std::to_string(EndVert()) + "]";

  return name;
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

bool Graph::IsWeighted() const {
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
  for (const auto& edge : edges_)
    if (edge != edges_[EdgesSize() - 1])
      os << edge << "; ";
    else
      os << edge;
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
        unique_edges.push_back(edges_[i]);
        break;
      }
  }

  edges_ = std::move(unique_edges);
  is_orient = false;
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

  if (!IsOrient()) Disorient();
}
