#include "../../graph.hpp"

template class Graph<size_t, long>;

template <typename vert_t, typename weight_t>
bool Graph<vert_t, weight_t>::IsWeighted() const {
  if (edges_.empty()) return false;

  bool is_weighted = true;
  for (const auto& edge : edges_) is_weighted &= edge.IsWeighted();
  return is_weighted;
}

template <typename vert_t, typename weight_t>
std::vector<std::tuple<vert_t, vert_t, weight_t>>
Graph<vert_t, weight_t>::Edges() const {
  if (edges_.empty()) return {};

  std::vector<std::tuple<vert_t, vert_t, weight_t>> edges_tuples(edges_.size());
  std::transform(
      edges_.begin(), edges_.end(), edges_tuples.begin(), [](const Edge& edge) {
        return std::make_tuple(edge.StartVert(), edge.EndVert(), edge.Weight());
      });

  return edges_tuples;
}

template <typename vert_t, typename weight_t>
std::ostream& Graph<vert_t, weight_t>::PrintVerts(std::ostream& os) const {
  os << Verts();
  return os;
}

template <typename vert_t, typename weight_t>
std::ostream& Graph<vert_t, weight_t>::PrintEdges(std::ostream& os) const {
  os << edges_;
  return os;
}

template <typename vert_t, typename weight_t>
std::ostream& Graph<vert_t, weight_t>::PrintAdjList(std::ostream& os) const {
  for (const auto& vert : Verts()) {
    os << vert << ": ";

    for (const auto& neighbor : edges_) {
      if (neighbor.StartVert() == vert) os << neighbor.EndVert() << "; ";
      if (!IsDirected())
        if (neighbor.EndVert() == vert) os << neighbor.StartVert() << "; ";
    }

    os << "\n";
  }

  return os;
}

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::MakeUndirected(bool remove_duplicates) {
  std::unordered_set<vert_t> seen_edges;
  std::vector<Edge> unique_edges;
  unique_edges.reserve(EdgesAmount());

  for (vert_t i = 0; i < EdgesAmount(); i++) {
    if (seen_edges.count(i) != 0) continue;

    for (vert_t j = i + 1; j < EdgesAmount(); j++)
      if (edges_[i].StartVert() == edges_[j].EndVert() &&
          edges_[j].StartVert() == edges_[i].EndVert()) {
        seen_edges.insert(j);
        break;
      }

    unique_edges.push_back(edges_[i]);
  }

  edges_ = std::move(unique_edges);
  is_direct = false;
  if (remove_duplicates) RemoveDuplicates();
}

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::RemoveDuplicates() {
  std::vector<Edge> unique_edges;
  unique_edges.reserve(EdgesAmount());

  for (const auto& edge : edges_)
    if (!Contains(unique_edges, edge)) unique_edges.push_back(edge);

  edges_ = std::move(unique_edges);

  if (!IsDirected()) MakeUndirected();
}

template <typename vert_t, typename weight_t>
std::vector<std::vector<vert_t>> Graph<vert_t, weight_t>::GetAdjList() const {
  std::vector<std::vector<vert_t>> adj_list(
      *std::max_element(Verts().begin(), Verts().end()) + 1);

  for (const auto& edge : edges_) {
    adj_list[edge.StartVert()].push_back(edge.EndVert());
    if (!IsDirected()) adj_list[edge.EndVert()].push_back(edge.StartVert());
  }

  return adj_list;
}

template <typename vert_t, typename weight_t>
std::vector<std::vector<weight_t>> Graph<vert_t, weight_t>::GetAdjMatrix()
    const {
  std::vector<std::vector<weight_t>> adj_matrix(
      VertsAmount(), std::vector<weight_t>(VertsAmount(), 0));

  for (const auto& edge : edges_)
    if (edge.IsWeighted()) {
      adj_matrix[edge.StartVert()][edge.EndVert()] = edge.Weight();
      if (!IsDirected())
        adj_matrix[edge.EndVert()][edge.StartVert()] = edge.Weight();
    } else {
      adj_matrix[edge.StartVert()][edge.EndVert()] = 1;
      adj_matrix[edge.EndVert()][edge.StartVert()] = 1;
    }

  return adj_matrix;
}

