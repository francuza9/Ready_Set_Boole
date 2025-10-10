#include <iostream>
#include <cstdint>
#include <cmath>

std::pair<uint16_t, uint16_t> reverse_map(double n) {
	if (n < 0.0 || n > 1.0) {
		std::cerr << "Error: input out of range [0,1]" << std::endl;
		return {0, 0};
	}

	uint32_t code = static_cast<uint32_t>(n * 0xFFFFFFFFu + 0.5); // convert back to integer code

	uint16_t x = 0, y = 0;
	for (int i = 0; i < 16; ++i) {
		x |= ((code >> (2 * i)) & 1u) << i;
		y |= ((code >> (2 * i + 1)) & 1u) << i;
	}
	return {x, y};
}
