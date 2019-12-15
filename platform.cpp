#include <filesystem>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#endif

namespace fs = std::filesystem;

int64_t get_file_size(const fs::path& path) {
#ifdef _WIN32
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesEx(path.generic_string().c_str(), GetFileExInfoStandard, &fad)) {
		return -1;
	}
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
#endif
}