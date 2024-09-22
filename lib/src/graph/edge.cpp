#include "../graph.hpp"

std::ostream& operator<<(std::ostream& os, const Graph::Edge& edge) {
  os << edge.Name();
  return os;
}

Graph::Edge::Edge(size_t start_vert, size_t end_vert, weight_t weight)
    : start_vert_{start_vert}, end_vert_{end_vert}, weight_{weight} {
  if (weight <= 0)
    raise std::invalid_argument("Edge: weight must be greater than zero.");
}

weight_t Graph::Edge::Weight() const {
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
    name = "[" + std::to_string(StartVert()) + "->" +
           std::to_string(EndVert()) + ", w: " + std::to_string(Weight()) + "]";
  else
    name = "[" + std::to_string(StartVert()) + "->" +
           std::to_string(EndVert()) + "]";

  return name;
}