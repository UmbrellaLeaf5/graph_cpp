#pragma once

// std libs:
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// clang-format off

#define pass {}
#define raise throw
#define except catch

using std::size_t;
// clang-format on

/**
 * @brief перегрузка, которая выводит все элементы вектора в поток
 * @tparam Type: тип, возможный к выводу в консоль
 * @param os: ссылка на поток, в который надо вывести (мод.)
 * @param vec: вектор элементов произвольного типа
 * @return std::ostream&: ссылка на поток, в который вывели
 */
template <typename Type>
inline std::ostream& operator<<(std::ostream& os,
                                const std::vector<Type>& vec) {
  os << "{";
  for (std::size_t i = 0; i < vec.size(); i++) {
    os << vec[i];
    if (i != vec.size() - 1) os << "; ";
  }
  return os << "}";
}

/**
 * @brief функция, которая обрезает незнач. нули float при преобр. в строку
 * @param number: число типа float
 * @return std::string: итоговое число, записанное в строку
 */
std::string ErasedZerosStr(float number);

/**
 * @brief перегрузка, которая выводит элементы пары в поток (в формате суммы)
 * @tparam Type: тип, возможный к выводу в консоль
 * @param os: ссылка на поток, в который надо вывести (мод.)
 * @param par: пара элементов типа Type
 * @return std::ostream&: ссылка на поток, в который вывели
 */
template <typename Type>
inline std::ostream& operator<<(std::ostream& os,
                                const std::pair<Type, Type>& par) {
  return os << par.first << " " << par.second;
}

/**
 * @brief перегрузка, которая вводит все элементы вектора из потока
 * (работает исключительно с консолью, так как
 * (вывод о текущем состоянии происходит туда)
 * @tparam Type: тип, возможный к выводу в консоль
 * @param is: ссылка на поток, из которого надо ввести (мод.)
 * @param vec: вектор элементов типа Type (мод.)
 * @return std::istream&: ссылка на поток, из которого ввели
 */
template <typename Type>
inline std::istream& operator>>(std::istream& is, std::vector<Type>& vec) {
  // @brief размер вектора
  long size = 0;

  std::cout << "Enter array size: ";
  while (size <= 0) {
    is >> size;
    if (!is) {
      std::cerr << "Invalid size input." << std::endl;
      return is;
    }
    if (size <= 0) std::cout << "Invalid size input. Try again: ";
  }

  // @brief текущий элемент
  Type curr;

  vec.clear();  // (для перезаписи нужна отчистка)
  std::cout << "Enter array elements: ";
  for (std::size_t i = 0; i < std::size_t(size); i++) {
    is >> curr;
    if (!is) {
      std::cerr << "Invalid array input. The entry is incorrect." << std::endl;
      return is;
    }
    vec.push_back(curr);
  }

  return is;
}

/**
 * @brief Проверяет наличие элемента в векторе
 * @tparam T: тип элемента
 * @param vec: исходный вектор
 * @param value: искомое значение
 * @return true: элемент найден
 * @return false: элемент не найден
 */
template <typename T>
bool Contains(const std::vector<T>& vec, const T& value) {
  auto it = std::find(vec.begin(), vec.end(), value);
  return it != vec.end();
}