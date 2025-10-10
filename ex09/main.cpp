#include <iostream>
#include <vector>
#include <string>

// prototype
std::vector<int> eval_set(const std::string &formula, const std::vector<std::vector<int>> &sets);

void print_set(const std::vector<int>& s) {
	std::cout << "{ ";
	for (size_t i = 0; i < s.size(); ++i) {
		std::cout << s[i];
		if (i + 1 < s.size()) std::cout << ", ";
	}
	std::cout << " }";
}

int main() {
	std::vector<std::vector<int>> sets1 = {
		{0, 1, 2},  // A
		{0, 3, 4}   // B
	};

	std::vector<int> r1 = eval_set("AB&", sets1);
	std::cout << "Formula: AB&  →  Intersection\nResult: "; print_set(r1); std::cout << "\n\n";

	std::vector<std::vector<int>> sets3 = {
		{0, 1, 2},
		{3, 4, 5}
	};
	std::vector<int> r2 = eval_set("AB|", sets3);
	std::cout << "Formula: AB|  →  Union\nResult: "; print_set(r2); std::cout << "\n\n";

	std::vector<std::vector<int>> sets2 = {
		{0, 1, 2}   // A
	};

	std::vector<int> r3 = eval_set("A!", sets2);
	std::cout << "Formula: A!  →  Complement\nResult: "; print_set(r3); std::cout << "\n\n";

	return 0;
}
