# Tree for C++17

This is a C++17 implementation of the GNU `tree` utility, making use of the new `filesystem` header in the C++17 standard library.

This project will make no effort to port the original C code over; instead this project aims to re-implement similar, if not identical, functionality from scratch.

## Changelog
Version **0.2.0**
- Added line that prints the number of directories and files.
- Simplified recursion logic a little.

## Building
Use CMake (>= 3.7) to configure the project, then use the compiler or IDE of your choice to build it.

The source code should compile with any C++17 compatible compiler.

## To-Do
- Implement colored output (Decide color scheme?)
- No support for multibyte characters in filenames yet (Will crash)
- Find a getopt replacement

## License

GPLv3

## FAQ
#### 1. Why?
I wanted to try out `filesystem` and `string_view` in C++17.

I also needed the scratch the itch where Windows does not have an up-to-date version of `tree`.

#### 2. Will you add support for the same features as the GNU `tree` utility?
If I have time, eventually. Pull requests are welcome.

However, I also hope to keep the source code simple.

#### 3. Why GPLv3?
In the spirit of the original GNU utilities.
