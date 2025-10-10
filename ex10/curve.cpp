#include <cstdint>

uint32_t interleave_bits(uint16_t x, uint16_t y) {
    uint32_t result = 0;
    for (int i = 0; i < 16; ++i) {
        result |= ((x >> i) & 1u) << (2 * i);     // place bit from x
        result |= ((y >> i) & 1u) << (2 * i + 1); // place bit from y
    }
    return result;
}

double map(uint16_t x, uint16_t y) {
    uint32_t code = interleave_bits(x, y);
    return static_cast<double>(code) / static_cast<double>(0xFFFFFFFFu);
}