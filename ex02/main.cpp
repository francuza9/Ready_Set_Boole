#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>

uint32_t gray_code(uint32_t n);

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

void print_comparison(const std::string& label, uint32_t expected, uint32_t result) {
	bool is_correct = (expected == result);
	std::string status = is_correct ? Colors::CORRECT + "(Correct)" + Colors::END
							: Colors::RED + "(Incorrect)" + Colors::END;

	std::cout << std::left << std::setw(25) << ("Expected " + label + ":")
		<< Colors::EXPECTED << expected << Colors::END << std::endl;

	if (is_correct)
		std::cout << std::left << std::setw(25) << "Result:" << Colors::GREEN << result << Colors::END << " " << status << std::endl;
	else
		std::cout << std::left << std::setw(25) << "Result:" << Colors::RED << result << Colors::END << " " << status << std::endl;

	std::cout << std::endl;
}

void test_gray_code() {
    std::cout << std::endl << Colors::HEADER << "--- GRAY CODE TESTS ---"
              << Colors::END << std::endl << std::endl;

    struct TestCase { uint32_t n, expected; };

    TestCase tests[] = {
        {0, 0},
        {1, 1},
        {2, 3},
        {3, 2},
        {4, 6},
        {5, 7},
        {6, 5},
        {7, 4},
        {8, 12},
        {9, 13},
        {15, 8},
        {16, 24},
        {31, 16},
        {255, 128},
        {1023, 512},
        {4294967295u, 2147483648u} // large edge case
    };

    for (auto& t : tests) {
        std::cout << Colors::TEST << "Testing gray_code(" << t.n << ")"
                  << Colors::END << std::endl << "---" << std::endl;
        uint32_t result = gray_code(t.n);
        print_comparison("Gray code", t.expected, result);
    }
}

int main() {
	test_gray_code();
	return 0;
}