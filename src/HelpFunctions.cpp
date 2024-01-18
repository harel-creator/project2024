#include "HelpFunctions.h"

/**
 * @Split a string into an array of words
 * @param str The input string to be split
 * @return A vector of strings containing the individual words
 * @note The caller is responsible for deleting the returned vector if dynamic memory is used.
 */
std::vector<std::string> split(std::string str) {
    std::vector<std::string> splited_str{};
    std::stringstream stream_str(str);
    std::string single_word = "";

    // Every iteration puts a full word to 'single_word', then pushes it to the 
    // end of the vector
    while (stream_str >> single_word) {
        splited_str.push_back(single_word);
    }

    return splited_str;
}
