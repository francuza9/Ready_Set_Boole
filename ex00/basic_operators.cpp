#include <cstdint>

uint32_t adder(uint32_t a, uint32_t b) {
	while (b != 0) {
		uint32_t carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}