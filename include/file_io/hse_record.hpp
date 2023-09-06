#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = filesystem;

class HseRecord {
public:
  int r1;
  int r2;
  int r1_start;
  int r1_end;
  int r1_size;
  char strand;
  int r2_start;
  int r2_end;
  int r2_size;
  static vector<HseRecord> get_records(
    const fs::path& file
  ) {
    auto res = vector<HseRecord>();
    auto fin = ifstream{file};
    auto line = string();
    while (getline(fin, line)) {
      auto ss = stringstream{line};
      auto hse_record = HseRecord();
      ss >> hse_record.r1;
      ss >> hse_record.r2;
      for (int i = 0; i < 3; i++) { ss >> line; }
      ss >> hse_record.r1_start;
      ss >> hse_record.r1_end;
      ss >> hse_record.r1_size;
      ss >> hse_record.strand;
      ss >> hse_record.r2_start;
      ss >> hse_record.r2_end;
      ss >> hse_record.r2_size;
      if (hse_record.r1_start > hse_record.r1_end) {
        cout << hse_record << endl;
        continue;
      }
      if (hse_record.r2_start > hse_record.r2_end) {
        cout << hse_record << endl;
        continue;
      }
      // assert(hse_record.r1_start <= hse_record.r1_end);
      // assert(hse_record.r2_start <= hse_record.r2_end);
      res.emplace_back(std::move(hse_record));
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const HseRecord& obj) {
    os << obj.r1 << '\t';
    os << obj.r2 << '\t';
    for (int i = 0; i < 3; i++) { os << "0 "; }
    os << obj.r1_start << '\t';
    os << obj.r1_end << '\t';
    os << obj.r1_size << '\t';
    os << obj.strand << '\t';
    os << obj.r2_start << '\t';
    os << obj.r2_end << '\t';
    os << obj.r2_size << '\n';
    return os;
  }
};
