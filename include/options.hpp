#pragma once

#include <filesystem>
#include <boost/program_options.hpp>

namespace Options {

extern std::filesystem::path reads_file;
extern std::filesystem::path mapping_file;
extern std::filesystem::path overlaps_file;
extern int min_ovl_len;
extern int max_ovl_len;
extern int ovl_len_bin_size;

void parse(int argc, char** argv);
void show_params();

};
