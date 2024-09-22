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

std::vector<std::tuple<size_t, size_t, weight_t>> Graph::Edges() const {
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

std::ostream& Graph::PrintAdjList(std::ostream& os) const {
  for (const auto& vert : Verts()) {
    os << vert << ": ";

    for (const auto& neighbor : edges_) {
      if (neighbor.StartVert() == vert) os << neighbor.EndVert() << "; ";
      if (!IsOrient())
        if (neighbor.EndVert() == vert) os << neighbor.StartVert() << "; ";
    }

    os << "\n";
  }

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

std::vector<std::vector<size_t>> Graph::GetAdjList() const {
  std::vector<std::vector<size_t>> adj_list(
      *std::max_element(Verts().begin(), Verts().end()) + 1);

  for (const auto& edge : edges_) {
    adj_list[edge.StartVert()].push_back(edge.EndVert());
    if (!IsOrient()) adj_list[edge.EndVert()].push_back(edge.StartVert());
  }

  return adj_list;
}

std::vector<std::vector<weight_t>> Graph::GetAdjMatrix() const {
  std::vector<std::vector<weight_t>> adj_matrix(
      VertsAmount(), std::vector<weight_t>(VertsAmount(), 0));

  for (const auto& edge : edges_)
    if (edge.IsWeighted()) {
      adj_matrix[edge.StartVert()][edge.EndVert()] = edge.Weight();
      if (!IsOrient())
        adj_matrix[edge.EndVert()][edge.StartVert()] = edge.Weight();
    } else {
      adj_matrix[edge.StartVert()][edge.EndVert()] = 1;
      adj_matrix[edge.EndVert()][edge.StartVert()] = 1;
    }

  return adj_matrix;
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

bool Graph::ContainsEdge(
    const std::tuple<size_t, size_t, weight_t>& edge) const {
  if (!IsWeighted())
    raise std::logic_error("ContainsEdge: graph is not weighted.");

  if (WeightFromTuple(edge) < 0)
    raise std::logic_error("ContainsEdge: weight must be greater than zero.");

  auto [start_vert, end_vert, weight] = edge;

  auto it = std::find_if(edges_.begin(), edges_.end(),
                         [start_vert, end_vert, weight](const auto& e) {
                           return e.StartVert() == start_vert &&
                                  e.EndVert() == end_vert &&
                                  e.Weight() == weight;
                         });

  return it != edges_.end();
}

bool Graph::ContainsEdge(const std::pair<size_t, size_t>& edge) const {
  auto [start_vert, end_vert] = edge;

  auto it = std::find_if(
      edges_.begin(), edges_.end(), [start_vert, end_vert](const auto& e) {
        return e.StartVert() == start_vert && e.EndVert() == end_vert;
      });

  return it != edges_.end();
}

weight_t Graph::GetWeightOfEdge(const std::pair<size_t, size_t>& edge) const {
  if (!IsWeighted())
    throw std::logic_error("GetWeightOfEdge: graph is not weighted.");

  if (!ContainsEdge(edge))
    raise std::invalid_argument("GetWeightOfEdge: there is no edge: " +
                                Edge(edge).Name());

  auto [start_vert, end_vert] = edge;

  auto it = std::find_if(
      edges_.begin(), edges_.end(), [start_vert, end_vert](const auto& e) {
        return e.StartVert() == start_vert && e.EndVert() == end_vert;
      });

  return it->Weight();
}

void Graph::AddVert(size_t vert) {
  if (!Contains(verts_, vert)) verts_.push_back(vert);
}

void Graph::AddEdge(size_t start_vert, size_t end_vert, weight_t weight) {
  AddVert(start_vert);
  AddVert(end_vert);

  try {
    edges_.emplace_back(Edge(start_vert, end_vert, weight));
  }

  except(const std::exception& ex) {
    raise std::invalid_argument(std::string("AddEdge: ") + ex.what());
  }
}

void Graph::AddEdge(size_t start_vert, size_t end_vert) {
  if (IsWeighted())
    raise std::logic_error(
        "AddEdge: weighted graph must consist of weighted edges.");

  AddVert(start_vert);
  AddVert(end_vert);

  edges_.emplace_back(Edge(start_vert, end_vert));
}

void Graph::RemoveVert(size_t vert) {
  if (!Contains(Verts(), vert))
    raise std::invalid_argument("RemoveVert: there is no such vert in graph: " +
                                std::to_string(vert));

  verts_.erase(std::remove(verts_.begin(), verts_.end(), vert), verts_.end());

  edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                              [vert](const Edge& edge) {
                                return edge.StartVert() == vert ||
                                       edge.EndVert() == vert;
                              }),
               edges_.end());
}

void Graph::RemoveEdge(const std::pair<size_t, size_t>& edge_pair) {
  if (!ContainsEdge(edge_pair)) {
    throw std::invalid_argument("RemoveEdge: there is no such edge in graph: " +
                                Edge(edge_pair).Name());
  }

  edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                              [&edge_pair](const Edge& e) {
                                return Edge(e.StartVert(), e.EndVert()) ==
                                       Edge(edge_pair);
                              }),
               edges_.end());
}

void Graph::RemoveEdge(const std::tuple<size_t, size_t, weight_t>& edge_tuple) {
  if (!ContainsEdge(edge_tuple)) {
    throw std::invalid_argument("RemoveEdge: there is no such edge in graph: " +
                                Edge(edge_tuple).Name());
  }

  edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                              [&edge_tuple](const Edge& e) {
                                return e == Edge(edge_tuple);
                              }),
               edges_.end());
}