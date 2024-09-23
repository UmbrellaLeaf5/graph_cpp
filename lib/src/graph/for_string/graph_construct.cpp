#include "../../graph.hpp"

template class Graph<std::string, long>;

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t>::Graph(const std::vector<Edge>& edges)
    : edges_{edges}, verts_() {
  if (edges.empty()) return;

  for (const auto& edge : edges_) {
    if (!Contains(Verts(), edge.StartVert()))
      verts_.push_back(edge.StartVert());

    if (!Contains(Verts(), edge.EndVert())) verts_.push_back(edge.EndVert());
  }

  if (!IsDirected()) MakeUndirected();
}