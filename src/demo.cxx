#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

// xnqscfg's header files, you don't have to include lexer.hxx, but i'm including
// it here to demonstrate how it works by itself
#include <xnqscfg/xnqscfg.hxx>
#include <xnqscfg/lexer.hxx>

// prints an xnqs::cfg::entry with a dfs-type algorithm
void print_variable(xnqs::cfg::entry* node) {
	if (node->type == xnqs::cfg::TypeString) {
		std::cout << "\"" << node->str << "\" ";
		return;
	}

	std::cout << "{ ";
	for (const auto& next : node->arr) {
		print_variable(next);
	}
	std::cout << "}\n";
}

int main() {
	// xnqscfg takes an std::filesystem::path which points to a config file
	std::filesystem::path config_file("../sample.xnqscfg");
	std::cout << config_file.c_str() << "\n";

	// here we are using xnqs::cfg::run_lexer(config_file), which
	// is again completely unnecessary, but we are doing it just
	// to demonstrate how the lexer works
	std::cout << "Tokens:\n";
	std::vector<std::string> tokens = xnqs::cfg::run_lexer(config_file);
	for (const auto& token : tokens) {
		std::cout << token << "\n";
	}
	std::cout << "\n";

	// xnqs::cfg::parse_config_file(config_file) returns a map where
	// the key is an std::string and the value is an xnqs::cfg::entry_t*
	std::map<std::string, xnqs::cfg::entry_t*> config = xnqs::cfg::parse_config_file(config_file);
	std::cout << "Let's print all of the variables and their contents below, after we've parsed the tokens:\n";
	for (const auto& [key, value] : config) {
		std::cout << key << " = ";
		print_variable(value);
		std::cout << "\n";
	}
	std::cout << "\n";

	// syntax for accessing individual members
	std::cout << "Let's access individual members:\n";
	std::cout << "name = " << config["name"]->str << "\n";
	std::cout << "array[0] = " << config["array"]->arr[0]->str << "\n";
	std::cout << "array2[1][2] = " << config["array2"]->arr[1]->arr[2]->str << "\n";

	// Use this to avoid memory leaks
	xnqs::cfg::cleanup(config);
}
