#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cctype>

std::vector<int> normalize(std::vector<int> v) {
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());
	return v;
}

std::vector<int> set_union_op(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<int> result;
	std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result));
	return normalize(result);
}

std::vector<int> set_intersection_op(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<int> result;
	std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result));
	return normalize(result);
}

std::vector<int> set_difference_op(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<int> result;
	std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result));
	return normalize(result);
}

std::vector<int> set_symmetric_diff_op(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<int> result;
	std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result));
	return normalize(result);
}

std::vector<int> set_complement_op(const std::vector<int>& a, const std::vector<int>& universe) {
	return set_difference_op(universe, a);
}

std::vector<int> set_equivalence_op(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
	auto inter = set_intersection_op(a, b);
	auto not_a = set_complement_op(a, universe);
	auto not_b = set_complement_op(b, universe);
	auto inter_neg = set_intersection_op(not_a, not_b);
	return set_union_op(inter, inter_neg);
}

std::vector<int> set_implication_op(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& universe) {
	auto not_a = set_complement_op(a, universe);
	return set_union_op(not_a, b);
}

std::vector<int> eval_set(const std::string &formula, const std::vector<std::vector<int>> &sets) {
	// compute the universe
	std::vector<int> universe;
	for (const auto &s : sets)
		universe = set_union_op(universe, s);

	std::stack<std::vector<int>> st;

	for (char c : formula) {
		if (std::isspace(c))
			continue;

		if (std::isupper(c)) {
			size_t idx = c - 'A';
			if (idx >= sets.size()) {
				std::cerr << "Error: not enough sets for variable " << c << "\n";
				return {};
			}
			st.push(sets[idx]);
		}
		else if (c == '!') {
			if (st.empty()) {
				std::cerr << "Error: missing operand for '!'\n";
				return {};
			}
			auto a = st.top(); st.pop();
			st.push(set_complement_op(a, universe));
		}
		else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=') {
			if (st.size() < 2) {
				std::cerr << "Error: not enough operands for '" << c << "'\n";
				return {};
			}
			auto b = st.top(); st.pop();
			auto a = st.top(); st.pop();

			std::vector<int> result;
			if (c == '&') result = set_intersection_op(a, b);
			else if (c == '|') result = set_union_op(a, b);
			else if (c == '^') result = set_symmetric_diff_op(a, b);
			else if (c == '>') result = set_implication_op(a, b, universe);
			else if (c == '=') result = set_equivalence_op(a, b, universe);
			st.push(result);
		}
		else {
			std::cerr << "Error: invalid character '" << c << "'\n";
			return {};
		}
	}

	if (st.size() != 1) {
		std::cerr << "Error: malformed formula.\n";
		return {};
	}

	return normalize(st.top());
}
