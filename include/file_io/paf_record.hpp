#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

class PafRecord {
public:
  std::string qry_name;
  int qry_len;
  int qry_start;
  int qry_end;
  char relative_strand;
  std::string tar_name;
  int tar_len;
  int tar_start;
  int tar_end;
  int num_match_residue;
  int len_alignment_block;
  int map_qual;

  static std::vector<PafRecord> get_records(
    const std::filesystem::path& file
  ) {
    auto res = std::vector<PafRecord>();
    auto fin = std::ifstream{file};
    if (!fin.is_open()) {
      std::cerr << "fin fail: " << file << std::endl;
      exit(-1);
    }
    auto line = std::string();
    while (getline(fin, line)) {
      auto ss = std::stringstream(line);
      auto paf_record = PafRecord();
      ss >> paf_record.qry_name;
      ss >> paf_record.qry_len;
      ss >> paf_record.qry_start;
      ss >> paf_record.qry_end;
      ss >> paf_record.relative_strand;
      ss >> paf_record.tar_name;
      ss >> paf_record.tar_len;
      ss >> paf_record.tar_start;
      ss >> paf_record.tar_end;
      ss >> paf_record.num_match_residue;
      ss >> paf_record.len_alignment_block;
      ss >> paf_record.map_qual;
      res.emplace_back(std::move(paf_record));
    }
    return res;
  }

  friend std::ostream& operator<<(std::ostream& os, const PafRecord& obj) {
    os << obj.qry_name << '\t';
    os << obj.qry_len << '\t';
    os << obj.qry_start << '\t';
    os << obj.qry_end << '\t';
    os << obj.relative_strand << '\t';
    os << obj.tar_name << '\t';
    os << obj.tar_len << '\t';
    os << obj.tar_start << '\t';
    os << obj.tar_end << '\t';
    os << obj.num_match_residue << '\t';
    os << obj.len_alignment_block << '\t';
    os << obj.map_qual << '\n';
    return os;
  }
};
