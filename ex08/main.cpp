#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// ───────────────────────────────
// COLORS (same style as example)
// ───────────────────────────────
namespace Colors {
    const std::string RED = "\033[91m";
    const std::string GREEN = "\033[92m";
    const std::string BLUE = "\033[94m";
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
    const std::string HEADER = BOLD + BLUE + UNDERLINE;
    const std::string TEST = BLUE + BOLD;
    const std::string CORRECT = GREEN;
    const std::string EXPECTED = BOLD + UNDERLINE;
    const std::string END = "\033[0m";
}

std::vector<std::vector<int>> powerset(const std::vector<int>& set);

std::string subset_to_string(const std::vector<int>& subset) {
    std::string s = "{ ";
    for (size_t i = 0; i < subset.size(); ++i) {
        s += std::to_string(subset[i]);
        if (i + 1 < subset.size()) s += ", ";
    }
    s += " }";
    return s;
}

void test_powerset(const std::vector<int>& set) {
    std::cout << std::endl
              << Colors::TEST << "Testing powerset({ " 
              << ([](const std::vector<int>& s){
                    std::string tmp;
                    for (size_t i = 0; i < s.size(); ++i) {
                        tmp += std::to_string(s[i]);
                        if (i + 1 < s.size()) tmp += ", ";
                    }
                    return tmp;
                 })(set)
              << " })" << Colors::END << std::endl
              << "---" << std::endl;

    auto result = powerset(set);
    std::cout << Colors::HEADER << "Generated Powerset (" 
              << result.size() << " subsets):" 
              << Colors::END << std::endl;

    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << std::setw(3) << i << ": "
                  << subset_to_string(result[i]) << std::endl;
    }
}

int main() {
    std::cout << std::endl 
              << Colors::HEADER << "--- POWERSET TESTS ---" 
              << Colors::END << std::endl;

    test_powerset({});                // empty set
    test_powerset({1});               // single element
    test_powerset({1, 2});            // two elements
    test_powerset({10, 20, 30});      // three elements
    test_powerset({1, 2, 3, 4});      // four elements

    std::cout << std::endl 
              << Colors::GREEN << "All tests completed successfully!" 
              << Colors::END << std::endl;
    return 0;
}
