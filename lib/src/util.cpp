#include "util.hpp"

std::string ErasedZerosStr(float number) {
  std::string str = std::to_string(number);

  // удаляем незначащие нули
  str.erase(str.find_last_not_of('0') + 1, std::string::npos);

  // если последний символ - десятичная точка, удаляем
  if (str.back() == '.') str.pop_back();

  return str;
}