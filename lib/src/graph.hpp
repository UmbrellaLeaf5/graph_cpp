#include <unordered_set>

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

  static Graph GraphFromAdjMatrix(
      const std::vector<std::vector<weight_t>>& adj_matrix,
      bool is_weighted = false);

  static Graph GraphFromAdjList(
      const std::vector<std::vector<size_t>>& adj_list);

  bool IsWeighted() const;

  size_t VertsSize() const { return verts_.size(); }
  size_t EdgesSize() const { return edges_.size(); }

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
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);
