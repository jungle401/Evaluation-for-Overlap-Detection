#include <iostream>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <options.hpp>

namespace po = boost::program_options;
namespace fs = std::filesystem;

namespace Options {

namespace {

template<typename T>
void show_param(T& item) {
  std::cout << "[PARAM] - ";
  std::cout << item << std::endl;
}

void check_mandatory_params(
  const po::variables_map& vm
) {
  assert(vm.count("reads_file"));
  assert(vm.count("mapping_file"));
  assert(vm.count("overlaps_file"));
  assert(vm.count("min_ovl_len"));
  assert(vm.count("max_ovl_len"));
  assert(vm.count("ovl_len_bin_size"));
}

}

fs::path reads_file;
fs::path mapping_file;
fs::path overlaps_file;
int min_ovl_len;
int max_ovl_len;
int ovl_len_bin_size;

void parse(int argc, char** argv) {
  auto desc = po::options_description("Allowed options");
  desc.add_options()
    ("help", "Produce help messages")
    ("reads_file", po::value<fs::path>(&reads_file))
    ("mapping_file", po::value<fs::path>(&mapping_file))
    ("overlaps_file", po::value<fs::path>(&overlaps_file))
    ("min_ovl_len", po::value<int>(&min_ovl_len))
    ("max_ovl_len", po::value<int>(&max_ovl_len))
    ("ovl_len_bin_size", po::value<int>(&ovl_len_bin_size))
    ;
  auto vm = po::variables_map();
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);
  check_mandatory_params(vm);
}

void show_params() {
  std::cout << "params:\n";
  show_param(reads_file);
  show_param(mapping_file);
  show_param(overlaps_file);
  show_param(min_ovl_len);
  show_param(max_ovl_len);
  show_param(ovl_len_bin_size);
  std::cout << std::endl;
}

};
