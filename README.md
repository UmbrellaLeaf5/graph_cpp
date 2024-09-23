# Graph_cpp: helper class for C++ with CMake support

## Description

In the second year of my MIPT DAFE/RSE education, as part of the Algorithms and Data Structures course in C++, we studied graph algorithms. For writing these, a separate Graph class was required.

At that moment, a crazy idea came to my mind: "What if I don't create a `Vertex` class, but create an `Edge` class and put it in the `private` field of the `Graph`?". And so I set out...

Over time, more and more such ideas emerged, and the lines of code grew at a doubled pace... And so this abnormal class was born, with eight static methods - pseudo-constructors, various auxiliary methods for deleting and searching for an edge or vertex, as well as templates for integer and string vertex types (more details - in the `examples` folder).

Since the project uses CMake, it is easy to integrate it into projects with the same build system - just clone the project into one folder:
```
git clone https://github.com/UmbrellaLeaf5/graph_cpp
```
or
```
git submodule add https://github.com/UmbrellaLeaf5/graph_cpp
```
and import the subdirectory:
```CMake
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/graph_cpp)
target_link_libraries(project_name PUBLIC graph_cpp)
```

## Examples

```C++
#include <iostream>

#include "graph/graph.hpp"

int main() {
  std::cout << std::endl
            << "------------------------------"
               "       Graph from pairs       "
               "------------------------------"
            << std::endl
            << std::endl;

  std::vector<std::pair<size_t, size_t>> edges_pairs = {{0, 1}, {1, 2}, {2, 0}};

  auto graph = Graph<size_t, long>::GraphNonWeighted(edges_pairs);

  std::cout << "Pairs: " << edges_pairs << std::endl
            << std::endl
            << graph << std::endl
            << std::endl;

  graph.PrintAdjList();

  return 0;
}
```
Output:
```
------------------------------       Graph from pairs       ------------------------------

Pairs: {{0; 1}; {1; 2}; {2; 0}}

Edges:
     {[0->1]; [1->2]; [2->0]}
Vertices:
     {0; 1; 2}

0: 1;
1: 2;
2: 0;

```