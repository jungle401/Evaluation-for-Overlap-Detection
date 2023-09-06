#pragma once

#include <iostream>
#include <vector>

namespace utils {

template<typename T>
void println(const std::vector<T>& v) {
  for (const auto& i : v) {
    std::cout << i;
  }
  std::cout << std::endl;
}

template<typename T>
void print(const std::vector<T>& v) {
  for (const auto& i : v) {
    std::cout << i << '\t';
  }
  std::cout << std::endl;
}

}
