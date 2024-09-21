#include "util.hpp"

class Graph {
 public:
  Graph() : verts_(), edges_() {}

  static Graph GraphNonWeighted(
      const std::vector<std::pair<size_t, size_t>>& edges_pairs);

  static Graph GraphWeighted(
      const std::vector<std::pair<size_t, size_t>>& edges_pairs,
      const std::vector<double>& weights);

  static Graph GraphFromAdjMatrix(
      const std::vector<std::vector<double>>& adj_matrix,
      bool is_weighted = false);

  static Graph GraphFromAdjList(
      const std::vector<std::vector<size_t>>& adj_list);

 private:
  class Edge {
   public:
    Edge() = delete;

    Edge(size_t start_vert, size_t end_vert)
        : start_vert_{start_vert}, end_vert_{end_vert} {}

    Edge(size_t start_vert, size_t end_vert, double weight)
        : start_vert_{start_vert}, end_vert_{end_vert}, weight_{weight} {}

    bool IsWeighted() const { return weight_ != 0; }

    size_t StartVert() const { return start_vert_; }
    size_t EndVert() const { return end_vert_; }
    double Weight() const;

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

   private:
    size_t start_vert_;
    size_t end_vert_;
    double weight_ = 0;

    const std::string& Name() const;
  };

  std::vector<size_t> verts_;
  std::vector<Edge> edges_;

 public:
  friend std::ostream& operator<<(std::ostream& os, const Graph::Edge& edge);

 private:
  Graph(const std::vector<Edge>& edges);
};
