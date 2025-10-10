#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdint>
#include <cmath>

namespace Colors {
	const std::string RED = "\033[91m";
	const std::string GREEN = "\033[92m";
	const std::string BLUE = "\033[94m";
	const std::string BOLD = "\033[1m";
	const std::string UNDERLINE = "\033[4m";
	const std::string HEADER = BOLD + BLUE + UNDERLINE;
	const std::string TEST = BLUE + BOLD;
	const std::string END = "\033[0m";
}


double map(uint16_t x, uint16_t y);
std::pair<uint16_t, uint16_t> reverse_map(double n);

void test_pair(uint16_t x, uint16_t y) {
	double encoded = map(x, y);
	auto [rx, ry] = reverse_map(encoded);
	bool ok = (x == rx && y == ry);

	std::cout << Colors::TEST << "Testing pair (" << x << ", " << y << ")"
			  << Colors::END << std::endl
			  << "---" << std::endl;

	std::cout << std::fixed << std::setprecision(12);
	std::cout << "Encoded: " << encoded << std::endl;
	std::cout << "Decoded: (" << rx << ", " << ry << ") ";

	if (ok)
		std::cout << Colors::GREEN << "(Correct)" << Colors::END << "\n\n";
	else
		std::cout << Colors::RED << "(Incorrect)" << Colors::END << "\n\n";
}

void run_tests() {
	std::cout << Colors::HEADER << "--- EX11: INVERSE FUNCTION TESTS ---" << Colors::END << "\n\n";

	// subject edge tests
	test_pair(0, 0);
	test_pair(1, 0);
	test_pair(0, 1);
	test_pair(65535, 65535);

	// mid and random
	test_pair(32767, 32767);
	test_pair(12345, 54321);
	test_pair(10000, 50000);

	// boundaries
	test_pair(65535, 0);
	test_pair(0, 65535);

	// alternating patterns
	test_pair(0xAAAA, 0x5555);
	test_pair(0x5555, 0xAAAA);
}

int main() {
	run_tests();
	std::cout << Colors::GREEN << "All inverse tests executed successfully!" << Colors::END << "\n";
	return 0;
}
