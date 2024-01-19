#include "BloomFilter.h"
#include <vector>
#include <string>
//#include "HashFunc.h"  // Consider adding this include if needed.
#include "HelpFunctions.h"
#include <istream>

int main(int argc, char** argv) {
    std::string user_input;
    bool flag_user_input = true;

    // Get user input for configuration
    while (flag_user_input) {
        std::getline(std::cin, user_input);
        std::vector<std::string> str_vector = split(user_input);
        if (str_vector.size() < 2) {
            // Handle invalid input
            // You may want to provide feedback to the user or exit the program
        } else {
            flag_user_input = false;
        }
    }

    // Create a BloomFilter based on the user configuration
    BloomFilter bl(user_input);

    // Main loop for processing user input
    while (true) {
        std::getline(std::cin, user_input);
        if (user_input == "") {
            continue;  // Skip empty lines
        }
        bl.dealWithLine(user_input);
    }

    return 0;
}
