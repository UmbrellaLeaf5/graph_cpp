#include "../../graph.hpp"

template class Graph<size_t, long>;

template <typename vert_t, typename weight_t>
const std::string& Graph<vert_t, weight_t>::Edge::Name() const {
  static std::string name;

  if (IsWeighted())
    name = "[" + std::to_string(StartVert()) + "->" +
           std::to_string(EndVert()) + ", w: " + std::to_string(Weight()) + "]";
  else
    name = "[" + std::to_string(StartVert()) + "->" +
           std::to_string(EndVert()) + "]";

  // example: "[4->5]"

  return name;
}