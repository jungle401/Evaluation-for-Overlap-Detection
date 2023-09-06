#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = filesystem;

class MhpRecord {
public:
  int r1;
  int r2;
  char r1_strand;
  int r1_start;
  int r1_end;
  char r2_strand;
  int r2_start;
  int r2_end;
  static vector<MhpRecord> get_records(
    const fs::path& file
  ) {
    auto res = vector<MhpRecord>();
    auto fin = ifstream{file};
    auto line = string();
    while (getline(fin, line)) {
      auto ss = stringstream{line};
      auto mhp_record = MhpRecord();
      ss >> mhp_record.r1;
      ss >> mhp_record.r2;
      for (int i = 0; i < 2; i++) { ss >> line; }
      ss >> mhp_record.r1_strand;
      ss >> mhp_record.r1_start;
      ss >> mhp_record.r1_end;
      ss >> line;
      ss >> mhp_record.r2_strand;
      ss >> mhp_record.r2_start;
      ss >> mhp_record.r2_end;
      assert(mhp_record.r1_start <= mhp_record.r1_end);
      assert(mhp_record.r2_start <= mhp_record.r2_end);
      res.emplace_back(std::move(mhp_record));
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const MhpRecord& obj) {
    os << obj.r1 << '\t';
    os << obj.r2 << '\t';
    os << obj.r1_start << '\t';
    os << obj.r1_end << '\t';
    os << obj.r2_start << '\t';
    os << obj.r2_end << '\n';
    return os;
  }
};
