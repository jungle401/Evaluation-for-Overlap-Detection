#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
class ReadPairLogger {
  public:
  // read pairs logger
  std::ofstream fout;
  ReadPairLogger(const std::filesystem::path& file) {
    fout = std::ofstream(file);
    assert(fout.is_open());
  }

};
