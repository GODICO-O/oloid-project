#include <vector>
#include <stdint.h>
#include <string.h>

// Fungsi buat nyari "Sidik Jari" (Signature) di memori
uintptr_t find_signature(const char* base, size_t size, const uint8_t* pattern, const char* mask) {
    size_t pattern_len = strlen(mask);
    
    for (size_t i = 0; i < size - pattern_len; i++) {
        bool found = true;
        for (size_t j = 0; j < pattern_len; j++) {
            // Jika mask bukan '?' dan byte nggak cocok, berarti bukan ini fungsinya
            if (mask[j] != '?' && pattern[j] != (uint8_t)base[i + j]) {
                found = false;
                break;
            }
        }
        if (found) return (uintptr_t)base + i;
    }
    return 0;
}
