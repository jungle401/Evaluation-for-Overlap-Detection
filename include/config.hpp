#pragma once
#include <filesystem>
namespace config {

static std::filesystem::path project_source_dir = PROJECT_SOURCE_DIR;
constexpr static bool log_true_positives = false;

}
