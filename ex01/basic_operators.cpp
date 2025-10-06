#include <cstdint>

uint32_t adder(uint32_t a, uint32_t b) {
	while (b != 0) {
		uint32_t carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

uint32_t multiplier(uint32_t a, uint32_t b) {
	uint32_t result = 0;
	while (b > 0) {
		if (b & 1) {
			result = adder(result, a);
		}
		a <<= 1;
		b >>= 1;
	}
	return result;
}