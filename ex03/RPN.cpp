#include <string>
#include <stack>
#include <iostream>

bool eval_formula(const std::string &formula) {
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
			default:
				std::cerr << "Error: Invalid character '" << c << "' in formula." << std::endl;
				return false;
		}
	}
	if (stk.size() != 1) {
		std::cerr << "Error: Invalid formula (final stack size = " << stk.size() << ")" << std::endl;
		return false;
	}
	return stk.top();
}