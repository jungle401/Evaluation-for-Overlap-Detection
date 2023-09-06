#include <filesystem>
#include <algorithm>
#include <execution>

#include <fmt/format.h>
#include <omp.h>

#include <options.hpp>
#include <utils.hpp>
#include <read.hpp>
#include <alignment.hpp>
#include <overlap.hpp>
#include <evaluator.hpp>

#include <file_io/hse_record.hpp>

using namespace std;
using VI = vector<int>;

int main(int argc, char** argv) {
  Options::parse(argc, argv);
  Options::show_params();
  auto reads = Read::get_reads(Options::reads_file);
  auto read_name_to_id = Read::get_read_name_to_id(reads);
  auto reference_mapping = Alignment::get_alignments(Options::mapping_file, read_name_to_id);
  auto reads_overlaps = Overlap::get_overlaps(Options::overlaps_file, read_name_to_id);
  cout << reads.size() << endl;
  cout << reference_mapping.size() << endl;
  cout << reads_overlaps.size() << endl;
  auto evaluator = Evaluator(Options::min_ovl_len, Options::max_ovl_len, Options::ovl_len_bin_size, reads);
  evaluator.set_positive_ovl_count(reference_mapping);
  evaluator.set_prediction_ovl_count(reads_overlaps);
  // evaluator.show_result<Evaluator::ResultType::TRADITIONAL>();
  // evaluator.show_result<Evaluator::ResultType::INTERVAL>();
  evaluator.show_result<Evaluator::ResultType::ACCUMULATIVE>();
}
