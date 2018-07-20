#include <vector>
#include <filesystem>
#include <iostream>

#include "config.hpp"

namespace fs = std::filesystem;

#if ASCII_ONLY
constexpr std::string_view junction("|---"), bar("|   "), angle("\\---"), space("    ");
#else
constexpr std::string_view junction("├── "), bar("│   "), angle("└── "), space("    ");
#endif

void walk(const fs::path& path, const int depth = 0, const bool is_last = false, std::vector<std::string_view>& headers = std::vector<std::string_view>()) {
	for (const auto& token : headers) {
		std::cout << token;
	}

	if (depth != 0) {
		std::cout << (is_last ? angle : junction);
	}

	std::cout << path.filename().generic_string() << '\n';

	if (depth != 0) {
		headers.emplace_back(is_last ? space : bar);
	}

	if (!fs::is_directory(path)) {
		return;
	}

	fs::directory_iterator dir_iter(path);
	const auto entry_count = std::distance(fs::begin(dir_iter), fs::end(dir_iter));
	dir_iter = fs::directory_iterator(path);
	for (int i = 0; i < entry_count; ++i, ++dir_iter) {
		walk(dir_iter->path(), depth + 1, (i == entry_count - 1), headers);
		headers.pop_back();
	}
}

void print_version() {
	std::cout << "tree-cpp17 v" << TREECPP17_VERSION << " (c) " << CURRENT_YEAR << " by " << CREDITS << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc > 1 && std::string_view(argv[1]) == "--version") {
		print_version();
		return EXIT_SUCCESS;
	}

	const fs::path root((argc > 1) ? argv[1] : ".");

	walk(root);

	return EXIT_SUCCESS;
}