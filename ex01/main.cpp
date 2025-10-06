#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>

uint32_t multiplier(uint32_t a, uint32_t b);

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

void test_multiplier() {
    std::cout << std::endl
              << Colors::HEADER << "--- BITWISE MULTIPLIER TESTS ---"
              << Colors::END << std::endl << std::endl;

    struct TestCase { uint32_t a, b, expected; };

    TestCase tests[] = {
        // --- Basic small numbers ---
        {0, 0, 0},
        {0, 5, 0},
        {7, 0, 0},
        {1, 1, 1},
        {2, 2, 4},
        {2, 3, 6},
        {3, 5, 15},
        {4, 8, 32},

        // --- Asymmetrical cases ---
        {1, 1234, 1234},
        {1234, 1, 1234},
        {5, 9, 45},
        {9, 5, 45},

        // --- Powers of two ---
        {8, 8, 64},
        {16, 4, 64},
        {64, 64, 4096},

        // --- Random mid-range ---
        {123, 456, 56088},
        {789, 321, 253269},
        {1024, 1024, 1048576},

        // --- Larger but safe (within 32-bit range) ---
        {65535, 2, 131070},
        {10000, 10000, 100000000},

        // --- Overflow checks (wraparound expected) ---
        {4294967295u, 1, 4294967295u},          // max * 1
        {4294967295u, 2, (uint32_t)(4294967295u * 2u)}, // overflow
        {4294967290u, 10, (uint32_t)(4294967290u * 10u)}, // overflow
        {4000000000u, 2, (uint32_t)(4000000000u * 2u)},   // overflow
        {3000000000u, 3, (uint32_t)(3000000000u * 3u)},   // overflow
    };

    for (auto& t : tests) {
        std::cout << Colors::TEST << "Testing multiplier("
                  << t.a << ", " << t.b << ")" << Colors::END << std::endl
                  << "---" << std::endl;

        uint32_t result = multiplier(t.a, t.b);
        print_comparison("Product", t.expected, result);
    }
}

int main() {
	test_multiplier();
	return 0;
}