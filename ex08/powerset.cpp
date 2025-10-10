#include <vector>

std::vector<std::vector<int>> powerset(const std::vector<int>& set) {
	std::vector<std::vector<int>> result;
	size_t n = set.size();
	size_t pow_size = 1 << n; // 2^n subsets
	result.reserve(pow_size);

	for (size_t i = 0; i < pow_size; ++i) {
		std::vector<int> subset;
		for (size_t j = 0; j < n; ++j) {
			if (i & (1 << j)) {
				subset.push_back(set[j]);
			}
		}
		result.push_back(subset);
	}
	return result;
}