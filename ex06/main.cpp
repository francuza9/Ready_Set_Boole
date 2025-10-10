#include <iostream>
#include <iomanip>
#include <string>

std::string conjunctive_normal_form(const std::string& str);

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

void print_comparison(const std::string& label, const std::string& expected, const std::string& result) {
	bool is_correct = (expected == result);
	std::string status = is_correct ? Colors::CORRECT + "(Correct)" + Colors::END
	                                : Colors::RED + "(Incorrect)" + Colors::END;

	std::cout << std::left << std::setw(25) << ("Expected " + label + ":")
	          << Colors::EXPECTED << expected << Colors::END << std::endl;

	std::cout << std::left << std::setw(25) << "Result:"
	          << (is_correct ? Colors::GREEN : Colors::RED)
	          << result << Colors::END << " " << status << std::endl << std::endl;
}

void test_conjunctive_normal_form() {
	std::cout << std::endl << Colors::HEADER
	          << "--- CONJUNCTIVE NORMAL FORM TESTS ---"
	          << Colors::END << std::endl << std::endl;

	struct TestCase {
		std::string input;
		std::string expected;
	};

	TestCase tests[] = {
		// Subject Tests
		{"AB&!", "A!B!|"},
		{"AB|!", "A!B!&"},
		{"AB|C&", "AB|C&"},
		{"AB|C|D|", "ABCD|||"},
		{"AB&C&D&", "ABCD&&&"},
		{"AB&!C!|", "A!B!C!||"},
		{"AB|!C!&", "A!B!C!&&"},

		// Simple negations and base cases
		{"AB&!", "A!B!|"},     // ¬(A ∧ B) = ¬A ∨ ¬B
		{"AB|!", "A!B!&"},     // ¬(A ∨ B) = ¬A ∧ ¬B
		{"A!",   "A!"},        // ¬A stays ¬A

		// Already CNF
		{"AB|C&", "AB|C&"},    // (A ∨ B) ∧ C
		{"AB&C&D&", "ABCD&&&"},// A ∧ B ∧ C ∧ D

		// Nested OR distribution
		{"AB&C|", "AC|BC|&"},  // (A ∧ B) ∨ C  => (A ∨ C) ∧ (B ∨ C)
		{"ABC&|", "AB|AC|&"},  // A ∨ (B ∧ C) => (A ∨ B) ∧ (A ∨ C)

		// Multiple ORs and ANDs
		{"AB|C|D|", "ABCD|||"},// A ∨ B ∨ C ∨ D
		{"AB|!C!&", "A!B!C!&&"},// ¬(A ∨ B) ∧ ¬C
		{"AB&!C!|", "A!B!C!||"},// ¬(A ∧ B) ∨ ¬C

		// Larger distribution chain
		{"ABC&|D|", "ABD||ACD||&"}, // (A ∨ (B ∧ C)) ∨ D = (A ∨ D) ∧ (B ∨ D) ∧ (C ∨ D)
	};

	for (auto& t : tests) {
		std::cout << Colors::TEST << "Testing conjunctive_normal_form(\"" << t.input << "\")"
		          << Colors::END << std::endl << "---" << std::endl;
		std::string result = conjunctive_normal_form(t.input);
		print_comparison("CNF", t.expected, result);
	}
}

int main() {
	test_conjunctive_normal_form();
	return 0;
}
