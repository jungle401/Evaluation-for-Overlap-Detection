#pragma once

#include <iostream>
#include <filesystem>
#include <unordered_map>

#include <file_io/fasta_record.hpp>

class Read {
public:
  std::string name;
  size_t size;
  Read(const std::string& name, size_t size)
  : name(name), size(size) {}
  static std::vector<Read> get_reads(
    const std::filesystem::path& file
  ) {
    auto res = std::vector<Read>();
    if (file.extension() == ".fasta") {
      auto fasta_records = FastaRecord::get_records(file);
      for (auto& rec : fasta_records) {
        res.push_back(Read(rec.name, rec.seq.size()));
      }
    }
    return res;
  }
  static std::unordered_map<std::string, int> get_read_name_to_id(
    const std::vector<Read>& reads
  ) {
    auto res = std::unordered_map<std::string, int>();
    auto iter = 0;
    for (const auto& item : reads) {
      res[item.name] = iter++;
    }
    return res;
  }
  friend std::ostream& operator<<(std::ostream& os, const Read& obj) {
    os << ">" << obj.name << "\t";
    os << obj.size << "\n";
    return os;
  }
};
