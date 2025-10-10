#include <string>
#include <stack>
#include <iostream>
#include <map>
#include <set>
#include <vector>

bool eval_formula(const std::string &formula, const std::map<char, bool>& values = {}) {
	std::stack<bool> stk;
	for (char c : formula) {
		switch (c) {
			case '0':
			case '1':
				stk.push(c == '1');
				break;
			case '!': {
				if (stk.empty()) {
					std::cerr << "Error: Not enough operands for '!'" << std::endl;
					return false;
				}
				bool val = stk.top();
				stk.pop();
				stk.push(!val);
				break;
			}
			case '&':
			case '|':
			case '^':
			case '>':
			case '=': {
				if (stk.size() < 2) {
					std::cerr << "Error: Not enough operands for '" << c << "'" << std::endl;
					return false;
				}
				bool right = stk.top(); stk.pop();
				bool left = stk.top(); stk.pop();
				switch (c) {
					case '&': stk.push(left && right); break;
					case '|': stk.push(left || right); break;
					case '^': stk.push(left ^ right); break;
					case '>': stk.push(!left || right); break;
					case '=': stk.push(left == right); break;
				}
				break;
			}
			default: {
				if (std::isupper(c)) {
					auto it = values.find(c);
					if (it == values.end()) {
						std::cerr << "Error: No value provided for variable '" << c << "'" << std::endl;
						return false;
					}
					stk.push(it->second);
				} else {
					std::cerr << "Error: Invalid character '" << c << "' in formula." << std::endl;
					return false;
				}
			}
		}
	}
	if (stk.size() != 1) {
		std::cerr << "Error: Invalid formula (final stack size = " << stk.size() << ")" << std::endl;
		return false;
	}
	return stk.top();
}

bool sat(const std::string &formula) {
    std::set<char> variables;

    // 1. Collect all variables (A–Z)
    for (char c : formula)
        if (std::isupper(c))
            variables.insert(c);

    std::vector<char> var_list(variables.begin(), variables.end());
    int var_count = var_list.size();
    int rows = 1 << var_count; // 2^n combinations

    // 2. Try every combination of True/False
    for (int mask = 0; mask < rows; ++mask) {
        std::map<char, bool> values;
        for (int i = 0; i < var_count; ++i)
            values[var_list[i]] = (mask >> (var_count - i - 1)) & 1;

        // 3. Evaluate formula with current assignment
        if (eval_formula(formula, values))
            return true; // Satisfiable found!
    }

    // 4. No satisfying combination found
    return false;
}
