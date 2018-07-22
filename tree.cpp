#include <filesystem>
#include <iostream>
#include <vector>

#include "config.hpp"

namespace fs = std::filesystem;

#if ASCII_ONLY
constexpr std::string_view junction("|---"), bar("|   "), angle("\\---"), space("    ");
#else
constexpr std::string_view junction("├── "), bar("│   "), angle("└── "), space("    ");
#endif

void walk(const fs::path& path, std::vector<std::string_view>& headers, std::pair<int, int>& counter) {
	if (!fs::is_directory(path)) {
		++counter.second;
		return;
	}

	fs::directory_iterator dir_iter(path);
	const auto entry_count = std::distance(fs::begin(dir_iter), fs::end(dir_iter));
	dir_iter = fs::directory_iterator(path);
	for (int i = 0; i < entry_count; ++i, ++dir_iter) {
		for (const auto& token : headers) {
			std::cout << token;
		}

		const bool is_last = (i == entry_count - 1);

		std::cout << (is_last ? angle : junction)
			<< dir_iter->path().filename().generic_string() << '\n';

		if (fs::is_directory(dir_iter->path())) {
			++counter.first;
			headers.emplace_back(is_last ? space : bar);
			walk(dir_iter->path(), headers, counter);
			headers.pop_back();
		} else {
			++counter.second;
		}
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

	std::pair<int, int> counter = std::make_pair(0, 0);
	const fs::path root((argc > 1) ? argv[1] : ".");

	std::cout << root.generic_string() << '\n';
	walk(root, std::vector<std::string_view>(), counter);

	std::cout << '\n' 
		<< counter.first << ((counter.first == 1) ? " directory, " : " directories, ")
		<< counter.second << ((counter.second == 1) ? " file." : " files.")
		<< std::endl;

	return EXIT_SUCCESS;
}