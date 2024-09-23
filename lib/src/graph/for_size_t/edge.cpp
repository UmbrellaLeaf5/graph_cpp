#include "../../graph.hpp"

template class Graph<size_t, long>;

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t>::Edge::Edge(vert_t start_vert, vert_t end_vert,
                                    weight_t weight)
    : start_vert_{start_vert}, end_vert_{end_vert}, weight_{weight} {
  if (weight <= 0)
    raise std::invalid_argument("Edge: weight must be greater than zero.");
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t>::Edge::Edge(std::pair<vert_t, vert_t> edge_pair)
    : start_vert_{edge_pair.first}, end_vert_{edge_pair.second} {}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t>::Edge::Edge(
    std::tuple<vert_t, vert_t, weight_t> edge_tuple)
    : start_vert_{StartVertFromTuple(edge_tuple)},
      end_vert_{EndVertFromTuple(edge_tuple)},
      weight_{WeightFromTuple(edge_tuple)} {}

template <typename vert_t, typename weight_t>
weight_t Graph<vert_t, weight_t>::Edge::Weight() const {
  if (!IsWeighted())
    raise std::logic_error("Edge: " + Name() + " is not weighted.");

  return weight_;
}

template <typename vert_t, typename weight_t>
auto Graph<vert_t, weight_t>::Edge::operator<=>(const Edge& rhs) const {
  if (!(IsWeighted() && rhs.IsWeighted()))
    raise std::invalid_argument("Edge: unweighted edges are not comparable.");

  return weight_ <=> rhs.Weight();
}

template <typename vert_t, typename weight_t>
const std::string& Graph<vert_t, weight_t>::Edge::Name() const {
  static std::string name;

  if (IsWeighted())
    name = "[" + std::to_string(StartVert()) + "->" +
           std::to_string(EndVert()) + ", w: " + std::to_string(Weight()) + "]";
  else
    name = "[" + std::to_string(StartVert()) + "->" +
           std::to_string(EndVert()) + "]";

  return name;
}