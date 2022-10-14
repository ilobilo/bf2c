// Copyright (C) 2022  ilobilo

#include <conflict/conflict.hpp>

#include <filesystem>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string_view> files;
uint64_t flags = 0;

const auto parser = conflict::parser
{
    conflict::option { { 'h', "help", "Show help" }, flags, (1 << 0) },
    conflict::option { { 'v', "version", "Show version" }, flags, (1 << 1) }
};

bool parse_flags()
{
    if (flags & (1 << 0))
    {
        std::cout << "Usage:\n";
        std::cout << "    bf2c input.bf output.c\n";
        std::cout << "Options:\n";
        parser.print_help();
        return true;
    }
    else if (flags & (1 << 1))
    {
        std::cout << "bf2c v0.1\n";
        return true;
    }

    return false;
}

auto main(int argc, char **argv) -> int
{
    parser.apply_defaults();
    conflict::default_report(parser.parse(argc - 1, argv + 1, files));

    if (parse_flags())
        return EXIT_SUCCESS;

    if (files.size() != 2)
    {
        std::cerr << "Usage:\n";
        std::cerr << "    bf2c input.bf output.c" << std::endl;
        return EXIT_FAILURE;
    }

    auto input_file = files.front();
    auto output_file = files.back();

    if (fs::exists(input_file) == false)
    {
        std::cerr << "File '" << input_file << "' does not exist!" << std::endl;
        return EXIT_FAILURE;
    }

    if (fs::is_regular_file(input_file) == false)
    {
        std::cerr << "'" << input_file << "' is not a regular file!" << std::endl;
        return EXIT_FAILURE;
    }

    if (fs::exists(output_file) && fs::is_regular_file(output_file) == false)
    {
        std::cerr << "'" << output_file << "' is not a regular file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream input(input_file.data());
    std::ofstream output(output_file.data(), std::ios::trunc);
    std::string spaces("    ");

    output << "extern int putchar(int __c);\n"
           << "extern int getchar(void);\n"
           << "\n"
           << "int main()\n"
           << "{\n"
           << "    char array[30000] = { 0 };\n"
           << "    char *ptr = array;\n"
           << "\n";

    for (auto c = input.get(); c != EOF; c = input.get())
    {
        switch (c)
        {
            case '>':
                output << spaces << "((ptr == &array[29999]) ? ptr = array : ptr++);\n";
                break;
            case '<':
                output << spaces << "((ptr == array) ? ptr = &array[29999] : ptr--);\n";
                break;
            case '+':
                output << spaces << "++*ptr;\n";
                break;
            case '-':
                output << spaces << "--*ptr;\n";
                break;
            case '.':
                output << spaces << "putchar(*ptr);\n";
                break;
            case ',':
                output << spaces << "*ptr = getchar();\n";
                break;
            case '[':
                output << spaces << "while (*ptr)\n";
                output << spaces << "{\n";
                spaces += "    ";
                break;
            case ']':
                spaces.erase(spaces.length() - 4);
                output << spaces << "}\n";
                break;
        }
    }

    output << "}";

    input.close();
    output.close();

    return EXIT_SUCCESS;
}