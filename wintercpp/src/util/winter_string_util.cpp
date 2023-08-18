//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2020-01-30.
//

#include <wintercpp/util/winter_string_util.h>

#include <algorithm>
#include <locale>

namespace winter::util::string {

    /**
     * @brief Replaces all occurrences of a substring in a string.
     *
     * This function returns a new string where every occurrence of the specified substring is replaced
     * with another string. The original string IS MODIFIED.
     *
     * @param str The input string to search for substrings.
     * @param from The substring to replace.
     * @param to The string to replace `from` with.
     * @return A new string where all occurrences of `from` have been replaced with `to`.
     */
    std::string replace(std::string& str, const std::string& from, const std::string& to) {
        str = replace_value(str, from, to);
        return str;
    }

    /**
     * @brief Replaces all occurrences of a substring in a string.
     *
     * This function returns a new string where every occurrence of the specified substring is replaced
     * with another string. The original string is not modified.
     *
     * @param str The input string to search for substrings.
     * @param from The substring to replace.
     * @param to The string to replace `from` with.
     * @return A new string where all occurrences of `from` have been replaced with `to`.
     */

    std::string replace_value(std::string str, const std::string& from, const std::string& to) {
        size_t       start_pos = 0;
        const size_t from_len = from.length();
        const size_t to_len = to.length();

        // Use a loop and std::string::find() to find all occurrences of the substring.
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            // When we find a match, use std::string::replace() to replace it with the new string.
            str.replace(start_pos, from_len, to);
            // Increment start_pos to avoid replacing the same substring again.
            start_pos += to_len;
        }

        // Return the modified string.
        return str;
    }

    /**
     * @brief Removes non-ASCII characters and whitespace from a string.
     *
     * This function modifies the input string by removing any characters that are outside
     * the ASCII range (with a value greater than 127) or are considered whitespace according
     * to the classic C locale. The resulting string will only contain ASCII characters that
     * are not whitespace.
     *
     * @param str The string to modify.
     */
    void strip_unicode(std::string& str) {
        // Use the erase-remove idiom to remove non-ASCII characters and whitespace.
        // This works by calling std::remove_if to move all unwanted characters to the end
        // of the string, then erasing them with the corresponding call to str.erase().
        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
                      // Check if the character is outside of the ASCII range or is whitespace.
                      // We use static_cast to convert the char to an unsigned char for comparison.
                      // We also use std::isspace() to check if it's a whitespace character.
                      return static_cast<unsigned char>(c) > 127 || std::isspace(c, std::locale::classic());
                  }),
                  str.end());
    }

    /**
     * @brief Removes leading and trailing whitespace from a string.
     *
     * This function modifies the input string to remove any whitespace characters (e.g. spaces, tabs,
     * newlines) that appear at the beginning or end of the string.
     *
     * @param str The string to modify.
     */
    void trim_string(std::string& str) {
        // Find the first non-whitespace character.
        const size_t start = str.find_first_not_of(" \t\n\v\f\r");
        if (start == std::string::npos) {
            // If the string is empty or contains only whitespace, clear it.
            str.clear();
            return;
        }

        // Trim leading whitespace by erasing it from the string.
        str.erase(0, start);

        // Find the last non-whitespace character.
        const size_t end = str.find_last_not_of(" \t\n\v\f\r");

        // Trim trailing whitespace by erasing it from the string.
        if (end != std::string::npos && end != str.length() - 1) {
            str.erase(end + 1);
        }
    }
}  // namespace winter::util::string