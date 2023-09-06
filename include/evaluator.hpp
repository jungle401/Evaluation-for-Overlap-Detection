#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <atomic>
#include <memory>
#include <iomanip>

#include <omp.h>
#include <boost/container_hash/hash.hpp>
#include <fmt/format.h>

#include <read.hpp>
#include <alignment.hpp>
#include <overlap.hpp>
#include <options.hpp>
#include <config.hpp>
#include <rp_logger.hpp>

using namespace std;

class Evaluator {
public:
  // Binned true overlap count. Binning is by true overlap length obtained from
  // reads-to-reference mapping.
  vector<int> positive_ovl_count;
  // minimum overlap length
  int min_ovl_len;
  // maximum overlap length
  int max_ovl_len;
  // overlap length bin size
  int ovl_len_bin_size;
  // count of bin
  int bin_count;
  // numeric read id from reads_file should be mappable to alignment after sorting.
  vector<Alignment*> read_id_to_alignment;
  // tool's overlap prediction of true and false should be both count
  vector<int> true_positives;
  // reads_size
  int reads_size;
  vector<int> false_positives;
  vector<float> FPRs;
  vector<float> sensitivities;
  vector<float> precisions;
  vector<float> f1_scores;
  // ammount of instances with completely no overlap
  int negatives = 0;

  Evaluator(
    int min_ovl_len,
    int max_ovl_len,
    int ovl_len_bin_size,
    const vector<Read>& reads
  )
    : min_ovl_len(min_ovl_len), max_ovl_len(max_ovl_len), ovl_len_bin_size(ovl_len_bin_size)
  {
    // auto max_seq_len = max_element( reads.begin(), reads.end(), [] (const Read& lhs, const Read& rhs) { return lhs.size < rhs.size; })->size;
    // bin_count = (max_seq_len - min_ovl_len) / this->ovl_len_bin_size;
    bin_count = (max_ovl_len - min_ovl_len) / ovl_len_bin_size + 1;
    positive_ovl_count.resize(bin_count);
    true_positives.resize(bin_count);
    false_positives.resize(bin_count);
    for (auto& i : positive_ovl_count) { i = 0; }
    for (auto& i : true_positives) { i = 0; }
    for (auto& i : false_positives) { i = 0; }
    reads_size = reads.size();
  }

private:
  void set_read_id_to_alignment(
    vector<Alignment>& reference_mapping
  ) {
    this->read_id_to_alignment.resize(reference_mapping.size());
    // for (auto& alignment : reference_mapping) {
    for (int i = 0; i < reference_mapping.size(); i++) {
      this->read_id_to_alignment[reference_mapping[i].qry_read_id] = &(reference_mapping[i]);
    }
  }

public:
  void set_positive_ovl_count(
    vector<Alignment>& reference_mapping
  ) {
    // sort first by reference name and then by ref_start
    sort(
      reference_mapping.begin(), reference_mapping.end(),
      [] (const Alignment& lhs, const Alignment& rhs) {
        if (lhs.ref_name < rhs.ref_name) {
          return true;
        } else if (lhs.ref_name > rhs.ref_name) {
          return false;
        } else {
          return lhs.ref_start < rhs.ref_start;
        }
        // if (lhs.ref_name == rhs.ref_name) {
        //   return lhs.ref_start < rhs.ref_start;
        // } else {
        //   return lhs.ref_name < rhs.ref_name;
        // }
      }
    );
    set_read_id_to_alignment(reference_mapping);
    // find true overlaps, and classify then by overlap length by storing into
    // different bucket of positive_ovl_count.
    for (int it_1 = 0; it_1 < reference_mapping.size();) {
      auto cur_ref_end = reference_mapping.size();
      for (; it_1 < cur_ref_end; it_1++) {
        auto& a1 = reference_mapping[it_1];
        if (a1.ref_end - a1.ref_start < min_ovl_len) { continue; }
        for (int it_2 = it_1 + 1; it_2 < cur_ref_end; it_2++) {
          auto& a2 = reference_mapping[it_2];
          if (a2.ref_name != a1.ref_name) {
            cur_ref_end = it_2;
            break;
          }
          auto r1_st = a1.ref_start;
          auto r1_ed = a1.ref_end;
          auto r2_st = a2.ref_start;
          auto r2_ed = a2.ref_end;
          // TODO:remove the assertion
          assert(r1_st <= r2_st);
          // with the property that r1_st <= r2_st always holds, break r2
          // iteration because the next r2 would also not suffice.
          if (r1_ed - min_ovl_len < r2_st) { break; }
          if (r2_ed - r2_st < min_ovl_len) { continue; }
          auto ovl_len = int();
          if (r1_ed < r2_ed) {
            ovl_len = r1_ed - r2_st;
          } else {
            ovl_len = r2_ed - r2_st;
          }
          assert(ovl_len >= 0);
          auto bucket = (ovl_len > this->max_ovl_len)
            ? this->bin_count - 1
            : (ovl_len - min_ovl_len) / this->ovl_len_bin_size;
          this->positive_ovl_count.at(bucket)++;
        }
      }
    }
  }

