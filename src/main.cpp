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

void usage(bool err)
{
    auto &out = (err ? std::cerr : std::cout);
    out << "Usage:\n";
    out << "    bf2asm input.bf output.S\n";
}

bool parse_flags()
{
    if (flags & (1 << 0))
    {
        usage(false);
        std::cout << "Options:\n";
        parser.print_help();
        return true;
    }
    else if (flags & (1 << 1))
    {
        std::cout << "bf2asm v0.1\n";
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
        usage(true);
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

    output <<
R"(.bss
array: .zero 30000

.text

write:
    enter 0, 0

    push di

    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1

    syscall

    leave
    ret

read:
    enter 1, 0

    mov rax, 0
    mov rdi, 0
    lea rsi, [rbp - 1]
    mov rdx, 1

    syscall

    movzx ax, byte ptr [rsp]

    leave
    ret

_start:
    mov rax, array
    mov [rsp], rax
)";

    for (auto c = input.get(); c != EOF; c = input.get())
    {
        switch (c)
        {
            case '>':
                output << "    add rsp, 1\n";
                break;
            case '<':
                output << "    sub rsp, 1\n";
                break;
            case '+':
                output << "    mov ax, [rsp]\n    inc ax\n    mov [rsp], ax\n";
                break;
            case '-':
                output << "    mov ax, [rsp]\n    dec ax\n    mov [rsp], ax\n";
                break;
            case '.':
                output << "    mov di, [rsp]\n    call write\n";
                break;
            case ',':
                output << "    xor ax, ax\n    call read\n    mov [rsp], ax\n";
                break;
            case '[':
                output << "    mov ax, [rsp]\n    test ax, ax\n    jz 2f\n";
                output << "1:\n";
                break;
            case ']':
                output << "    mov ax, [rsp]\n    test ax, ax\n    jnz 1b\n";
                output << "2:\n";
                break;
        }
    }

    output <<
R"(    mov rax, 60
    mov rdi, 0
    syscall
.global _start
)";

    input.close();
    output.close();

    return EXIT_SUCCESS;
}