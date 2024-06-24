#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace xnqs {
namespace cfg {

enum EntryType {
	TypeString,
	TypeArray,
};

typedef int entry_type_t;

typedef struct entry_value entry_value_t;
typedef struct entry entry_t;

struct entry {
	xnqs::cfg::entry_type_t type;
	std::string str;
	std::vector<xnqs::cfg::entry_t*> arr;

	~entry() {
		if (type == xnqs::cfg::TypeArray) {
			while (!arr.empty()) {
				delete arr.back();
				arr.pop_back();
			}
		}
	}
};

void cleanup(std::map<std::string, xnqs::cfg::entry_t*>& map);
std::map<std::string, xnqs::cfg::entry_t*> parse_config_file(const std::filesystem::path& config_filepath);

};
};
