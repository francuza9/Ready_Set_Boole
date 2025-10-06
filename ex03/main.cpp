#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>

bool eval_formula(const std::string &formula);

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

void print_comparison(const std::string& label, bool expected, bool result) {
	bool is_correct = (expected == result);
	std::string status = is_correct ? Colors::CORRECT + "(Correct)" + Colors::END
									: Colors::RED + "(Incorrect)" + Colors::END;

	std::cout << std::left << std::setw(25)
			<< ("Expected " + label + ":")
			<< Colors::EXPECTED << (expected ? "true" : "false")
			<< Colors::END << std::endl;

	if (is_correct)
		std::cout << std::left << std::setw(25)
				<< "Result:" << Colors::GREEN
				<< (result ? "true" : "false")
				<< Colors::END << " " << status << std::endl;
	else
		std::cout << std::left << std::setw(25)
				<< "Result:" << Colors::RED
				<< (result ? "true" : "false")
				<< Colors::END << " " << status << std::endl;

	std::cout << std::endl;
}

void test_eval_formula() {
	std::cout << std::endl
			<< Colors::HEADER << "--- BOOLEAN EVALUATION TESTS ---"
			<< Colors::END << std::endl << std::endl;

	struct TestCase {
		std::string expr;
		bool expected;
		bool is_valid;
	};

	TestCase tests[] = {
		// simple valid
		{"10&", false, true},
		{"10|", true, true},
		{"11^", false, true},
		{"10^", true, true},
		{"11>", true, true},
		{"10>", false, true},
		{"10=", false, true},
		{"11=", true, true},
		{"101|&", true, true},   // 1 & (0 | 1)
		{"1011||=", true, true}, // (1 | 0 | 1) == 1
		{"10!&", true, true},    // 1 & !0

		// nested logical combinations
		{"110|&", true, true},   // 1 & (1 | 0)
		{"101^!", false, true},  // !(1 ^ 0) -> false
		{"101|!", false, true},  // !(1 | 0) -> false
		{"110|>", true, true},   // 1 ⇒ (1 | 0) -> true
		{"110|=", false, true},  // 1 == (1 | 0) -> false

		// longer valid chains
		{"110011&&||", true, true},
		{"101010&&||=", true, true},
		{"101010||&&=", true, true},

		// malformed / invalid (should print error but behavior undefined)
		{"!", false, false},             // unary op no operand
		{"1!", false, false},            // leftover result
		{"10", false, false},            // missing operator
		{"10&1", false, false},          // extra operand
		{"1011||==", false, false},      // too many operators
		{"abcd", false, false},          // invalid characters
		{"", false, false},              // empty string
		{"1!!", false, false},           // extra negation after finished
		{"11>!", false, false},          // negating after complete formula
	};

	for (auto& t : tests) {
		std::cout << Colors::TEST
				<< "Testing eval_formula(\"" << t.expr << "\")"
				<< Colors::END << std::endl << "---" << std::endl;

		bool result = eval_formula(t.expr);
		if (t.is_valid)
			print_comparison("Value", t.expected, result);
		else
			std::cout << Colors::RED
					<< "(Invalid formula — expected error message above)"
					<< Colors::END << std::endl << std::endl;
	}
}

int main() {
	test_gray_code();
	return 0;
}