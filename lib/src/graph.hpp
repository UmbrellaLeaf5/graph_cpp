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
  /// @brief Инициализирует новый экземпляр Graph
  Graph() : edges_(), verts_() {}

  /**
   * @brief Создает новый экземпляр Graph по ребрам,
   * представленными вектором std::pair (НЕВЗВЕШЕННЫЙ)
   * @param edges_pairs: ребра графа
   * @return Graph: новый экземпляр Graph
   */
  static Graph GraphNonWeighted(
      const std::vector<std::pair<size_t, size_t>>& edges_pairs);

  /**
   * @brief Создает новый экземпляр Graph по ребрам,
   * представленными вектором std::pair и weight_t (ВЗВЕШЕННЫЙ)
   * @param edges_pairs: ребра графа
   * @param weights: веса ребер
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2},
   *                                                       {2, 0}};
   * std::vector<long> weights = {1, 2, 3};
   * Graph graph = Graph::GraphWeighted(edges_pairs, weights);
   */
  static Graph GraphWeighted(
      const std::vector<std::pair<size_t, size_t>>& edges_pairs,
      const std::vector<weight_t>& weights);

  /**
   * @brief Создает новый экземпляр Graph по ребрам
   * представленными вектором std::tuple (ВЗВЕШЕННЫЙ)
   * @param edges_tuples: ребра графа
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::tuple<size_t, size_t, weight_t>> input = {
   *   {0, 1, 5}, {1, 2, 10}, {2, 0, 3}};
   * Graph graph = Graph::GraphWeighted(input);
   */
  static Graph GraphWeighted(
      const std::vector<std::tuple<size_t, size_t, weight_t>>& edges_tuples);

  /**
   * @brief Создает новый экземпляр Graph по ребрам
   * представленными вектором std::string (НЕВЗВЕШЕННЫЙ)
   * @param edges_strs: ребра графа
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::string> edges_strs = {"0->1", "2->1", "3->2", "1->3"};
   * Graph graph = Graph::GraphFromStrs(edges_strs);
   */
  static Graph GraphFromStrs(const std::vector<std::string>& edges_strs);

  /**
   * @brief Создает новый экземпляр Graph по ребрам
   * представленными словарем из std::string и weight_t (ВЗВЕШЕННЫЙ)
   * @param edges_dict: ребра графа
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::unordered_map<std::string, weight_t> edges_dict = {
   *     {"0->1", 5}, {"2->1", 1}, {"3->2", 2}, {"1->3", 3}};
   * Graph graph = Graph::GraphFromMap(edges_dict);
   */
  static Graph GraphFromMap(
      const std::unordered_map<std::string, weight_t>& edges_dict);

  /**
   * @brief Создает новый экземпляр Graph по матрице смежности
   * @param adj_matrix: матрица смежности
   * @param is_weighted: взвешен ли граф
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::vector<long>> adj_matrix = {{0, 1, 0},
   *                                              {1, 0, 1},
   *                                              {0, 1, 0}};
   * Graph graph = Graph::GraphFromAdjMatrix(adj_matrix);
   *
   * std::vector<std::vector<long>> adj_matrix_2 = {{0, 1, 0},
   *                                                {1, 0, 5},
   *                                                {0, 7, 0}};
   * Graph graph_2 = Graph::GraphFromAdjMatrix(adj_matrix_2, true);
   */
  static Graph GraphFromAdjMatrix(
      const std::vector<std::vector<weight_t>>& adj_matrix,
      bool is_weighted = false);

  /**
   * @brief Создает новый экземпляр Graph
   * по списку смежности (НЕВЗВЕШЕННЫЙ)
   * @param adj_list: список смежности
   * @return Graph: новый экземпляр Graph
   *
   * @example code:
   * std::vector<std::vector<size_t>> adj_list = {{1},
   *                                              {0, 2},
   *                                              {1}};
   * Graph graph = Graph::GraphFromAdjList(adj_list);
   */
  static Graph GraphFromAdjList(
      const std::vector<std::vector<size_t>>& adj_list);

  /// @brief Проверяет, взвешен ли граф
  bool IsWeighted() const;

  /// @return size_t: кол-во вершин
  size_t VertsAmount() const { return verts_.size(); }

  /// @return size_t: кол-во ребер
  size_t EdgesAmount() const { return edges_.size(); }

  /// @return const std::vector<size_t>&: вершины
  const std::vector<size_t>& Verts() const { return verts_; }

  /// @return std::vector<std::tuple<size_t, size_t, weight_t>>: ребра
  std::vector<std::tuple<size_t, size_t, weight_t>> Edges() const;

  /**
   * @brief Выводит в поток список вершин
   * @param os: входной поток
   * @return std::ostream&: выходной поток
   */
  std::ostream& PrintVerts(std::ostream& os = std::cout) const;

  /**
   * @brief Выводит в поток список ребер
   * @param os: входной поток
   * @return std::ostream&: выходной поток
   */
  std::ostream& PrintEdges(std::ostream& os = std::cout) const;

  /**
   * @brief Выводит в поток список смежности
   * @param os: входной поток
   * @return std::ostream&: выходной поток
   */
  std::ostream& PrintAdjList(std::ostream& os = std::cout) const;

  /**
   * @brief Делает граф ненаправленным (удаляет лишние ребра)
   * @param remove_duplicates: удалять ли дубликаты
   */
  void MakeUndirected(bool remove_duplicates = false);

  /// @brief Делает граф направленным (ничего)
  void MakeDirected() { is_direct = true; }

  /// @brief Проверяет, направлен ли граф
  bool IsDirected() const { return is_direct; }

  /// @brief Удаляет из графа ребрами с одинаковым вершинами
  void RemoveDuplicates();

  /// @return std::vector<std::vector<size_t>>: список смежности
  std::vector<std::vector<size_t>> GetAdjList() const;

  /// @return std::vector<std::vector<size_t>>: матрица смежности
  std::vector<std::vector<weight_t>> GetAdjMatrix() const;

  /**
   * @brief Проверяет, содержится ли ребро в графе (ВЗВЕШЕННЫЙ)
   * @param edge: ребро
   * @return true: содержится
   * @return false: не содержится
   */
  bool ContainsEdge(const std::tuple<size_t, size_t, weight_t>& edge) const;

  /**
   * @brief Проверяет, содержится ли ребро в графе (НЕВЗВЕШЕННЫЙ)
   * @param edge: ребро
   * @return true: содержится
   * @return false: не содержится
   */
  bool ContainsEdge(const std::pair<size_t, size_t>& edge) const;

  /**
   * @brief Находит вес ребра в взвешенном графе
   * @param edge: ребро
   * @return weight_t: вес
   */
  weight_t GetWeightOfEdge(const std::pair<size_t, size_t>& edge) const;

  void AddVert(size_t vert);
  void AddEdge(size_t start_vert, size_t end_vert, weight_t weight);
  void AddEdge(size_t start_vert, size_t end_vert);

  void RemoveVert(size_t vert);
  void RemoveEdge(const std::pair<size_t, size_t>& edge_pair);
  void RemoveEdge(const std::tuple<size_t, size_t, weight_t>& edge_tuple);

 private:
  class Edge {
   public:
    Edge() = delete;

    Edge(size_t start_vert, size_t end_vert)
        : start_vert_{start_vert}, end_vert_{end_vert} {}

    Edge(size_t start_vert, size_t end_vert, weight_t weight);

    Edge(std::pair<size_t, size_t> edge_pair);
    Edge(std::tuple<size_t, size_t, weight_t> edge_tuple);

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

    const std::string& Name() const;

   private:
    size_t start_vert_;
    size_t end_vert_;
    weight_t weight_ = 0;
  };

  std::vector<Edge> edges_;
  std::vector<size_t> verts_;

  bool is_direct = true;

 public:
  friend std::ostream& operator<<(std::ostream& os, const Graph::Edge& edge);

 private:
  Graph(const std::vector<Edge>& edges);

  static std::pair<size_t, size_t> ParseEdgeString(const std::string& edge_str);
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

inline size_t StartVertFromTuple(
    const std::tuple<size_t, size_t, weight_t>& edge) {
  return std::get<0>(edge);
}

inline size_t EndVertFromTuple(
    const std::tuple<size_t, size_t, weight_t>& edge) {
  return std::get<1>(edge);
}

inline weight_t WeightFromTuple(
    const std::tuple<size_t, size_t, weight_t>& edge) {
  return std::get<2>(edge);
}
