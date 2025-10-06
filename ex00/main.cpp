#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>

uint32_t adder(uint32_t a, uint32_t b);

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

void test_adder() {
	std::cout << std::endl << Colors::HEADER << "--- BITWISE ADDER TESTS ---" << Colors::END << std::endl << std::endl;

	struct TestCase { uint32_t a, b, expected; };
	TestCase tests[] = {
		{0, 0, 0},
		{0, 5, 5},
		{7, 0, 7},
		{1, 1, 2},
		{2, 3, 5},
		{5, 9, 14},
		{15, 1, 16},
		{8, 8, 16},
		{255, 255, 510},
		{12345, 6789, 19134},
		{4294967290, 5, (4294967290u + 5u)}, // wrap naturally in uint32_t
		{4294967295, 1, 0}, // overflow case
	};

	for (auto& t : tests) {
		std::cout << Colors::TEST << "Testing adder(" << t.a << ", " << t.b << ")" 
			<< Colors::END << std::endl << "---" << std::endl;
		uint32_t result = adder(t.a, t.b);
		print_comparison("Sum", t.expected, result);
	}
}

int main() {
	test_adder();
	return 0;
}