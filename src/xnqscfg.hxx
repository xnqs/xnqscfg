#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>

namespace xnqs {
namespace cfg {

enum EntryType {
	TypeString,
	TypeArray,
};

typedef int entry_type_t;
typedef struct entry_value entry_value_t;
typedef struct entry entry_t;

std::unordered_map<std::string, xnqs::cfg::entry_t*> parse_config_file(const std::filesystem::path& config_filepath);

};
};
