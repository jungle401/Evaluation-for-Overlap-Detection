#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cassert>
using namespace std;
namespace fs = filesystem;
class FastaRecord {
public:
  FastaRecord(string name) : name(name) {}
  string name;
  string seq;
  static vector<FastaRecord> get_records(
    const fs::path& file
  ) {
    auto res = vector<FastaRecord>{};
    auto fin = ifstream{file};
    if (!fin.is_open()) {
      cerr << "fin fail: " << file << endl;
      assert(false);
    }
    auto line = string{};
    getline(fin, line);
    res.push_back(FastaRecord(line.substr(1)));
    while (getline(fin, line)) {
      if (line[0] == '>') {
        res.push_back(FastaRecord(line.substr(1)));
      } else {
        res.back().seq += line;
      }
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const FastaRecord& obj) {
    os << ">" << obj.name << endl;
    os << obj.seq;
    return os;
  }
  friend ostream& operator<<(ostream& os, const vector<FastaRecord>& obj_vec) {
    for (const auto& obj : obj_vec) {
      os << obj << "\n";
    }
    return os;
  }
};
