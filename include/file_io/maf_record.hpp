#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

/**
  * @brief Not a formal class for the maf record, in which be assumed only two
  * sequences exist within one MAF block. This is for maf output particularly
  * by PBSIM, used as ground truth mapping for overlap detecting evaluation.
  * Also, comments are assumed to be absent. Besides, aligned sequences are
  * ignored due to their unnecessity for the evaluation.
  */
class MafRecord {
public:
  std::string ref_name;
  int ref_alignment_start;
  int ref_alignment_size;
  char ref_strand;
  int ref_size;
  // std::string ref_seq;
  std::string qry_name;
  int qry_alignment_start;
  int qry_alignment_size;
  char qry_strand;
  int qry_size;
  // std::string qry_seq;

  static std::vector<MafRecord> get_records(
    const std::filesystem::path& file
  ) {
    auto res = std::vector<MafRecord>();
    auto fin = std::ifstream{file};
    if (!fin.is_open()) {
      std::cerr << "fin failed: " << file << std::endl;
      exit(-1);
    }
    auto line = std::string();
    auto dummy_str = std::string();
    while (std::getline(fin, line)) {
      if (line[0] == 'a') {
        auto maf_record = MafRecord();
        std::getline(fin, line);
        auto ss = std::stringstream(line);
        ss >> dummy_str;
        ss >> maf_record.ref_name;
        ss >> maf_record.ref_alignment_start;
        ss >> maf_record.ref_alignment_size;
        ss >> maf_record.ref_strand;
        ss >> maf_record.ref_size;
        // ss >> maf_record.ref_seq;
        std::getline(fin, line);
        ss = std::stringstream(line);
        ss >> dummy_str;
        ss >> maf_record.qry_name;
        ss >> maf_record.qry_alignment_start;
        ss >> maf_record.qry_alignment_size;
        ss >> maf_record.qry_strand;
        ss >> maf_record.qry_size;
        // ss >> maf_record.qry_seq;
        res.emplace_back(std::move(maf_record));
      }
    }
    return res;
  }

  int get_ref_alignment_end() const {
    return this->ref_alignment_start + this->ref_alignment_size;
  }

  friend std::ostream& operator<<(std::ostream& os, const MafRecord& obj) {
    os << obj.ref_name << '\t';
    os << obj.ref_alignment_start << '\t';
    os << obj.ref_alignment_size << '\t';
    os << obj.ref_strand << '\t';
    os << obj.ref_size << '\t';
    // os << maf_record.ref_seq;
    os << obj.qry_name << '\t';
    os << obj.qry_alignment_start << '\t';
    os << obj.qry_alignment_size << '\t';
    os << obj.qry_strand << '\t';
    os << obj.qry_size << '\n';
    // os << maf_record.ref_seq;
    return os;
  }
};
