#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstring>

#include "lexer.hxx"

namespace xnqs {
namespace cfg {

std::vector<std::string>
run_lexer(const std::filesystem::path& config_path) {
	std::vector<std::string> ret;
	std::ifstream fin(config_path.c_str());

	if (!fin.good()) {
		return ret;
	}

	bool in_comment = 0;
	bool in_string = 0;
	int array_depth = 0;
	std::string buffer;

	while (!fin.eof()) {
		char ch = fin.get();

		if (in_comment) {
			if (ch == '\n' || ch == '\r') {
				in_comment = 0;
			}
			continue;
		}
		if (in_string) {
			if (ch == '\"') {
				if (!buffer.empty() && buffer.back() == '\\') {
					buffer.pop_back();
					buffer += ch;
				}
				else {
					ret.emplace_back(buffer);
					buffer.clear();
					in_string = 0;
				}
			}
			else {
				buffer += ch;
			}
			continue;
		}
		if (array_depth > 0) {
			if (ch == ';' || ch == '=') {
				ret.clear();
				return ret;
			}
		}

		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_') {
			buffer += ch;
			continue;
		}
		if (ch == '=') {
			if (buffer.empty()) {
				ret.clear();
				return ret;
			}
			ret.emplace_back(buffer);
			buffer.clear();
			ret.emplace_back(std::string(1,ch));
			continue;
		}
		if (ch == '#') {
			in_comment = 1;
			continue;
		}
		if (ch == '\"') {
			in_string = 1;
			continue;
		}
		if (ch == '{') {
			ret.emplace_back(std::string(1,ch));
			array_depth += 1;
			continue;
		}
		if (ch == '}') {
			if (array_depth <= 0) {
				ret.clear();
				return ret;
			}
			else {
				--array_depth;
				ret.emplace_back(std::string(1,ch));
			}
		}
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',' || ch == ';') {
			continue;
		}
	}
	
	fin.close();
	return ret;
}

};
};
