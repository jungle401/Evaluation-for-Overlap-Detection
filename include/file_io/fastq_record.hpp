#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cassert>
using namespace std;
namespace fs = filesystem;
/**
  * @brief Only accommodate with non-multi-lines fastq file.
  */
class FastqRecord {
public:
  string name;
  string seq;
  string qual;
  static vector<FastqRecord> get_records(
    const fs::path& file
  ) {
    auto res = vector<FastqRecord>{};
    auto fin = ifstream{file};
    if (!fin.is_open()) {
      cerr << "fin fail: " << file << endl;
      assert(false);
    }
    auto line = string{};
    while (getline(fin, line)) {
      auto fastq_record = FastqRecord();
      fastq_record.name = line.substr(1);
      getline(fin, line);
      fastq_record.seq = line;
      getline(fin, line);
      getline(fin, line);
      fastq_record.qual = line;
      res.emplace_back(std::move(fastq_record));
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const FastqRecord& obj) {
    os << "@" << obj.name << "\n";
    os << obj.seq << "\n";
    os << "+" << "\n";
    os << obj.qual << "\n";
    return os;
  }
  friend ostream& operator<<(ostream& os, const vector<FastqRecord>& obj_vec) {
    for (const auto& obj : obj_vec) {
      os << obj;
    }
    return os;
  }
};
