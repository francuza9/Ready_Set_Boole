#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <iostream>

std::string eval_formula(const std::string &formula);

static std::string flatten_or(const std::string& a, const std::string& b) {
	std::string merged;

	// remove trailing '|' characters (to avoid duplicates)
	std::string cleanA = a;
	while (!cleanA.empty() && cleanA.back() == '|')
		cleanA.pop_back();

	std::string cleanB = b;
	while (!cleanB.empty() && cleanB.back() == '|')
		cleanB.pop_back();

	// concatenate both sides
	merged = cleanA + cleanB;

	// count number of literals (by counting uppercase letters)
	int literals = 0;
	for (char c : merged)
		if (std::isupper(c))
			literals++;

	// append (literals - 1) '|'
	merged.append(std::max(0, literals - 1), '|');
	return merged;
}


static std::vector<std::string> distribute(
	const std::vector<std::string>& left,
	const std::vector<std::string>& right)
{
	std::vector<std::string> result;
	for (const auto& a : left)
		for (const auto& b : right)
			result.push_back(flatten_or(a, b));
	return result;
}

std::string conjunctive_normal_form(const std::string& str)
{
	std::stack<std::vector<std::string>> st;
	std::string nnf = eval_formula(str); // your ex05 function gives valid NNF
	std::cout << "STR: " << str << " => NNF: " << nnf << std::endl;

	for (size_t i = 0; i < nnf.size(); ++i)
	{
		char c = nnf[i];

		// Case 1: variable (A–Z)
		if (std::isupper(c))
		{
			std::string lit(1, c);
			// attach negation if next char is '!'
			if (i + 1 < nnf.size() && nnf[i + 1] == '!')
			{
				lit += "!";
				++i;
			}
			st.push({ lit }); // single clause CNF
		}

		// Case 2: AND — merge clause lists
		else if (c == '&')
		{
			auto right = st.top(); st.pop();
			auto left  = st.top(); st.pop();
			std::vector<std::string> merged = left; // left first, then right
			merged.insert(merged.end(), right.begin(), right.end());
			st.push(merged);
		}

		// Case 3: OR — distribute OR over AND
		else if (c == '|')
		{
			auto right = st.top(); st.pop();
			auto left  = st.top(); st.pop();
			st.push(distribute(left, right));
		}

		// No other tokens possible in valid NNF
	}
	std::cout << "CNF clauses: ";
	for (const auto& clause : st.top())
		std::cout << " " << clause;
	std::cout << std::endl;
	// At the end: only one CNF (list of clauses)
	if (st.empty())
		return "";
	auto clauses = st.top();
	std::string res;
	for (const auto& clause : clauses)
		res += clause;
	for (unsigned int i = 0; i < clauses.size() - 1; ++i)
		res += "&"; // RPN conjunction
	std::cout << "clauses size: " << clauses.size() << std::endl;

	return res;
}

// ------------------- NEGATION -------------------
std::string simplify_double_negations(std::string s) {
	size_t pos;
	while ((pos = s.find("!!")) != std::string::npos)
		s.erase(pos, 2);
	return s;
}

std::string apply_negation(const std::string &expr) {
	if (expr.empty()) return "";

	// Base case: single variable
	if (expr.size() == 1 && std::isupper(expr[0]))
		return expr + "!";

	// Detect the main operator at the end
	char op = expr.back();
	if (op != '&' && op != '|') {
		return expr + "!";
	}

	// Split into left and right subexpressions
	std::stack<std::string> stk;
	for (size_t i = 0; i < expr.size() - 1; ++i) {
		char c = expr[i];
		if (std::isupper(c)) stk.push(std::string(1, c));
		else if (c == '!') {
			auto a = stk.top(); stk.pop();
			stk.push(apply_negation(a)); // recursive call
		}
		else if (c == '&' || c == '|') {
			auto b = stk.top(); stk.pop();
			auto a = stk.top(); stk.pop();
			stk.push(a + b + c);
		}
	}

	// Pop the two operands
	std::string right = stk.top(); stk.pop();
	std::string left  = stk.top(); stk.pop();

	// Apply De Morgan’s swap
	char new_op = (op == '&') ? '|' : '&';
	std::string res = apply_negation(left) + apply_negation(right) + new_op;
	return simplify_double_negations(res);
}


// ------------------- MATERIAL CONDITION -------------------
std::string apply_material_conditions(const std::string &left,
									const std::string &right) {
	if (left.empty() || right.empty()) {
		std::cerr << "Error: Cannot apply material condition to empty expressions.\n";
		return "";
	}
	// (A ⇒ B) ⇔ (¬A ∨ B)
	return left + "!" + right + "|";
}

// ------------------- EQUIVALENCE -------------------
std::string apply_equivalence(const std::string &left,
							const std::string &right) {
	if (left.empty() || right.empty()) {
		std::cerr << "Error: Cannot apply equivalence to empty expressions.\n";
		return "";
	}
	// (A ⇔ B) ⇔ ((¬A ∨ B) ∧ (¬B ∨ A))
	std::string new_left  = apply_material_conditions(left, right);
	std::string new_right = apply_material_conditions(right, left);
	return new_left + new_right + "&";
}

// ------------------- MAIN PARSER -------------------
std::string eval_formula(const std::string &formula) {
	std::stack<std::string> stk;
	for (char c : formula) {
		if (std::isupper(c)) {
			stk.emplace(1, c);
		}
		else if (c == '!') {
			if (stk.empty()) {
				std::cerr << "Error: Not enough operands for '!'\n";
				return "";
			}
			std::string val = stk.top(); stk.pop();
			stk.push(apply_negation(val));
		}
		else if (c == '|' || c == '&' || c == '>' || c == '=') {
			if (stk.size() < 2) {
				std::cerr << "Error: Not enough operands for '" << c << "'\n";
				return "";
			}
			std::string right = stk.top(); stk.pop();
			std::string left  = stk.top(); stk.pop();

			if (c == '|')      stk.push(left + right + "|");
			else if (c == '&') stk.push(left + right + "&");
			else if (c == '>') stk.push(apply_material_conditions(left, right));
			else if (c == '=') stk.push(apply_equivalence(left, right));
		}
		else {
			std::cerr << "Error: Unknown character '" << c << "' in formula.\n";
			return "";
		}
	}

	if (stk.empty()) {
		std::cerr << "Error: Empty result stack. Invalid formula?\n";
		return "";
	}
	if (stk.size() > 1) {
		std::cerr << "Error: More than one element left in stack. Invalid formula?\n";
		return "";
	}
	if (stk.size() == 1 && formula.find_first_of("&|>=!") == std::string::npos) {
		std::cerr << "Error: Formula must contain at least one operator.\n";
		return "";
	}
	return simplify_double_negations(stk.top());
}
