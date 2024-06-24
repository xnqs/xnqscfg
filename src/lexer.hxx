#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstring>

namespace xnqs {
namespace cfg {

std::vector<std::string> run_lexer(const std::filesystem::path& config_path);

};
};
