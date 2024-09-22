#pragma once

// std libs:
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <variant>

#include "util.hpp"

using weight_t = long;

class Graph {
 public:
  Graph() : verts_(), edges_() {}

  static Graph GraphNonWeighted(
      const std::vector<std::pair<size_t, size_t>>& edges_pairs);

  static Graph GraphWeighted(
      const std::vector<std::pair<size_t, size_t>>& edges_pairs,
      const std::vector<weight_t>& weights);

  static Graph GraphWeighted(
      const std::vector<std::tuple<size_t, size_t, weight_t>>& edges_tuples);

  static Graph GraphFromMap(
      const std::unordered_map<std::string, weight_t>& edges_dict);

  static Graph GraphFromStrs(const std::vector<std::string>& edges_strs);

  static Graph GraphFromAdjMatrix(
      const std::vector<std::vector<weight_t>>& adj_matrix,
      bool is_weighted = false);

  static Graph GraphFromAdjList(
      const std::vector<std::vector<size_t>>& adj_list);

  bool IsWeighted() const;

  size_t VertsAmount() const { return verts_.size(); }
  size_t EdgesAmount() const { return edges_.size(); }

  const std::vector<size_t>& Verts() const { return verts_; }
  std::vector<std::tuple<size_t, size_t, weight_t>> Edges();

  std::ostream& PrintVerts(std::ostream& os = std::cout) const;
  std::ostream& PrintEdges(std::ostream& os = std::cout) const;

  void Disorient();
  void Orient() { is_orient = true; }
  bool IsOrient() const { return is_orient; }

  void RemoveDuplicates();

 private:
  class Edge {
   public:
    Edge() = delete;

    Edge(size_t start_vert, size_t end_vert)
        : start_vert_{start_vert}, end_vert_{end_vert} {}

    Edge(size_t start_vert, size_t end_vert, weight_t weight);

    bool IsWeighted() const { return weight_ != 0; }

    size_t StartVert() const { return start_vert_; }
    size_t EndVert() const { return end_vert_; }
    weight_t Weight() const;

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

    bool operator==(const Edge& rhs) const {
      return start_vert_ == rhs.start_vert_ && end_vert_ == rhs.end_vert_ &&
             weight_ == rhs.weight_;
    }

    bool operator!=(const Edge& rhs) const { return !(*this == rhs); }

    auto operator<=>(const Edge& rhs) const;

   private:
    size_t start_vert_;
    size_t end_vert_;
    weight_t weight_ = 0;

    const std::string& Name() const;
  };

  std::vector<size_t> verts_;
  std::vector<Edge> edges_;

  bool is_orient = true;

 public:
  friend std::ostream& operator<<(std::ostream& os, const Graph::Edge& edge);

 private:
  Graph(const std::vector<Edge>& edges);

  static std::pair<size_t, size_t> ParseEdgeString(const std::string& edge_str);
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

inline size_t StartVert(const std::tuple<size_t, size_t, weight_t>& edge) {
  return std::get<0>(edge);
}

inline size_t EndVert(const std::tuple<size_t, size_t, weight_t>& edge) {
  return std::get<1>(edge);
}

inline weight_t Weight(const std::tuple<size_t, size_t, weight_t>& edge) {
  return std::get<2>(edge);
}
