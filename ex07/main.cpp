#include <iostream>
#include <iomanip>
#include <string>

bool sat(const std::string& formula);

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

	std::cout << std::left << std::setw(25) << ("Expected " + label + ":")
	          << Colors::EXPECTED << (expected ? "true" : "false") << Colors::END << std::endl;

	std::cout << std::left << std::setw(25) << "Result:"
	          << (is_correct ? Colors::GREEN : Colors::RED)
	          << (result ? "true" : "false") << Colors::END
	          << " " << status << std::endl << std::endl;
}

void test_sat() {
	std::cout << std::endl << Colors::HEADER
	          << "--- SAT TESTS ---"
	          << Colors::END << std::endl << std::endl;

	struct TestCase {
		std::string input;
		bool expected;
	};

	TestCase tests[] = {
		// ✅ Subject ones (for baseline)
		{"AB|", true},
		{"AB&", true},
		{"AA!&", false},
		{"AA^", false},

		// ✅ Single variable (always satisfiable unless it's negated)
		{"A", true},
		{"A!", true},     // satisfiable because A=false satisfies ¬A

		// ✅ Tautology (always true)
		{"AA|", true},    // A ∨ A  -> always true
		{"AA=!", false},  // ¬(A ⇔ A) -> always false (never satisfiable)

		// ✅ Contradiction (never true)
		{"AA!&", false},  // A ∧ ¬A  -> false always
		{"AA!|!", false}, // ¬(A ∨ ¬A) -> false always

		// ✅ Implications
		{"AB>", true},    // ¬A ∨ B -> satisfiable for most combinations
		{"AB>!", true},   // ¬(A⇒B) == A ∧ ¬B -> satisfiable (A=true,B=false)

		// ✅ More complex
		{"AB|C&", true},  // (A∨B)∧C -> satisfiable when C=true
		{"AB&C!&", true}, // satisfiable for (A=1,B=1,C=0)

		// ✅ XOR and Equivalence
		{"AB^", true},    // true if A≠B
		{"AB=", true},    // true if A==B
		{"AA=", true},    // tautology (always true)

		// ✅ Nested combinations
		{"AB|C|D|E|", true},  // chain of ORs, definitely satisfiable
		{"AB&C&D&E&", true},  // AND chain, satisfiable if all true
		{"AA!&BB!&|", false}, // (A∧¬A)∨(B∧¬B) -> unsatisfiable

		// ✅ Mix with constants
		{"10&", false},  // 1 ∧ 0
		{"10|", true},   // 1 ∨ 0
		{"1!", false},   // ¬1
		{"0!", true},    // ¬0

		// ✅ Edge / malformed cases
		{"", false},     // empty formula (undefined, but return false)
		{"!", false},    // missing operand
		{"A0&", false},  // A∧0 -> always false
		{"A1|", true},   // A∨1 -> always true
	};

	for (auto& t : tests) {
		std::cout << Colors::TEST << "Testing sat(\"" << t.input << "\")"
		          << Colors::END << std::endl << "---" << std::endl;
		bool result = sat(t.input);
		print_comparison("SAT", t.expected, result);
	}
}

int main() {
	test_sat();
	return 0;
}
