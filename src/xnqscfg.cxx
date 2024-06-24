#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdint>
#include <unordered_map>
#include <cstring>
#include <functional>

#include "xnqscfg.hxx"
#include "lexer.hxx"

namespace xnqs {
namespace cfg {

typedef int entry_type_t;

typedef struct entry_value {
	std::string str;
	std::vector<xnqs::cfg::entry_t*> arr;
} entry_value_t;

typedef struct entry {
	xnqs::cfg::entry_type_t type;
	xnqs::cfg::entry_value_t value;

	xnqs::cfg::entry_t* operator[] (int idx) {
		if (type != xnqs::cfg::TypeArray) {
			return nullptr;
		}
		if (!(0 <= idx && idx < value.arr.size())) {
			return nullptr;
		}

		return value.arr[idx];
	}

	~entry() {
		if (type == xnqs::cfg::TypeArray) {
			while (!value.arr.empty()) {
				delete value.arr.back();
				value.arr.pop_back();
			}
		}
	}
} entry_t;

void
clear_map(std::unordered_map<std::string, xnqs::cfg::entry_t*>& map) {
	for (auto& [key, value] : map) {
		delete value;
	}
	map.clear();
}

std::unordered_map<std::string, xnqs::cfg::entry_t*>
parse_config_file(const std::filesystem::path& config_filepath) {
	std::vector<std::string> tokens = xnqs::cfg::run_lexer(config_filepath);

	std::unordered_map<std::string, xnqs::cfg::entry_t*> ret;

	std::size_t i = 0;
	while (i < tokens.size()) {
		const std::string& variable_name = tokens[i];
		
		++i;
		if (!(i < tokens.size())) {
			xnqs::cfg::clear_map(ret);
			return ret;
		}

		if (tokens[i] != "=") {
			xnqs::cfg::clear_map(ret);
			return ret;
		}
		++i;

		xnqs::cfg::entry_t* curr = new xnqs::cfg::entry_t;
		ret[variable_name] = curr;

		std::function<int()> eval;
		std::function<int()> parse_string;

		parse_string = [&]() {
			if (i >= tokens.size()) {
				return 0;
			}
			curr->type = xnqs::cfg::TypeString;
			curr->value.str = tokens[i++];
			return 1;
		};

		eval = [&]() {
			// check for potentially malformed input (var = )
			if (i >= tokens.size()) {
				return 0;
			}

			int ret = 1;

			// parse an array: call eval() recursively in curr's children
			if (tokens[i] == "{") {
				++i;
				curr->type = xnqs::cfg::TypeArray;

				xnqs::cfg::entry_t* tmp = curr;

				while (i < tokens.size() && tokens[i] != "}") {
					xnqs::cfg::entry_t* next = new xnqs::cfg::entry_t;
					curr->value.arr.emplace_back(next);
					curr = next;
					ret &= eval();
					curr = tmp;
				}

				if (tokens[i] != "}") {
					return 0;
				}
				else {
					++i;
				}
			}

			// parse a string: base case
			else if (tokens[i][0] == '\"') {
				ret &= parse_string();
			}

			// malformed input: base case
			else {
				return 0;
			}

			return ret;
		};

		if (!eval()) {
			xnqs::cfg::clear_map(ret);
			return ret;
		}
	}

	return ret;
}
};
};