template <typename vert_t, typename weight_t>
std::pair<vert_t, vert_t> Graph<vert_t, weight_t>::ParseEdgeString(
    const std::string& edge_str) {
  vert_t pos = edge_str.find("->");

  if (pos == std::string::npos)
    throw std::invalid_argument("EdgeString: invalid edge string format: " +
                                edge_str);

  try {
    vert_t start_vert = std::stoul(edge_str.substr(0, pos));
    vert_t end_vert = std::stoul(edge_str.substr(pos + 2));

    return {start_vert, end_vert};
  }

  except(...) {
    raise std::invalid_argument(
        "EdgeString: invalid edge string format "
        "(vertices should be numbers): " +
        edge_str);
  }
}

template <typename vert_t, typename weight_t>
bool Graph<vert_t, weight_t>::ContainsEdge(
    const std::tuple<vert_t, vert_t, weight_t>& edge) const {
  if (!IsWeighted())
    raise std::logic_error("ContainsEdge: graph is not weighted.");

  if (WeightFromTuple(edge) <= 0)
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

template <typename vert_t, typename weight_t>
bool Graph<vert_t, weight_t>::ContainsEdge(
    const std::pair<vert_t, vert_t>& edge) const {
  auto [start_vert, end_vert] = edge;

  auto it = std::find_if(
      edges_.begin(), edges_.end(), [start_vert, end_vert](const auto& e) {
        return e.StartVert() == start_vert && e.EndVert() == end_vert;
      });

  return it != edges_.end();
}

template <typename vert_t, typename weight_t>
weight_t Graph<vert_t, weight_t>::GetWeightOfEdge(
    const std::pair<vert_t, vert_t>& edge) const {
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

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::AddVert(vert_t vert) {
  if (!Contains(verts_, vert)) verts_.push_back(vert);
}

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::AddEdge(vert_t start_vert, vert_t end_vert,
                                      weight_t weight) {
  AddVert(start_vert);
  AddVert(end_vert);

  try {
    edges_.emplace_back(Edge(start_vert, end_vert, weight));
  }

  except(const std::exception& ex) {
    raise std::invalid_argument(std::string("AddEdge: ") + ex.what());
  }
}

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::AddEdge(vert_t start_vert, vert_t end_vert) {
  if (IsWeighted())
    raise std::logic_error(
        "AddEdge: weighted graph must consist of weighted edges.");

  AddVert(start_vert);
  AddVert(end_vert);

  edges_.emplace_back(Edge(start_vert, end_vert));
}

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::RemoveVert(vert_t vert) {
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

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::RemoveEdge(
    const std::pair<vert_t, vert_t>& edge_pair) {
  if (!ContainsEdge(edge_pair))
    throw std::invalid_argument("RemoveEdge: there is no such edge in graph: " +
                                Edge(edge_pair).Name());

  edges_.erase(
      std::remove_if(
          edges_.begin(), edges_.end(),
          [&edge_pair, this](const Edge& e) {
            if (IsDirected())
              return Edge(e.StartVert(), e.EndVert()) == Edge(edge_pair);

            return (Edge(e.StartVert(), e.EndVert()) == Edge(edge_pair)) ||
                   (Edge(e.EndVert(), e.StartVert()) == Edge(edge_pair));
          }),
      edges_.end());
}

template <typename vert_t, typename weight_t>
void Graph<vert_t, weight_t>::RemoveEdge(
    const std::tuple<vert_t, vert_t, weight_t>& edge_tuple) {
  if (!ContainsEdge(edge_tuple))
    throw std::invalid_argument("RemoveEdge: there is no such edge in graph: " +
                                Edge(edge_tuple).Name());

  edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                              [&edge_tuple, this](const Edge& e) {
                                if (IsDirected()) return e == Edge(edge_tuple);

                                return (e == Edge(edge_tuple)) ||
                                       (e == Edge(std::make_tuple(
                                                 EndVertFromTuple(edge_tuple),
                                                 StartVertFromTuple(edge_tuple),
                                                 WeightFromTuple(edge_tuple))));
                              }),
               edges_.end());
}