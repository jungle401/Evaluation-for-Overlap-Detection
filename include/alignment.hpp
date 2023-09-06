#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <cassert>

#include <file_io/maf_record.hpp>
#include <file_io/paf_record.hpp>

class Alignment {
public:
  std::string ref_name;
  int ref_start;
  int ref_end;
  char ref_strand;
  // int ref_size;
  // std::string ref_seq;
  std::string qry_name;
  int qry_start;
  int qry_end;
  char qry_strand;
  // int qry_size;
  // std::string qry_seq;
  int qry_read_id;
  Alignment(
    std::string ref_name,
    int ref_start,
    int ref_end,
    char ref_strand,
    std::string qry_name,
    int qry_start,
    int qry_end,
    char qry_strand,
    int qry_read_id
  ) :
    ref_name(ref_name),
    ref_start(ref_start),
    ref_end(ref_end),
    ref_strand(ref_strand),
    qry_name(qry_name),
    qry_start(qry_start),
    qry_end(qry_end),
    qry_strand(qry_strand),
    qry_read_id(qry_read_id)
  {}

  static std::vector<Alignment> get_alignments(
    const std::filesystem::path& file,
    const std::unordered_map<std::string, int>& read_name_to_id
  ) {
    auto res = std::vector<Alignment>();
    auto format = file.extension();
    if (format == ".maf") {
      auto maf_records = MafRecord::get_records(file);
      for (auto& r : maf_records) {
        auto alignment =
          Alignment(
            r.ref_name,
            r.ref_alignment_start,
            r.ref_alignment_start + r.ref_alignment_size,
            r.ref_strand,
            r.qry_name,
            r.qry_alignment_start,
            r.qry_alignment_start + r.qry_alignment_size,
            r.qry_strand,
            read_name_to_id.at(r.qry_name)
          );
        res.emplace_back(std::move(alignment));
      }
    } else if (format == ".paf") {
      auto paf_records = PafRecord::get_records(file);
      // Note the strand of reference sequence in read-to-reference mapping
      // simulated by PBSIM3 would always be positive, so the relative strand
      // could be representative.
      for (auto& r : paf_records) {
        auto alignment =
          Alignment(
            r.tar_name,
            r.tar_start,
            r.tar_end,
            '+',
            r.qry_name,
            r.qry_start,
            r.qry_end,
            r.relative_strand,
            read_name_to_id.at(r.qry_name)
          );
        res.emplace_back(std::move(alignment));
      }
    } else {
      assert(false);
    }
    return res;
  }
  friend std::ostream& operator<<(std::ostream& os, const Alignment& obj) {
    os << obj.ref_name << '\t';
    os << obj.ref_start << '\t';
    os << obj.ref_end << '\t';
    os << obj.ref_strand << '\t';
    os << obj.qry_name << '\t';
    os << obj.qry_start << '\t';
    os << obj.qry_end << '\t';
    os << obj.qry_strand << '\t';
    os << obj.qry_read_id << '\n';
    return os;
  }
};
