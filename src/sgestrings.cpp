#include "sgestrings.h"

#include <string>
#include <vector>

std::vector<std::string> split(const std::string& string, char separator)
{
    std::vector<std::string> string_parts{};

    std::string current_word{};
    for (const char c : string) {
        if (c != separator) {
            current_word += c;
        } else {
            string_parts.push_back(current_word);
            current_word = "";
        }
    }

    if (!current_word.empty()) {
        string_parts.push_back(current_word);
    }

    return string_parts;
}
