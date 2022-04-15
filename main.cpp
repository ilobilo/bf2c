// Copyright (C) 2022  ilobilo

#include <iostream>
#include <fstream>
#include <cerrno>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "  bf2c in.bf out.c" << std::endl;
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    std::string spaces("    ");

    fout << "extern int putchar(int __c);\n"
         << "extern int getchar(void);\n"
         << "\n"
         << "int main()\n"
         << "{\n"
         << "    char array[30000] = { 0 };\n"
         << "    char *ptr = array;\n"
         << "\n";

    char ch;
    while (fin >> ch)
    {
        switch (ch)
        {
            case '>':
                fout << spaces << "((ptr == &array[29999]) ? ptr = array : ptr++);\n";
                break;
            case '<':
                fout << spaces << "((ptr == array) ? ptr = &array[29999] : ptr--);\n";
                break;
            case '+':
                fout << spaces << "++*ptr;\n";
                break;
            case '-':
                fout << spaces << "--*ptr;\n";
                break;
            case '.':
                fout << spaces << "putchar(*ptr);\n";
                break;
            case ',':
                fout << spaces << "*ptr = getchar();\n";
                break;
            case '[':
                fout << spaces << "while (*ptr)\n";
                fout << spaces << "{\n";
                spaces += "    ";
                break;
            case ']':
                spaces.erase(spaces.length() - 4);
                fout << spaces << "}\n";
                break;
        }
    }

    fout << "}";

    fin.close();
    fout.close();

    return EXIT_SUCCESS;
}