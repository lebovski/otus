// OTUS C++ basic course
// Capitalize all words

#include <cctype>
#include <iostream>
#include <string>

void print_capitalized(const std::string &text) {
    bool in_word = false;
    for (char ch : text) {
        if (std::isspace(ch)) {
            in_word = false;
        } else {
            if (!in_word) {
                ch = std::toupper(ch);
                in_word = true;
            }
        }
        std::cout << ch;
    }
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        print_capitalized(argv[i]);
        std::cout << ((i == argc - 1) ? '\n' : ' ');
    }
}
