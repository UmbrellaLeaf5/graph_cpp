#include <iostream>

#include "graph/graph.hpp"

int main() {
  // ------------------- Graph from pairs and weights -------------------

  std::cout << "------------------------------"
               " Graph from pairs and weights "
               "------------------------------"
            << std::endl
            << std::endl;

  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};
  std::vector<long> weights = {1, 2, 3};

  std::cout << "Pairs: " << edges_pairs << std::endl
            << "Weights: " << weights << std::endl
            << std::endl
            << Graph<size_t, long>::GraphWeighted(edges_pairs, weights)
            << std::endl;

  // --------------------------------------------------------------------

  return 0;
}
