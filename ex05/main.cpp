#include <string>
#include <iostream>
#include <iomanip>

std::string eval_formula(const std::string &formula);

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

	std::cout << std::left << std::setw(25)
			<< ("Expected " + label + ":")
			<< Colors::EXPECTED << expected << Colors::END << std::endl;

	if (is_correct)
		std::cout << std::left << std::setw(25)
				<< "Result:" << Colors::GREEN
				<< result << Colors::END << " " << status << std::endl;
	else
		std::cout << std::left << std::setw(25)
				<< "Result:" << Colors::RED
				<< result << Colors::END << " " << status << std::endl;

	std::cout << std::endl;
}

void test_eval_formula() {
	std::cout << std::endl
			<< Colors::HEADER << "--- NEGATION NORMAL FORM TESTS ---"
			<< Colors::END << std::endl << std::endl;

	struct TestCase {
		std::string input;
		std::string expected;
		bool is_valid;
	};

	TestCase tests[] = {
		// Basic negations
		{"A!", "A!", true},
		{"A!!", "A", true},
		{"AB&!", "A!B!|", true},  // ¬(A∧B)
		{"AB|!", "A!B!&", true},  // ¬(A∨B)

		// Material condition
		{"AB>", "A!B|", true},    // (A⇒B)
		{"AB>!", "AB!&", true},	  // Negated implication

		// Equivalence
		{"AB=", "A!B|B!A|&", true},     // (A⇔B)
		{"AB=!", "AB!&BA!&|", true},   // Negated equivalence

		// Nested De Morgan cases
		{"AB|C&!", "A!B!&C!|", true},   // ¬((A∨B)∧C)
		{"AB&C|!", "A!B!|C!&", true},   // ¬((A∧B)∨C)
		{"AB&C|D&!", "A!B!|C!&D!|", true}, // ¬(((A∧B)∨C)∧D)

		// Chains of implications and equivalences
		{"AB>CD>&", "A!B|C!D|&", true},  // (A⇒B) ∧ (C⇒D)
		{"AB=CD=|", "A!B|B!A|&C!D|D!C|&|", true}, // (A⇔B)∨(C⇔D)

		// Edge simple double negation cleanup
		{"A!!B!!&", "AB&", true},
		{"A!B!|!", "AB&", true}, // ¬(¬A∨¬B) = A∧B

		// Invalid or malformed
		{"!", "", false},           // missing operand
		{"A", "", false},           // no operator
		{"AB", "", false},          // incomplete
		{"AB|C", "", false},        // missing operator
		{"AB|C&&", "", false},      // too many operators
		{"abc", "", false},         // invalid chars
		{"", "", false}             // empty string
	};

	for (auto &t : tests) {
		std::cout << Colors::TEST
				<< "Testing eval_formula(\"" << t.input << "\")"
				<< Colors::END << std::endl
				<< "---" << std::endl;

		std::string result = eval_formula(t.input);
		if (t.is_valid)
			print_comparison("NNF", t.expected, result);
		else
			std::cout << Colors::RED
					<< "(Invalid formula — expected error message above)"
					<< Colors::END << std::endl << std::endl;
	}
}

int main() {
	test_eval_formula();
}