  inline int get_real_ovl_len(
    const Overlap& ovl
  ) {
    auto alm1 = read_id_to_alignment[ovl.ref_id];
    auto alm2 = read_id_to_alignment[ovl.qry_id];
    if (alm1->ref_name != alm2->ref_name) { return 0; }
    auto r1 = pair<int, int>{alm1->ref_start, alm1->ref_end};
    auto r2 = pair<int, int>{alm2->ref_start, alm2->ref_end};
    if (r1.first > r2.first) {
      std::swap(r1, r2);
    }
    if (r1.second < r2.first) {
      return 0;
    }
    if (r1.second < r2.second) {
      return r1.second - r2.first;
    } else {
      return r2.second - r2.first;
    }
  }

  inline int get_predicted_ovl_len(
    const Overlap& ovl
  ) {
    // assert(ovl.ref_start <= ovl.ref_end);
    // assert(ovl.qry_start <= ovl.qry_end);
    auto ref_ovl_len = ovl.ref_end - ovl.ref_start;
    auto qry_ovl_len = ovl.qry_end - ovl.qry_start;
    auto mean_ovl_len = (ref_ovl_len + qry_ovl_len) / 2;
    return mean_ovl_len;
  }

  void set_prediction_ovl_count(
    const vector<Overlap>& reads_overlaps
  ) {
    // TODO: compress multiple record with duplicate read pair
    auto false_pos_read_pairs = std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>();
    auto true_pos_read_pairs = std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>();
    for (const auto& ovl : reads_overlaps) {
      if (ovl.ref_id >= read_id_to_alignment.size()) {
        cout << ovl.ref_id << " / " << read_id_to_alignment.size() << endl;
        exit(-1);
      }
      if (ovl.qry_id >= read_id_to_alignment.size()) {
        cout << ovl.qry_id << " / " << read_id_to_alignment.size() << endl;
        exit(-1);
      }
      auto r1id = read_id_to_alignment.at(ovl.ref_id)->qry_read_id;
      auto r2id = read_id_to_alignment.at(ovl.qry_id)->qry_read_id;
      // minimap2 output self mapping overlaps ......
      if (r1id == r2id) { continue; }
      auto rp = (r1id < r2id) ? make_pair( r1id, r2id ) : make_pair( r2id, r1id );
      // overlap length inferred by absolute coordinates on reference mapping is
      // seen as real overlap length
      auto real_ovl_len = get_real_ovl_len(ovl);
      assert(real_ovl_len >= 0);
      if (real_ovl_len == 0) {
        // cout << r1id << ',' << r2id << endl;
        static auto rp_logger = ReadPairLogger(config::project_source_dir / "output/scere_fps.ovl");
        rp_logger.fout << r1id << ',' << r2id << std::endl;
        // false positive
        if (false_pos_read_pairs.contains(rp)) {
          continue;
        } else {
          false_pos_read_pairs.insert(rp);
        }
        auto predicted_ovl_len = get_predicted_ovl_len(ovl);
        auto bucket = int();
        if (predicted_ovl_len > this->max_ovl_len) {
          bucket = this->bin_count - 1;
        } else if (predicted_ovl_len < this->min_ovl_len) {
          bucket = 0;
        } else {
          bucket = (predicted_ovl_len - min_ovl_len) / this->ovl_len_bin_size;
        }
        false_positives.at( bucket ) += 1;
      } else if (real_ovl_len >= min_ovl_len) {
        if (true_pos_read_pairs.contains(rp)) {
          continue;
        } else {
          true_pos_read_pairs.insert(rp);
        }
        if constexpr (config::log_true_positives) {
          std::cout << r1id << ',' << r2id << std::endl;
        }
        auto bucket = (real_ovl_len > this->max_ovl_len)
         ? this->bin_count - 1
         : (real_ovl_len - min_ovl_len) / this->ovl_len_bin_size;
        true_positives.at( bucket ) += 1;
      } else {
        // Instances whose overlap length shorter than min_ovl_len and larger
        // than 0 would neither be count for false_positives or true_positives.
      }
    }
  }
  enum class ResultType {
    ACCUMULATIVE,
    INTERVAL,
    TRADITIONAL
  };
  template<ResultType result_type>
  void show_result() {
    if constexpr (result_type == ResultType::TRADITIONAL) {
      auto false_positive = 0;
      for (int i = 0; i < false_positives.size(); i++) {
        false_positive += false_positives[i];
      }
      for (int i = 0; i < false_positives.size(); i++) {
        false_positives[i] = false_positive;
      }
      for (int i = true_positives.size() - 1; i >= 1; i--) {
        true_positives[i - 1] += true_positives[i];
        positive_ovl_count[i - 1] += positive_ovl_count[i];
      }
    } else if (result_type == ResultType::ACCUMULATIVE) {
      for (int i = true_positives.size() - 1; i >= 1; i--) {
        false_positives[i - 1] += false_positives[i];
        true_positives[i - 1] += true_positives[i];
        positive_ovl_count[i - 1] += positive_ovl_count[i];
      }
    } else if (result_type == ResultType::INTERVAL) {
      // simply do nothing
    }
    for (int i = 0; i < true_positives.size(); i++) {
      sensitivities.push_back(float(true_positives[i]) / float(positive_ovl_count[i]));
      precisions.push_back(float(true_positives[i]) / float(true_positives[i] + false_positives[i]));
      f1_scores.push_back(2 * sensitivities[i] * precisions[i] / (sensitivities[i] + precisions[i]));
      FPRs.push_back(float(false_positives[i]) / float(reads_size - true_positives[i]));
    }
    cout << fmt::format("ovlen, #pos, true_pos, #false_pos") << endl;
    for (int i = 0; i < true_positives.size(); i++) {
      cout << min_ovl_len + i * ovl_len_bin_size << ", ";
      cout << positive_ovl_count[i] << ',';
      cout << true_positives[i] << ',';
      cout << false_positives[i] << '\n';
    }
    auto show_precision = 4;
    cout << endl;
    cout << fmt::format("ovlen, sens, prec, f1sc") << endl;
    for (int i = 0; i < true_positives.size(); i++) {
      cout << min_ovl_len + i * ovl_len_bin_size << ", ";
      cout << setprecision(show_precision) << sensitivities[i] << ", ";
      cout << setprecision(show_precision) << precisions[i] << ", ";
      cout << setprecision(show_precision) << f1_scores[i];
      cout << endl;
    }
    cout << endl;
  }
};
