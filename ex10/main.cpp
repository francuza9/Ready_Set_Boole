#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdint>

namespace Colors {
	const std::string RED = "\033[91m";
	const std::string GREEN = "\033[92m";
	const std::string BLUE = "\033[94m";
	const std::string BOLD = "\033[1m";
	const std::string UNDERLINE = "\033[4m";
	const std::string HEADER = BOLD + BLUE + UNDERLINE;
	const std::string TEST = BLUE + BOLD;
	const std::string CORRECT = GREEN;
	const std::string END = "\033[0m";
}


double map(uint16_t x, uint16_t y);

void print_result(uint16_t x, uint16_t y, double result, double expected = -1.0) {
	std::cout << Colors::TEST << "Testing map(" << x << ", " << y << ")"
			  << Colors::END << std::endl
			  << "---" << std::endl;

	std::cout << std::fixed << std::setprecision(12);
	std::cout << "Result: " << Colors::GREEN << result << Colors::END;

	if (expected >= 0.0) {
		bool ok = std::fabs(result - expected) < 1e-12;
		std::cout << "\nExpected: " << expected
				  << " " << (ok ? Colors::GREEN + "(Correct)" + Colors::END
								: Colors::RED + "(Incorrect)" + Colors::END);
	}
	std::cout << "\n\n";
}

void test_edge_cases() {
	std::cout << Colors::HEADER << "--- EDGE & ROBUSTNESS TESTS ---" << Colors::END << "\n\n";

	print_result(0, 0, map(0, 0)); // minimal case
	print_result(1, 0, map(1, 0));
	print_result(0, 1, map(0, 1));
	print_result(1, 1, map(1, 1));

	// Middle values
	print_result(32767, 32767, map(32767, 32767));
	print_result(10000, 50000, map(10000, 50000));
	print_result(12345, 54321, map(12345, 54321));

	// Upper boundaries
	print_result(65535, 65535, map(65535, 65535));
	print_result(65535, 0, map(65535, 0));
	print_result(0, 65535, map(0, 65535));

	// Random pattern checks
	print_result(0xAAAA, 0x5555, map(0xAAAA, 0x5555)); // alternating pattern
	print_result(0x5555, 0xAAAA, map(0x5555, 0xAAAA)); // reversed pattern
}

void test_monotonicity_hint() {
	std::cout << Colors::HEADER << "--- MONOTONICITY HINT TESTS ---" << Colors::END << "\n\n";
	double prev = 0.0;
	for (int i = 0; i <= 8; ++i) {
		double val = map(i, 0);
		std::cout << "map(" << i << ", 0) = " << std::fixed << std::setprecision(10) << val;
		if (val < prev)
			std::cout << " " << Colors::RED << "⚠ (Not strictly increasing)" << Colors::END;
		prev = val;
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main() {
	std::cout << std::endl
			  << Colors::HEADER << "--- EX10: SPACE-FILLING CURVE TESTS ---"
			  << Colors::END << std::endl
			  << std::endl;

	// Subject base examples
	std::cout << Colors::HEADER << "--- SUBJECT EXAMPLES ---" << Colors::END << "\n\n";
	print_result(0, 0, map(0, 0));
	print_result(1, 0, map(1, 0));
	print_result(0, 1, map(0, 1));
	print_result(65535, 65535, map(65535, 65535));

	test_edge_cases();
	test_monotonicity_hint();

	std::cout << Colors::GREEN << "All tests executed successfully!" << Colors::END << "\n";
	return 0;
}
