#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = filesystem;

class OvlRecord {
public:
  int r1;
  int r2;
  int r1_start;
  int r1_end;
  int r2_start;
  int r2_end;
  static vector<OvlRecord> get_ovl_records(
    const fs::path& file
  ) {
    auto res = vector<OvlRecord>();
    auto fin = ifstream{file};
    auto line = string();
    while (getline(fin, line)) {
      auto ss = stringstream{line};
      auto ovl_record = OvlRecord();
      ss >> ovl_record.r1;
      ss >> ovl_record.r2;
      ss >> ovl_record.r1_start;
      ss >> ovl_record.r1_end;
      ss >> ovl_record.r2_start;
      ss >> ovl_record.r2_end;
      assert(ovl_record.r1_start <= ovl_record.r1_end);
      assert(ovl_record.r2_start <= ovl_record.r2_end);
      res.emplace_back(std::move(ovl_record));
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const OvlRecord& obj) {
    os << obj.r1 << '\t';
    os << obj.r2 << '\t';
    os << obj.r1_start << '\t';
    os << obj.r1_end << '\t';
    os << obj.r2_start << '\t';
    os << obj.r2_end << '\n';
    return os;
  }
};
