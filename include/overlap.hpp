#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <cassert>

#include <read.hpp>
#include <file_io/maf_record.hpp>
#include <file_io/paf_record.hpp>
#include <file_io/ovl_record.hpp>
#include <file_io/hse_record.hpp>
#include <file_io/mhp_record.hpp>

class Overlap {
public:
  int ref_id = -1;
  std::string ref_name;
  int ref_start;
  int ref_end;
  char ref_strand;
  // int ref_size;
  // std::string ref_seq;
  int qry_id = -1;
  std::string qry_name;
  int qry_start;
  int qry_end;
  char qry_strand;
  // int qry_size;
  // std::string qry_seq;
  Overlap(
    int ref_id,
    std::string ref_name,
    int ref_start,
    int ref_end,
    char ref_strand,
    int qry_id,
    std::string qry_name,
    int qry_start,
    int qry_end,
    char qry_strand
  ) :
    ref_id(ref_id),
    ref_name(ref_name),
    ref_start(ref_start),
    ref_end(ref_end),
    ref_strand(ref_strand),
    qry_id(qry_id),
    qry_name(qry_name),
    qry_start(qry_start),
    qry_end(qry_end),
    qry_strand(qry_strand) {}

  static std::vector<Overlap> get_overlaps(
    const std::filesystem::path& file,
    const std::unordered_map<std::string, int>& read_name_to_id
  ) {
    auto res = std::vector<Overlap>();
    auto format = file.extension();
    if (format == ".paf") {
      // auto read_name_to_id = std::unordered_map<std::string, int>();
      // auto iter = 0;
      // for (const auto& read : reads) {
      //   read_name_to_id[read.name] = iter++;
      // }
      auto paf_records = PafRecord::get_records(file);
      // Note the strand of reference sequence in read-to-reference mapping
      // simulated by PBSIM3 would always be positive, so the relative strand
      // could be representative.
      for (auto& r : paf_records) {
        auto overlap =
          Overlap(
            read_name_to_id.at(r.tar_name),
            r.tar_name,
            r.tar_start,
            r.tar_end,
            '+',
            read_name_to_id.at(r.qry_name),
            r.qry_name,
            r.qry_start,
            r.qry_end,
            r.relative_strand
          );
        res.emplace_back(std::move(overlap));
      }
    } else if (format == ".ovl") {
      auto ovl_records = OvlRecord::get_ovl_records(file);
      for (auto& r : ovl_records) {
        auto overlap =
          Overlap(
            r.r1,
            "dummy",
            r.r1_start,
            r.r1_end,
            '+',
            r.r2,
            "dummy",
            r.r2_start,
            r.r2_end,
            '+'
          );
        res.emplace_back(std::move(overlap));
      }
    } else if (format == ".hse") {
      auto hse_records = HseRecord::get_records(file);
      for (auto& r : hse_records) {
        auto overlap =
          Overlap(
            r.r1 - 1,
            "dummy",
            r.r1_start,
            r.r1_end,
            '+',
            r.r2 - 1,
            "dummy",
            r.r2_start,
            r.r2_end,
            (r.strand == '0') ? '+' : '-'
          );
        res.emplace_back(std::move(overlap));
      }
    } else if (format == ".mhp" || ".m4") {
      auto mhp_records = MhpRecord::get_records(file);
      for (auto& r : mhp_records) {
        auto overlap =
          Overlap(
            r.r1 - 1,
            "dummy",
            r.r1_start,
            r.r1_end,
            '+',
            r.r2 - 1,
            "dummy",
            r.r2_start,
            r.r2_end,
            (r.r1_strand == r.r2_strand) ? '+' : '-'
          );
        res.emplace_back(std::move(overlap));
      }
    } else {
      assert(false);
    }
    return res;
  }
  friend std::ostream& operator<<(std::ostream& os, const Overlap& obj) {
    os << obj.ref_id << '\t';
    os << obj.ref_name << '\t';
    os << obj.ref_start << '\t';
    os << obj.ref_end << '\t';
    os << obj.ref_strand << '\t';
    os << obj.qry_id << '\t';
    os << obj.qry_name << '\t';
    os << obj.qry_start << '\t';
    os << obj.qry_end << '\t';
    os << obj.qry_strand << '\n';
    return os;
  }
};
